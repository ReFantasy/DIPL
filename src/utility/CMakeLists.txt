AUX_SOURCE_DIRECTORY(. UTILITY_LIST)


source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${UTILITY_LIST})

file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/include/utility/*.h)
ADD_LIBRARY(utility ${UTILITY_LIST} ${HEADER_FILES})

# 导出全部符号，否则 MSVC 不会生成 utility.lib（导入库），可执行文件无法链接
if(WIN32)
    set_target_properties(utility PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

target_link_libraries(utility algorithm OpenMP::OpenMP_CXX)

target_include_directories(utility
        INTERFACE
        ${CMAKE_SOURCE_DIR}/include/)

# 安装
INSTALL(TARGETS utility
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin)

# FILE(GLOB HEADER_FILE ./*.h ./*.hpp) #所有头文件存入变量
# FOREACH(F ${HEADER_FILE})
#     INSTALL(FILES ${F} DESTINATION ${PROJECT_BINARY_DIR}/install/include/utility)
# ENDFOREACH(F)
