# 配置 OpenCV 库
FIND_PACKAGE( OpenCV REQUIRED )
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

AUX_SOURCE_DIRECTORY(. UTILITY_LIST)


source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${UTILITY_LIST})

file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/include/utility/*.h)
ADD_LIBRARY(utility SHARED ${UTILITY_LIST} ${HEADER_FILES})


target_link_libraries(utility
    PUBLIC algorithm OpenMP::OpenMP_CXX ${OpenCV_LIBS})

target_include_directories(utility
        PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        ${OpenCV_INCLUDE_DIRS}
        )


if(WIN32)
    # set_target_properties(algorithm PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
    add_custom_command(TARGET utility POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:utility>
            $<TARGET_RUNTIME_DLLS:utility>
            COMMAND_EXPAND_LISTS
            COMMENT "Copying runtime DLLs (via TARGET_RUNTIME_DLLS)..."
        )
endif()
