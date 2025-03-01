AUX_SOURCE_DIRECTORY(. UTILITY_LIST)
ADD_LIBRARY(utility ${UTILITY_LIST}) # 动态库

# 链接库image依赖于algorithm
#TARGET_LINK_LIBRARIES(utility algorithm)


