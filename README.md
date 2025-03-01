# IPL
The C++ Implement of Digital Image Processing, Third Ediiton.

## Install

*Your system should have installed **cmake** and **OpenCV**.* 

> Especially on Windows systems, you should add the following to the PATH environment variable: *YOUR_OPENCV_PATH\build\x64\vc15\bin*

### Windows
```bash
cmake -S . -B build -DOpenCV_DIR="E:/opencv/build/x64/vc15/lib" -DUSER_INSTALL_PREFIX=install
```
then open visual studio project in build dirctory.

### Linux & MacOS
```bash
cmake -S . -B build -DUSER_INSTALL_PREFIX=./build/install
cmake --build build
```

