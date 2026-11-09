CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
PROJECT(IPL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Build type - Release by default
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
elseif(CMAKE_BUILD_TYPE MATCHES "Debug")
	add_definitions(-DDEBUG)
endif()
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# 设置 CMAKE_INSTALL_PREFIX 的默认值
if(NOT USER_INSTALL_PREFIX)
	set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/install)
else()
	set(CMAKE_INSTALL_PREFIX ${USER_INSTALL_PREFIX})
endif()

if(WIN32)
	MESSAGE(STATUS "operating system is windows")
	find_package(OpenMP REQUIRED)
elseif(APPLE)
	MESSAGE(STATUS "operating system is Apple system.")
	set(OpenMP_ROOT "/opt/homebrew/opt/libomp")  # Apple Silicon Mac
	find_package(OpenMP REQUIRED)
	set(TASKING_SYSTEM_LIBS OpenMP::OpenMP_CXX)
elseif(UNIX)
	MESSAGE(STATUS "operating system is UNIX-like OS.")
	find_package(OpenMP REQUIRED)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

# 库文件输出目录
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
# 可执行文件输出目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# 配置 OpenCV 库
set(OpenCV_DIR "C:/opencv/build")
FIND_PACKAGE( OpenCV REQUIRED )
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
LINK_LIBRARIES(${OpenCV_LIBS})

add_definitions(-DDATA_DIR="${PROJECT_SOURCE_DIR}/sample/data")

include_directories(${PROJECT_SOURCE_DIR}/include)
# include_directories(${PROJECT_SOURCE_DIR}/include/algorithm)
# include_directories(${PROJECT_SOURCE_DIR}/include/utility)


ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(sample)
