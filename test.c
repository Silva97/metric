#include <inttypes.h>
#include "metric.h"

test_t test_array_ok(void)
{
  int arr1[] = {1, 2, 3};
  int arr2[] = {1, 2, 3};

  METRIC_ASSERT_ARRAY(arr1, arr2, sizeof arr1);

  METRIC_TEST_OK("");
}

test_t test_array_fail(void)
{
  int arr1[] = {1, 2, 3};
  int arr2[] = {1, 2, 9};

  METRIC_ASSERT_ARRAY(arr1, arr2, sizeof arr1);

  METRIC_TEST_OK("");
}

test_t test_string_ok(void)
{
  char str1[] = "Hello!";
  char str2[] = "Hello!";

  METRIC_ASSERT_STRING(str1, str2);

  METRIC_TEST_OK("");
}

test_t test_string_fail(void)
{
  char str1[] = "Hello!";
  char str2[] = "Hello!!";

  METRIC_ASSERT_STRING(str1, str2);

  METRIC_TEST_OK("");
}

test_t test_expr_ok(void)
{
  volatile int x = 42;

  METRIC_ASSERT(x == 42);

  METRIC_TEST_OK("Meaning of life.");
}

test_t test_expr_fail(void)
{
  volatile int x = 42;

  METRIC_ASSERT(x < 42);

  METRIC_TEST_OK("Not have a meaning.");
}

test_t test_custom_ok(void)
{
  if (!test_custom_ok) {
    METRIC_TEST_FAIL("Where am i?");
  }

  METRIC_TEST_OK("Hi me!");
}

test_t test_custom_fail(void)
{
  volatile _Bool life = 0;

  if (!life) {
    METRIC_TEST_FAIL("I have no life.");
  }

  METRIC_TEST_OK(":)");
}


// For benchmark example //

uint64_t fibrec(uint64_t n)
{
  if (n < 2) return n;
  return fibrec(n-1) + fibrec(n-2);
}

test_t test_fibrec(void)
{
  METRIC_ASSERT( fibrec(12) == 144  );
  METRIC_ASSERT( fibrec(17) == 1597 );
  METRIC_ASSERT( fibrec(1)  == 1    );

  METRIC_TEST_OK("");
}

int main(void)
{
  // Unit-tests //
  METRIC_TEST(test_array_ok);
  METRIC_TEST(test_array_fail);
  METRIC_TEST(test_string_ok);
  METRIC_TEST(test_string_fail);
  METRIC_TEST(test_expr_ok);
  METRIC_TEST(test_expr_fail);
  METRIC_TEST(test_custom_ok);
  METRIC_TEST(test_custom_fail);
  METRIC_TEST(test_fibrec);

  // Benchmark //
  METRIC_START();

  METRIC_CALL(fibrec(20), 1);
  METRIC_CALL(fibrec(20), 5000);
  METRIC_CALL(fibrec(40), 1);

  METRIC_STOP("total_bench");
  return 0;
}
