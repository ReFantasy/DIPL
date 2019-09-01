CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(IPL)
ADD_COMPILE_OPTIONS(-std=c++11)

# 依赖
IF (WIN32)
    MESSAGE(STATUS "operating system is windows")
    find_package(OpenCV REQUIRED)
	
ELSEIF (APPLE)
    MESSAGE(STATUS "operating system is Apple system.")
	include_directories("/Users/refantasy/opencv-4.1.0/build/install/include/opencv4/")
    link_directories("/Users/refantasy/opencv-4.1.0/build/install/lib")
ELSEIF (UNIX)
	MESSAGE(STATUS "operating system is UNIX-like OS.")
ENDIF ()




ADD_SUBDIRECTORY(SRC)





