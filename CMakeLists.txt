CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(IPL)

ADD_COMPILE_OPTIONS(-std=c++11)

ADD_SUBDIRECTORY(SRC)

# 平台判断
MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
	MESSAGE(STATUS "current platform: Linux ")

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")

	MESSAGE(STATUS "current platform: Windows")
                MESSAGE(STATUS "OpenCV include...")
                INCLUDE_DIRECTORIES("D:\\opencv-3.4.5\\opencv-3.4.5\\Build\\install\\include\\")


ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
	MESSAGE(STATUS "current platform: FreeBSD")
ELSE ()
	MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")

ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")


