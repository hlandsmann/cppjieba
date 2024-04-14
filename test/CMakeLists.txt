SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

ADD_EXECUTABLE(demojieba demo.cpp)
target_link_libraries(demojieba 
    PRIVATE
        cppjieba::cppjieba
)
ADD_EXECUTABLE(load_test load_test.cpp)
target_link_libraries(load_test
    PRIVATE
       cppjieba::cppjieba
)
# ADD_SUBDIRECTORY(unittest)
