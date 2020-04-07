#ifndef _METRIC_H
#define _METRIC_H

#include <stdio.h>
#include <string.h>
#include <time.h>


typedef const char * test_t;


#ifdef NDEBUG

#define METRIC_DISPLAY(name, start, stop) 
#define METRIC_START() 
#define METRIC_STOP(name)
#define METRIC_CALL(call, times) 
#define METRIC_TEST_OK(msg) 
#define METRIC_TEST_FAIL(msg) 
#define METRIC_TEST(test) 
#define METRIC_ASSERT(expr)
#define METRIC_ASSERT_ARRAY(arr1, arr2, size)
#define METRIC_ASSERT_STRING(str1, str2)

#else

#ifdef ANSI_COLORS

#define AC_R "\x1b[31;1m"
#define AC_G "\x1b[32;1m"
#define AC_Y "\x1b[33;1m"
#define AC_B "\x1b[34;1m"
#define AC_W "\x1b[37;1m"
#define AC_N "\x1b[0m"

#else

#define AC_R
#define AC_G
#define AC_Y
#define AC_B
#define AC_W
#define AC_N

#endif /* ANSI_COLORS */


#define METRIC_DISPLAY(name, start, stop)                    \
  printf("<" AC_Y "BENCH" AC_N "> " __FILE__ ": " name  "\n"  \
    "        %lld clocks, %.8lf secs\n",                     \
    (long long int) (stop - start),                           \
    ( (double) stop - start ) / CLOCKS_PER_SEC)

#define METRIC_START() { \
  clock_t metric_clock_start = clock()

#define METRIC_STOP(name)                            \
  METRIC_DISPLAY(name, metric_clock_start, clock());  \
}


#define METRIC_CALL(call, times) {                                 \
  clock_t metric_clock_start = clock();                             \
  for (int metric_count = 0; metric_count < times; metric_count++) \
    call;                                                           \
  METRIC_DISPLAY(#call " x " #times, metric_clock_start, clock()); \
}

/*** Test's macro ***/

#define METRIC_TEST_OK(msg) \
  return "[" AC_G " OK " AC_N "] " msg

#define METRIC_TEST_FAIL(msg) \
  return "[" AC_R "FAIL" AC_N "] " msg 

#define METRIC_TEST(test)                                                    \
  printf("<" AC_B "TEST" AC_N "> " __FILE__ ":%d: " AC_W #test AC_N "\n%s\n", \
    __LINE__,                                                                \
    test())

#define METRIC_ASSERT(expr)                                          \
  if ( !(expr) ) METRIC_TEST_FAIL("Assertion is false: `" #expr "'")

#define METRIC_ASSERT_ARRAY(arr1, arr2, size)                         \
  if ( memcmp(arr1, arr2, size) )                                      \
    METRIC_TEST_FAIL("Array `" #arr1 "' is not equal to `" #arr2 "'")

#define METRIC_ASSERT_STRING(str1, str2)                               \
  if ( strcmp(str1, str2) )                                             \
    METRIC_TEST_FAIL("String `" #str1 "' is not equal to `" #str2 "'")


#endif /* NDEBUG */

#endif /* _METRIC_H */