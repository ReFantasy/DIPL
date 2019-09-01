#添加子目录
ADD_SUBDIRECTORY(algorithm)
ADD_SUBDIRECTORY(assist) 
ADD_SUBDIRECTORY(book_example) 
ADD_SUBDIRECTORY(image) 

ADD_EXECUTABLE(main main.cpp)

# 将第三方的库链接到可执行文件
target_link_libraries(main fourier filter ${OpenCV_LIBS})
