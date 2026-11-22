# network_message_processor

A minimal C11 message processor project using CMake, GoogleTest, and optional
coverage instrumentation.

## Build and test

The CMake presets require CMake 3.20 or newer.

```sh
cmake --preset debug
cmake --build --preset debug
ctest --preset test
```

For a Release build, use `release` in place of `debug`.

The library uses C11; the GoogleTest tests require a C++17 compiler. GoogleTest
is fetched from its upstream repository during CMake configuration.

## API

Include `message_processor.h` and link against `network_message_processor`.
`message_processor_process` copies exactly `message_size` bytes into a
caller-provided buffer and returns a status code. The buffer must have at
least `message_size` bytes; no terminating null byte is added. The input and
output may overlap. For an empty message, either pointer may be null.

## Formatting

The `.clang-format` configuration uses GNU style for C and C++ code. Run
`clang-format -i <file>` to format a source file.

## Static analysis

Install Cppcheck with its MISRA add-on and Python 3, then install the
recommended C/C++ Advanced Lint VS Code extension. It runs Cppcheck on save
with the MISRA C:2012 add-on. The POSIX editor wrapper skips files whose
basename ends in `_test` before the extension. Enable the extension's
workspace trust flag to allow its workspace-configured executable. To analyze
the C library from the command line:

```sh
cppcheck --std=c11 --enable=warning,style,performance,portability,information \
  --addon=misra -I include/network_message_processor src
```

Cppcheck's MISRA add-on implements only some MISRA C:2012 rules, and its
open-source distribution does not provide a CERT add-on. Additional analysis
is needed to assess MISRA or CERT compliance.

## Coverage

Coverage instrumentation is available with GCC and Clang:

```sh
cmake --preset coverage
cmake --build --preset coverage
ctest --preset coverage
cmake --build --preset coverage --target coverage
```

The `coverage` target uses `gcovr.cfg`, which excludes build and coverage
directories and writes the HTML report to `coverage/index.html`. Install
`gcovr` separately to generate the report.
