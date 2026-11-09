AUX_SOURCE_DIRECTORY(. ALGORITHM_LIST)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${ALGORITHM_LIST} )

file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/include/algorithm/*.h)
ADD_LIBRARY(algorithm SHARED ${ALGORITHM_LIST} ${HEADER_FILES})


target_link_libraries(algorithm OpenMP::OpenMP_CXX)

# target_include_directories(algorithm
#         INTERFACE
#         ${CMAKE_SOURCE_DIR}/include/)
target_include_directories(algorithm PUBLIC ${CMAKE_SOURCE_DIR}/include)










