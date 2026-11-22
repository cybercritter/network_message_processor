# network_message_processor

A minimal C++ message processor project using CMake, GoogleTest, and optional
coverage instrumentation.

## Build and test

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

GoogleTest is fetched from its upstream repository during CMake configuration.

## Coverage

Coverage instrumentation is available with GCC and Clang:

```sh
cmake -S . -B build-coverage -DENABLE_COVERAGE=ON
cmake --build build-coverage
ctest --test-dir build-coverage --output-on-failure
gcovr --root . --html-details coverage.html
```

Install `gcovr` separately to generate the HTML report.
