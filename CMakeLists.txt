cmake_minimum_required ( VERSION 3.14 )

project ( network_message_processor VERSION 0.1.0 LANGUAGES C CXX )

set ( CMAKE_C_STANDARD 11 )
set ( CMAKE_C_STANDARD_REQUIRED ON )
set ( CMAKE_C_EXTENSIONS OFF )

option ( ENABLE_COVERAGE "Enable compiler coverage instrumentation" OFF )

if ( ENABLE_COVERAGE )
    if ( NOT CMAKE_C_COMPILER_ID MATCHES "GNU|Clang"
         OR NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang" )
        message ( FATAL_ERROR "Coverage is only supported with GCC or Clang" )
    endif ()
endif ()
find_package ( PkgConfig REQUIRED )
pkg_check_modules ( SAFEC REQUIRED IMPORTED_TARGET libsafec )

add_library ( network_message_processor
    src/message_processor.c
)
target_include_directories ( network_message_processor
    PUBLIC include/network_message_processor
)
target_compile_features ( network_message_processor PUBLIC c_std_11 )
target_link_libraries ( network_message_processor PUBLIC PkgConfig::SAFEC )

include ( FetchContent )
FetchContent_Declare (
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
set ( gtest_force_shared_crt ON CACHE BOOL "" FORCE )
FetchContent_MakeAvailable ( googletest )

enable_testing ()
add_executable ( network_message_processor_tests
    tests/message_processor_test.cpp
)
target_compile_features ( network_message_processor_tests PRIVATE cxx_std_17 )
target_link_libraries ( network_message_processor_tests
    PRIVATE network_message_processor GTest::gtest_main
)
include ( GoogleTest )
gtest_discover_tests ( network_message_processor_tests )

if ( ENABLE_COVERAGE )
    target_compile_options ( network_message_processor PRIVATE --coverage -O0 -g )
    target_compile_options ( network_message_processor_tests PRIVATE --coverage -O0 -g )
    target_link_options ( network_message_processor_tests PRIVATE --coverage )

    add_custom_target ( coverage
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_SOURCE_DIR}/coverage"
        COMMAND gcovr --config "${CMAKE_CURRENT_SOURCE_DIR}/gcovr.cfg"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Generating coverage report"
        VERBATIM
    )
endif ()
