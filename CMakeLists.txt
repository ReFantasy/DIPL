CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(IPL)
ADD_COMPILE_OPTIONS(-std=c++11)

# 配置 OpenCV 库
FIND_PACKAGE( OpenCV REQUIRED )
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )
LINK_LIBRARIES( ${OpenCV_LIBS} )

# 目标文件输出目录
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

	
# 输出平台信息
IF (WIN32)
    MESSAGE(STATUS "operating system is windows")
ELSEIF (APPLE)
    MESSAGE(STATUS "operating system is Apple system.")
ELSEIF (UNIX)
	MESSAGE(STATUS "operating system is UNIX-like OS.")
ENDIF ()

ADD_SUBDIRECTORY(SRC)

# 拷贝资源图片到指定位置
file(COPY ./src/book_example/data DESTINATION ./install/)
file(COPY ./src/book_example/data DESTINATION ./src/book_example/)





