![version-0.2](https://img.shields.io/badge/version-0.2-lightgrey)
![c99-compatible](https://img.shields.io/static/v1?logo=c&logoColor=lightgrey&color=green&label=99&message=compatible)

# metric
This project is a set of macros to do unit tests and benchmark code to measure any problem of your program can have.

You can read the documentation in the GitHub's Wiki in any of the following languages:
* [English](https://github.com/Silva97/metric/wiki/English-home)
* [Português](https://github.com/Silva97/metric/wiki/Portuguese-home)

## Usage
Just import the `metric.h` to your project and done! You can use the macros including this header and following
the instructions in the documentation.

### Example of a test function
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
  return 0;
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
