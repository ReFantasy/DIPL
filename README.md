# DIPL
The C++ Implement of Digital Image Processing, Third Ediiton. For educational and learning purposes.

## Install

Your system should have installed **cmake** and **OpenCV**.

> On Windows, you should add the variable: *YOUR_OPENCV_PATH\build\x64\vc15\bin* to PATH environment. 

#### Windows
```bash
cmake -S . -B build -DOpenCV_DIR="E:/opencv/build/x64/vc15/lib" -DUSER_INSTALL_PREFIX=install
```
Please replace *OpenCV_DIR* with your own path, then open Visual Studio project in build dirctory.

#### Linux & MacOS
```bash
cmake -S . -B build -DUSER_INSTALL_PREFIX=./install
cmake --build build -j8 --target install
```

