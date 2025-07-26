from setuptools import setup, Extension
import pybind11

ext_modules = [
    Extension(
        "gdi",
        ["module.cpp"],
        include_dirs=[pybind11.get_include()],
        libraries=['user32', 'gdi32'],
        language="c++"
    )
]

setup(
    name="gdi",
    ext_modules=ext_modules
)

# python setup.py build_ext --inplace