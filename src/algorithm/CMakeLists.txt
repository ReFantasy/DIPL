# 傅里叶变换库
SET(LIBFOURIER_SRC Fourier.cpp)
ADD_LIBRARY(fourier SHARED ${LIBFOURIER_SRC}) # 动态库
ADD_LIBRARY(fourier_static STATIC ${LIBFOURIER_SRC}) # 静态库
SET_TARGET_PROPERTIES(fourier_static PROPERTIES OUTPUT_NAME "fourier") # 使用相同的名字


# 滤波器生成库
SET(LIBfilter_SRC frequency_filter.cpp)
ADD_LIBRARY(filter SHARED ${LIBfilter_SRC})
ADD_LIBRARY(filter_static STATIC ${LIBfilter_SRC})
SET_TARGET_PROPERTIES(filter_static PROPERTIES OUTPUT_NAME "filter")


