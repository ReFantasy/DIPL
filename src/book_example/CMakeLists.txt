#相关库文件的目录
LINK_DIRECTORIES( ${PROJECT_BINARY_DIR}/install/lib ) 

# 生成目标文件
ADD_EXECUTABLE(test test.cpp)
	
# 将第三方的库链接到可执行文件
target_link_libraries(test ${OpenCV_LIBS} fourier filter) 

