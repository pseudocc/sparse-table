#ifndef __SPARSE_TABLE_TYPE
#define __SPARSE_TABLE_TYPE int32_t
#endif

#include "generic.h"

typedef __SPARSE_TABLE_TYPE elem_t;
typedef __SPARSE_TABLE_SOURCE_TYPE source_t;

typedef elem_t (*method_t)(elem_t, elem_t);

struct opaque {
  method_t f;
  size_t N;
  sparse_table(elem_t) st;
};

sparse_table_t sparse_table_new(source_t* array, size_t n_elems, method_t method) {
  if (n_elems == 0)
    return NULL;
  int K = 64 - __builtin_clzll(n_elems);
  sparse_table_t inst = malloc(sizeof(method) + sizeof(n_elems) + sizeof(elem_t*) * n_elems);
  if (inst == NULL)
    return NULL;
  
  inst->f = method;
  inst->N = n_elems;
  sparse_table(elem_t) st = inst->st;

  for (size_t i = 0; i < n_elems; i++) {
    st[i] = malloc(sizeof(elem_t) * K);
    if (st[i] == NULL) {
      while (i--)
        free(st[i]);
      free(inst);
      return NULL;
    }
    st[i][0] = (elem_t)array[i];
  }

  for (int j = 1; j < K; j++)
    for (int i = 0; i + (1 << j) <= n_elems; i++)
      st[i][j] = method(st[i][j-1], st[i+(1<<(j-1))][j-1]);
  return inst;
}

void sparse_table_free(sparse_table_t inst) {
  if (inst == NULL)
    return;
  
  for (size_t i = 0; i < inst->N; i++) {
    free(inst->st[i]);
    inst->st[i] = NULL;
  }

  free(inst);
}

elem_t sparse_table_query(sparse_table_t inst, size_t l, size_t r) {
  int j = 63 - __builtin_clzll(r - l + 1);
  return inst->f(inst->st[l][j], inst->st[r-(1<<j)+1][j]);
}

elem_t sparse_table_accum(sparse_table_t inst, size_t l, size_t r, elem_t initial) {
  elem_t result = initial;
  int K = 63 - __builtin_clzll(inst->N);
  for (int j = K; j >= 0; j--) {
    if ((1 << j) <= r - l + 1) {
      result = inst->f(result, inst->st[l][j]);
      l += 1 << j;
    }
  }
  return result;
}