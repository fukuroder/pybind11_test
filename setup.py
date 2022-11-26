from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension

ext_modules = [
    Pybind11Extension("pybind11_test", ["sample.cpp", "minfft/minfft.c"])
]

setup(
    name="pybind11_test",
    ext_modules=ext_modules,
    install_requires=["numpy"])
