#include "generic/i32.h"
#include "./unit-test.h"

int calc_max_i32(int l, int r) {
  return l > r ? l : r;
}

int maxima() {
  int array[] = {
    10, 20, 35, 11, 28,  4, 30, 16,
    31, 31, 10, 32, 32, 31, 33, 14,
    12,  2, 33, 13, 34, 12, 16,  9,
    23, 22
  };
  int n = sizeof(array) / sizeof(int);
  sparse_table_t st = sparse_table_new(array, n, &calc_max_i32);

  int ranges[][2] = {
    {0, 25},
    {10, 19},
    {0, 9},
    {13, 14},
    {8, 15}
  };

  for (int i = 0; i < sizeof(ranges) / sizeof(int[2]); i++) {
    int l = ranges[i][0];
    int r = ranges[i][1];

    int bf_max = -1;
    for (int j = l; j <= r; j++)
      bf_max = calc_max_i32(bf_max, array[j]);

    int st_max = sparse_table_query(st, l, r);
    if (bf_max != st_max) {
      printf("[%d, %d]:\n\texpected:%d\n\tactual:%d\n", l, r, bf_max, st_max);
      return 1;
    }
  }

  return 0;
}

int calc_xor_i32(int l, int r) {
  return l ^ r;
}

int xor() {
  int array[] = {
    28,  5, 16, 13, 15, 11,  1,  7,
    13, 15,  5, 15, 39, 24, 25, 39,
    39,  4, 20, 28, 30, 29, 22, 24,
    10, 19, 11
  };
  int n = sizeof(array) / sizeof(int);
  sparse_table_t st = sparse_table_new(array, n, &calc_xor_i32);

  int ranges[][2] = {
    {0, 26},
    {10, 19},
    {0, 10},
    {13, 14},
    {8, 16}
  };

  for (int i = 0; i < sizeof(ranges) / sizeof(int[2]); i++) {
    int l = ranges[i][0];
    int r = ranges[i][1];

    int bf_result = 0;
    for (int j = l; j <= r; j++)
      bf_result = calc_xor_i32(bf_result, array[j]);

    int st_result = sparse_table_accum(st, l, r, 0);
    if (bf_result != st_result) {
      printf("[%d, %d]:\n\texpected:%d\n\tactual:%d\n", l, r, bf_result, st_result);
      return 1;
    }
  }

  return 0;
}