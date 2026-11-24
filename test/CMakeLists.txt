file(GLOB_RECURSE TEST_SRC_FILE_LIST CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(unit_tests ${TEST_SRC_FILE_LIST} catch_amalgamated.cpp.txt)

# 让 .txt 文件按 C++ 编译
set_source_files_properties(catch_amalgamated.cpp.txt PROPERTIES LANGUAGE CXX)

target_link_libraries(unit_tests PRIVATE algorithm utility)
