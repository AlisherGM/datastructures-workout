include(GoogleTest)

add_executable(test_map test_map.cpp)
target_link_libraries(test_map pthread googletest googletest_main)
<<<<<<< HEAD
add_test(test_map test_map)

add_executable(test_hashmap test_hashmap.cpp)
target_link_libraries(test_hashmap pthread googletest googletest_main)
add_test(test_hashmap test_hashmap)
=======
add_test(test_map test_map)
>>>>>>> aa062fe7f336ff682e3ccbaadb5cba5567ba6f89
