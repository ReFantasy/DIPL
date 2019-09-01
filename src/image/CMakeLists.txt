#链接库搜索目录
LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/lib)

# 
SET(LIBIMAGE_SRC Image.cpp)
ADD_LIBRARY(image SHARED ${LIBIMAGE_SRC} )
ADD_LIBRARY(image_static STATIC ${LIBIMAGE_SRC} )
SET_TARGET_PROPERTIES(image_static PROPERTIES OUTPUT_NAME "image")

# 链接库image依赖于fourier和filter
TARGET_LINK_LIBRARIES(image fourier filter)

# 将第三方的库链接到可执行文件
#TARGET_LINK_LIBRARIES(image ${OpenCV_LIBS} fourier filter) 



