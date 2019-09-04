CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(IPL)
#PROJECT(IPL)
ADD_COMPILE_OPTIONS(-std=c++11)

# 配置 OpenCV 库
FIND_PACKAGE( OpenCV REQUIRED )
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )
LINK_LIBRARIES( ${OpenCV_LIBS} )

# 库文件输出目录
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
# 可执行文件输出目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
	
# 输出平台信息
IF (WIN32)
    MESSAGE(STATUS "operating system is windows")
ELSEIF (APPLE)
    MESSAGE(STATUS "operating system is Apple system.")
ELSEIF (UNIX)
	MESSAGE(STATUS "operating system is UNIX-like OS.")
ENDIF ()

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(sample)

# 拷贝资源图片到指定位置
file(COPY ./sample/data DESTINATION ./install/)
file(COPY ./sample/data DESTINATION ./sample/)






