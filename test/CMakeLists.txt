file(GLOB_RECURSE TEST_SRC_FILE_LIST CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(unit_tests ${TEST_SRC_FILE_LIST})

target_link_libraries(unit_tests PRIVATE algorithm utility)
