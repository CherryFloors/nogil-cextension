pip uninstall -y cext
python -m build .
pip install dist/cext-1.0.0-cp310-cp310-linux_x86_64.whl
