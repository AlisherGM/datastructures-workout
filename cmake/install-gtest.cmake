ExternalProject_Add(googletest-build
        GIT_TAG           release-1.10.0
        GIT_REPOSITORY    https://github.com/google/googletest.git
        GIT_SHALLOW       true
        GIT_PROGRESS      true

        SOURCE_DIR        "${CMAKE_BINARY_DIR}/googletest/src"
        BINARY_DIR        "${CMAKE_BINARY_DIR}/googletest/build"
        INSTALL_DIR       "${CMAKE_BINARY_DIR}/googletest/install"

        CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/googletest/install/
        )

list(APPEND DEPS_LIST googletest-build)
add_library(googletest STATIC IMPORTED)
set_target_properties(googletest PROPERTIES IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/googletest/install/lib/libgtest.a)
add_library(googletest_main STATIC IMPORTED)
set_target_properties(googletest_main PROPERTIES IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/googletest/install/lib/libgtest_main.a)
add_dependencies(googletest googletest-build)
add_dependencies(googletest_main googletest-build)
set(GOOGLE_TEST_LIBS googletest googletest_main)