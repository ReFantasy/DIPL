#添加子目录
ADD_SUBDIRECTORY(algorithm)
ADD_SUBDIRECTORY(utility)

# 递归安装头文件
INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
        DESTINATION include/
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")

