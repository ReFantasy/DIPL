CMAKE_MINIMUM_REQUIRED(VERSION 3.20...4.4)
PROJECT(IPL VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type - Release by default
# if(NOT CMAKE_BUILD_TYPE)
#     set(CMAKE_BUILD_TYPE Release)
# elseif(CMAKE_BUILD_TYPE MATCHES "Debug")
#     add_definitions(-DDEBUG)
# endif()
# message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release RelWithDebInfo MinSizeRel)
endif()
add_compile_definitions($<$<CONFIG:Debug>:DEBUG>)

if(APPLE AND NOT DEFINED OpenMP_ROOT)
    set(OpenMP_ROOT "/opt/homebrew/opt/libomp")   # 允许 -DOpenMP_ROOT 覆盖（Intel Mac 等）
endif()
find_package(OpenMP REQUIRED COMPONENTS CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")



add_compile_definitions(DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/sample/data")
#include_directories(${PROJECT_SOURCE_DIR}/include)

# 顶层 CMakeLists.txt，放在 add_subdirectory 之前
if(WIN32 AND MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(sample)
