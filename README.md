# IPL
The Implement of Digital Image Processing, Third Ediiton.

![](./sample/book.jpg)

## Install

*Your system should have installed **cmake** and **OpenCV**.* 

Especially on Windows systems, you should add the following to the PATH environment variable: *YOUR_OPENCV_PATH\build\x64\vc15\bin*, and you also should create an new environment variable *OpenCV_DIR* whose value is *YOUR_OPENCV_PATH\build*.

### Windows(eg. Visual Studio 2017)

1. Open console
2. Go to the root directory
3. Create folder build by executing *mkdir build*
4. *cd build*
5. executive command *cmake -G "Visual Studio 15 Win64" ..* or *cmake -G "Visual Studio 15" ..*
6. Open solution *IPL.sln* generated in the previous step by Visual Studio 2017
7. Generate solutions *ALL_BUILD*
8. Generate solutions *INSTALL*