include(GoogleTest)

add_executable(test_map test_map.cpp)
target_link_libraries(test_map pthread googletest googletest_main)
add_test(test_map test_map)