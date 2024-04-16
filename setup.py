from setuptools import setup, Extension

setup(
    name="cext",
    version="1.0.0",
    description="Python interface for the fputs C library function",
    author="<your name>",
    author_email="your_email@gmail.com",
    ext_modules=[Extension("cext", ["cext.c"])]
)

