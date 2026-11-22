cmake_minimum_required(VERSION 3.14)

project(network_message_processor VERSION 0.1.0 LANGUAGES CXX)

option(ENABLE_COVERAGE "Enable compiler coverage instrumentation" OFF)

if(ENABLE_COVERAGE)
    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        message(FATAL_ERROR "Coverage is only supported with GCC or Clang")
    endif()
endif()

add_library(network_message_processor
    src/message_processor.cpp
)
target_include_directories(network_message_processor
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_features(network_message_processor PUBLIC cxx_std_17)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(network_message_processor_tests
    tests/message_processor_test.cpp
)
target_link_libraries(network_message_processor_tests
    PRIVATE network_message_processor GTest::gtest_main
)
if(ENABLE_COVERAGE)
    target_compile_options(network_message_processor PRIVATE --coverage -O0 -g)
    target_compile_options(network_message_processor_tests PRIVATE --coverage -O0 -g)
    target_link_options(network_message_processor_tests PRIVATE --coverage)
endif()

include(GoogleTest)
gtest_discover_tests(network_message_processor_tests)
