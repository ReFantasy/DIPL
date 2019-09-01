
#相关库文件的目录
LINK_DIRECTORIES( ${PROJECT_BINARY_DIR}/install/lib ) 

# 
SET(LIBIMAGE_SRC Image.cpp)
ADD_LIBRARY(image SHARED ${LIBIMAGE_SRC})
ADD_LIBRARY(image_static STATIC ${LIBIMAGE_SRC})
SET_TARGET_PROPERTIES(image_static PROPERTIES OUTPUT_NAME "image")

# 将第三方的库链接到可执行文件
target_link_libraries(image ${OpenCV_LIBS} fourier filter) 

INSTALL(FILES Image.h DESTINATION ${PROJECT_BINARY_DIR}/install/include/image)
INSTALL(TARGETS image image_static
        LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/install/lib
		ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/install/lib)


