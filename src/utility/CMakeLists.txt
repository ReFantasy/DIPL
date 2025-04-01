AUX_SOURCE_DIRECTORY(. UTILITY_LIST)


file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/include/utility/*.h)
source_group("${CMAKE_CURRENT_SOURCE_DIR}" FILES ${UTILITY_LIST} ${HEADER_FILES})

ADD_LIBRARY(utility ${UTILITY_LIST} ) 

target_link_libraries(utility algorithm)

# 安装
INSTALL(TARGETS utility ARCHIVE DESTINATION lib)

# FILE(GLOB HEADER_FILE ./*.h ./*.hpp) #所有头文件存入变量
# FOREACH(F ${HEADER_FILE})
#     INSTALL(FILES ${F} DESTINATION ${PROJECT_BINARY_DIR}/install/include/utility)
# ENDFOREACH(F)


