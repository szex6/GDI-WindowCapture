# 🖥️ GDI Screen Capture (Python + C++ via pybind11)

A high-performance screen capture module using Windows GDI, wrapped for Python using `pybind11`. Supports fast pixel data extraction and optional window rectangle info.

---

## ✅ Features

- Ultra-fast capture using `BitBlt` and `CreateDIBSection`
- Python integration via `pybind11`
- Capture specific window by title
- Return pixel buffer as a NumPy array
- Get window position and size (x, y, width, height)

---

## ⚙️ Installation

### Requirements

- Python 3.8+
- `pybind11`
- Visual Studio Build Tools (with C++ support)

### Build

```bash
python setup.py build_ext --inplace
```

## 🚀 Usage

```python
import gdi
import cv2

window = gdi.GDI("File Explorer")

img = window.capture()

x, y, w, h = window.rect()

cv2.imshow("Result", img)
```
