#ifndef __SPARSE_TABLE_TEST_H
#define __SPARSE_TABLE_TEST_H

#include "../include/function-macro.h"

typedef struct testcase testcase_t;

struct testcase {
  char name[20];
  int (*handler)();
};

int minima();
int sum();

#define DEFINE_CASE(name) { #name, &name }
testcase_t cases[] = {
  DEFINE_CASE(minima),
  DEFINE_CASE(sum)
};

#endif