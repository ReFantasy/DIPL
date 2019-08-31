#添加子目录
ADD_SUBDIRECTORY(algorithm)
#ADD_SUBDIRECTORY(assist) 
#ADD_SUBDIRECTORY(book_example) 
#ADD_SUBDIRECTORY(image) 


include_directories("/Users/refantasy/opencv-4.1.0/build/install/include/opencv4/")
link_directories("/Users/refantasy/opencv-4.1.0/build/install/lib")



ADD_EXECUTABLE(main main.cpp)

# 将第三方的库链接到可执行文件
target_link_libraries(main fourier opencv_world filter opencv_world.4.1.0)
