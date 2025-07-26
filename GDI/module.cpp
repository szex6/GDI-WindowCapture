#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <windows.h>

namespace py = pybind11;

class GDI {
private:
    HWND hwnd = nullptr;
    HDC hdcWindow = nullptr;
    HDC hdcMemDC = nullptr;
    HBITMAP hbmDIB = nullptr;
    BITMAPINFO bmi = {};
    uint8_t* buffer = nullptr;
    int width = 0, height = 0;

    void UpdateRect() {
        RECT rc;
        GetClientRect(hwnd, &rc);
        
        // Update when rect change
        if (width != rc.right || height != rc.bottom) {
            width = rc.right;
            height = rc.bottom;

            if (hbmDIB) { DeleteObject(hbmDIB); }

            ZeroMemory(&bmi, sizeof(bmi));
            bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            bmi.bmiHeader.biWidth = width;
            bmi.bmiHeader.biHeight = -height;  
            bmi.bmiHeader.biPlanes = 1;
            bmi.bmiHeader.biBitCount = 32;
            bmi.bmiHeader.biCompression = BI_RGB;

            hbmDIB = CreateDIBSection(hdcWindow, &bmi, DIB_RGB_COLORS, (void**)&buffer, NULL, 0);
            SelectObject(hdcMemDC, hbmDIB);
        } 
    }

public:
    GDI(const char* title) {
        hwnd = FindWindow(NULL, title);
        hdcWindow = GetDC(hwnd);
        hdcMemDC = CreateCompatibleDC(hdcWindow);
    }

    ~GDI() {
        if (hbmDIB) DeleteObject(hbmDIB);
        if (hdcMemDC) DeleteDC(hdcMemDC);
        if (hdcWindow) ReleaseDC(hwnd, hdcWindow);
    }

    py::array_t<uint8_t> capture() {
        UpdateRect();
        BitBlt(hdcMemDC, 0, 0, width, height, hdcWindow, 0, 0, SRCCOPY);
        
        return py::array_t<uint8_t>(
            {height, width, 4},
            {width * 4, 4, 1 },
            buffer
        );
    }

    py::tuple rect() const {
        POINT pt = { 0, 0 };
        ClientToScreen(hwnd, &pt);

        return py::make_tuple(pt.x, pt.y, width, height);
    }
};

PYBIND11_MODULE(gdi, mod) {
    py::class_<GDI>(mod, "GDI")
        .def(py::init<const char*>())
        .def("capture", &GDI::capture)
        .def("rect", &GDI::rect);
}