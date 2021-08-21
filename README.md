![GitHub release (latest by date)](https://img.shields.io/github/v/release/Silva97/metric)
![c99-compatible](https://img.shields.io/static/v1?logo=c&logoColor=lightgrey&color=green&label=99&message=compatible)

# metric
metric is a framework with a set of macros to do unit tests and benchmark code.

You can read the documentation in the GitHub's Wiki in any of the following languages:
* [English](https://github.com/Silva97/metric/wiki/English-home)
* [Português](https://github.com/Silva97/metric/wiki/Portuguese-home)


This repository has [CMake] files to build, install and run tests on the project. The directory structure of a project using the metric
framework is:

* `include` | Directory with header files
* `src`     | Directory with source code
  * `arch`  | Architecture dependent source files
  * `arch/{arch_name}/include` | Header files to specific architecture
* `tests/feature` | Feature tests
* `tests/unit`    | Unit tests

By default CMake is configured to compile a project with C (`.c`) and Assembly (`.s`) source files. The `src/arch` directory
is expected to have architecture dependent source files. Inside the directory is expected to have a subdirectory with the name
of the target architecture and inside it the source code. Example: `src/arch/x86_64/source.c`

The possible names of architecture is `x86_64`, `i386`, `ia64`, `arm64` and any other name used in `uname -m` command.

[CMake]: https://cmake.org/

## Creating new project with metric
This repository is a template repository, so you can create a new repository using this template as base following the instructions:
* English: [Creating a repository from a template]
* Portuguese: [Criar um repositório a partir de um modelo]

In `CMakeLists.txt` update the [project] command to set the project's name, version and languages.

In `configuration.cmake` you can update the configurations about the project. Read the commentaries on the file.

[Creating a repository from a template]: https://docs.github.com/en/github/creating-cloning-and-archiving-repositories/creating-a-repository-on-github/creating-a-repository-from-a-template
[Criar um repositório a partir de um modelo]: https://docs.github.com/pt/github/creating-cloning-and-archiving-repositories/creating-a-repository-on-github/creating-a-repository-from-a-template
[project]: https://cmake.org/cmake/help/latest/command/project.html

## Using cmake
First of all, run `cmake .` in the project directory and CMake will generate the files to build the project.

### Build the project
```sh
$ cmake --build . -t output_bin
```

Or to build also the tests' binaries just remove the `-t` option.

### Install the project's binary
```sh
$ sudo cmake --install .
```

### Run all tests
```sh
$ cmake --build .
$ ctest
```

## Header usage
You can use the macros including `metric.h` header and following the instructions in the documentation.

### Example of a test module
```c
#include <stdio.h>
#include <inttypes.h>
#include "metric.h"

uint64_t fib(uint64_t n)
{
  if (n < 2) return n;
  return fib(n-1) + fib(n-2);
}

test_t test_fib(void)
{
  METRIC_ASSERT( fib(12) == 144  );
  METRIC_ASSERT( fib(17) == 1597 );
  METRIC_ASSERT( fib(1)  == 1    );

  METRIC_TEST_OK("");
}

int main(void)
{
  METRIC_TEST(test_fib);
  METRIC_TEST_END();
}
```

Output:

![test-output](https://i.imgur.com/D2jSbKm.png)

### Example of benchmarking
```c
#include <stdio.h>
#include <inttypes.h>
#include "metric.h"

uint64_t fib(uint64_t n)
{
  if (n < 2) return n;
  return fib(n-1) + fib(n-2);
}

int main(void)
{
  METRIC_START();

  METRIC_CALL(1, fib, 20);
  METRIC_CALL(5000, fib, 20);
  METRIC_CALL(1, fib, 40);

  METRIC_STOP("total_bench");
  return 0;
}
```

Output:

![measure-output](https://i.imgur.com/F6cvRjK.png)
