# 🖥️ GDI Screen Capture (Python + C++ via pybind11)

A high-performance screen capture module using Windows GDI, wrapped for Python using `pybind11`. Supports fast pixel data extraction and optional window rectangle info.

## ✅ Features

- Ultra-fast capture using `BitBlt` and `CreateDIBSection`
- Python integration via `pybind11`
- Capture specific window by title
- Return pixel buffer as NumPy array
- Query window position and size

## ⚙️ Installation

### Requirements

- Python 3.8+
- `pybind11`
- Visual Studio Build Tools (C++)

### Build

```bash
python setup.py build_ext --inplace

### Usage

```bash
import gdi

# Initialize with window title
win = gdi.GDI("Calculator")

# Capture the image
img = win.capture()

# Get window position and size
x, y, w, h = win.rect()

# Use with OpenCV or NumPy
import cv2
cv2.imshow("Captured", img)
cv2.waitKey(0)
