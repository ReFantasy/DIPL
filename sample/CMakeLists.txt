# ADD_SUBDIRECTORY(ch01) 
# ADD_SUBDIRECTORY(ch02) 
ADD_SUBDIRECTORY(ch03) 
ADD_SUBDIRECTORY(ch04) 
ADD_SUBDIRECTORY(ch05)
ADD_SUBDIRECTORY(ch07) 
ADD_SUBDIRECTORY(ch08)
ADD_SUBDIRECTORY(ch09)

add_executable(test test.cpp)
target_link_libraries(test algorithm utility)






