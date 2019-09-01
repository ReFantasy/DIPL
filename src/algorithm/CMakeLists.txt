AUX_SOURCE_DIRECTORY(. ALGORITHM_LIST)
ADD_LIBRARY(algorithm SHARED ${ALGORITHM_LIST}) # 动态库
ADD_LIBRARY(algorithm_static STATIC ${ALGORITHM_LIST}) # 静态库
SET_TARGET_PROPERTIES(algorithm_static PROPERTIES OUTPUT_NAME "algorithm") # 使用相同的名字


# 安装
INSTALL(TARGETS algorithm algorithm_static
        LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/install/lib
        ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/install/lib)

file(GLOB HEADER_FILE ./*.h ./*.hpp) #所有头文件存入变量
FOREACH(F ${HEADER_FILE})
    INSTALL(FILES ${F} DESTINATION ${PROJECT_BINARY_DIR}/install/include/algorithm)
ENDFOREACH(F)







# 傅里叶变换库
#SET(LIBFOURIER_SRC Fourier.cpp)
#ADD_LIBRARY(fourier SHARED ${LIBFOURIER_SRC}) # 动态库
#ADD_LIBRARY(fourier_static STATIC ${LIBFOURIER_SRC}) # 静态库
#SET_TARGET_PROPERTIES(fourier_static PROPERTIES OUTPUT_NAME "fourier") # 使用相同的名字


# 滤波器生成库
#SET(LIBfilter_SRC frequency_filter.cpp)
#ADD_LIBRARY(filter SHARED ${LIBfilter_SRC})
#ADD_LIBRARY(filter_static STATIC ${LIBfilter_SRC})
#SET_TARGET_PROPERTIES(filter_static PROPERTIES OUTPUT_NAME "filter")


