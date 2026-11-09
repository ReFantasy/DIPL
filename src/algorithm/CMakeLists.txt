AUX_SOURCE_DIRECTORY(. ALGORITHM_LIST)


source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${ALGORITHM_LIST} )

file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/include/algorithm/*.h)
ADD_LIBRARY(algorithm SHARED ${ALGORITHM_LIST} ${HEADER_FILES})



target_link_libraries(algorithm OpenMP::OpenMP_CXX)

target_include_directories(algorithm
        INTERFACE
        ${CMAKE_SOURCE_DIR}/include/)


# 安装
INSTALL(TARGETS algorithm
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin)

# FILE(GLOB HEADER_FILE ./*.h ./*.hpp) #所有头文件存入变量
# FOREACH(F ${HEADER_FILE})
#     INSTALL(FILES ${F} DESTINATION ${PROJECT_BINARY_DIR}/install/include/algorithm)
# ENDFOREACH(F)

# 导出全部符号，否则 MSVC 不会生成 algorithm.lib（导入库），依赖它的目标无法链接
if(WIN32)
    set_target_properties(algorithm PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
    add_custom_command(TARGET algorithm POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:algorithm>
            $<TARGET_RUNTIME_DLLS:algorithm>
            COMMAND_EXPAND_LISTS
            COMMENT "Copying runtime DLLs (via TARGET_RUNTIME_DLLS)..."
        )
endif()








