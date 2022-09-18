#include "./unit-test.h"

typedef struct testcase testcase_t;

struct testcase {
  char category[16];
  char name[16];
  int (*handler)();
};

#define DEFINE_CASE(type, name) { #type, #name, &name }

testcase_t cases[] = {
  DEFINE_CASE(generic, maxima),
  DEFINE_CASE(generic, xor),
  DEFINE_CASE(macro, minima),
  DEFINE_CASE(macro, sum)
};

int main(void) {
  int n_cases = sizeof(cases) / sizeof(testcase_t);
  int failed = 0;
  for (int i = 0; i < n_cases; i++) {
    testcase_t* c = &cases[i];
    printf("[%s] %s:\n", c->category, c->name);
    int error = c->handler();
    printf("\t%s\n", error ? "error" : "success");
    failed += error;
  }
  return failed;
}