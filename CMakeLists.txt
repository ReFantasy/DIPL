CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
PROJECT(IPL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# 配置 OpenCV 库
#set(OpenCV_DIR "E:/opencv/build/x64/vc15/lib")
FIND_PACKAGE( OpenCV REQUIRED )
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )
LINK_LIBRARIES( ${OpenCV_LIBS} )

# 库文件输出目录
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
# 可执行文件输出目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)


# Build type - Release by default
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
elseif(CMAKE_BUILD_TYPE MATCHES "Debug")
	add_definitions(-DDEBUG)
endif()

#字符集
# Add_Definitions(-DUNICODE -D_UNICODE)


add_definitions(-DDATA_DIR="${PROJECT_SOURCE_DIR}/sample/data")
add_definitions(-DMY_VARIABLE=100)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/algorithm)
include_directories(${PROJECT_SOURCE_DIR}/include/utility)


ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(sample)

# 拷贝资源图片到指定位置
# file(COPY ./sample/data DESTINATION ./install/)
# file(COPY ./sample/data DESTINATION ./sample/)






