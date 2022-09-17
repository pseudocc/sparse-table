#include <stdio.h>
#include <stdlib.h>
#include "./sparse-table-test.h"

int _min(int l, int r) {
  return l < r ? l : r;
}

size_t _sum(size_t l, size_t r) {
  return l + r;
}

int minima() {
  int array[] = {
    10, 30, 27, 39, 29, 19,  4,
    31, 29, 15, 30, 14,  2, 24,
    9, 26, 39, 36,  0, 29
  };
  int n = sizeof(array) / sizeof(int);
  sparse_table(int) st = sparse_table_new(int, array, n, &_min);

  int ranges[][2] = {
    {0, 19},
    {10, 19},
    {0, 9},
    {3, 4},
    {8, 15}
  };

  for (int i = 0; i < sizeof(ranges) / sizeof(int[2]); i++) {
    int l = ranges[i][0];
    int r = ranges[i][1];

    int bf_min = 0xff;
    for (int j = l; j <= r; j++)
      bf_min = _min(bf_min, array[j]);

    int st_min = sparse_table_query(st, l, r);
    if (bf_min != st_min) {
      printf("[%d, %d]:\n\texpected:%d\n\tactual:%d\n", l, r, bf_min, st_min);
      return 1;
    }
  }

  return 0;
}

int sum() {
  int array[] = {
    14, 25, 10, 10, 28, 28,  9,
    21, 18, 26, 20, 22, 27, 26,
    3, 18, 16, 39,  8, 14, 22
  };
  int n = sizeof(array) / sizeof(int);
  sparse_table(size_t) st = sparse_table_new(size_t, array, n, &_sum);
  
  int ranges[][2] = {
    {0, 20},
    {13, 19},
    {0, 7},
    {9, 10},
    {7, 14}
  };

  for (int i = 0; i < sizeof(ranges) / sizeof(int[2]); i++) {
    int l = ranges[i][0];
    int r = ranges[i][1];

    size_t bf_sum = 0;
    for (int j = l; j <= r; j++)
      bf_sum = _sum(bf_sum, array[j]);

    size_t st_sum = sparse_table_accum(st, l, r, 0);
    if (bf_sum != st_sum) {
      printf("[%d, %d]:\n\texpected:%lu\n\tactual:%lu\n", l, r, bf_sum, st_sum);
      return 1;
    }
  }

  return 0;
}

int main(void) {
  int n_cases = sizeof(cases) / sizeof(testcase_t);
  int failed = 0;
  for (int i = 0; i < n_cases; i++) {
    testcase_t* c = &cases[i];
    printf("%s:\n", c->name);
    int error = c->handler();
    printf("\t%s\n", error ? "error" : "success");
    failed += error;
  }
  return failed;
}