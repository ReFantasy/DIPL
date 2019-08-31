# 傅里叶变换库
SET(LIBFOURIER_SRC Fourier.cpp)
ADD_LIBRARY(fourier SHARED ${LIBFOURIER_SRC})
ADD_LIBRARY(fourier_static STATIC ${LIBFOURIER_SRC})
SET_TARGET_PROPERTIES(fourier_static PROPERTIES OUTPUT_NAME "fourier")

INSTALL(FILES fourier.h DESTINATION ${PROJECT_BINARY_DIR}/install/include/algorithm)
INSTALL(TARGETS fourier fourier_static
        LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/install/lib
		ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/install/lib)


# 滤波器生成库
SET(LIBfilter_SRC frequency_filter.cpp)
ADD_LIBRARY(filter SHARED ${LIBfilter_SRC})
ADD_LIBRARY(filter_static STATIC ${LIBfilter_SRC})
SET_TARGET_PROPERTIES(filter_static PROPERTIES OUTPUT_NAME "filter")

INSTALL(FILES frequency_filter.h DESTINATION ${PROJECT_BINARY_DIR}/install/include/algorithm)
INSTALL(TARGETS filter filter_static
        LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/install/lib
		ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/install/lib)

