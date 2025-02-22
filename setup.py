import sys
from setuptools import setup, Extension
from Cython.Build import cythonize

extra_link_args = ["-static"] if sys.platform == "win32" else []
options = {"build_ext": {"compiler": "mingw32"}} if sys.platform == "win32" else {}

setup(
    name='gap buffer in python',
    ext_modules=cythonize(
        Extension(
            "pygap",
            ["pygap.pyx"],
            language="c++",
            extra_link_args=extra_link_args,
            define_macros=[("EXPORT_SHARED", "1")]
        )
    ),
    options=options
)
