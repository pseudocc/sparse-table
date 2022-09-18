#ifndef __SPARSE_TABLE_H
#define __SPARSE_TABLE_H

#include "./common.h"

/**
 * Constructor
 **/

#define sparse_table_new(type, array, n, method)                \
  ({                                                            \
    void* vp;                                                   \
    sparse_table(type) st;                                      \
    sparse_table(type) inst;                                    \
    typeof(array) source = array;                               \
    type (*f)(type, type) = method;                             \
    size_t N = (size_t)n;                                       \
    if (N == 0)                                                 \
      goto RETURN_NULL;                                         \
    int K = 64 - __builtin_clzll(N);                            \
    vp = malloc(sizeof(f) + sizeof(N) + sizeof(type*) * N);     \
    if (vp == NULL)                                             \
      goto RETURN_NULL;                                         \
    inst = vp;                                                  \
    *(void**)vp = f;                                            \
    vp += sizeof(f);                                            \
    *(size_t*)vp = N;                                           \
    vp += sizeof(N);                                            \
    st = vp;                                                    \
    for (size_t i = 0; i < N; i++) {                            \
      st[i] = malloc(sizeof(type) * K);                         \
      if (st[i] == NULL) {                                      \
        while (i--)                                             \
          free(st[i]);                                          \
        free(inst);                                             \
        goto RETURN_NULL;                                       \
      }                                                         \
      st[i][0] = (type)source[i];                               \
    }                                                           \
    for (int j = 1; j < K; j++)                                 \
      for (int i = 0; i + (1 << j) <= N; i++)                   \
        st[i][j] = f(st[i][j-1], st[i+(1<<(j-1))][j-1]);        \
    goto RETURN_INST;                                           \
RETURN_NULL:                                                    \
    inst = NULL;                                                \
RETURN_INST:                                                    \
    inst;                                                       \
   })

/**
 * Destructor
 **/

#define sparse_table_free(inst)                                 \
  do {                                                          \
    typeof(**inst) (*f)(typeof(**inst), typeof(**inst));        \
    void* alloc_p = inst;                                       \
    void* vp = alloc_p + sizeof(f);                             \
    size_t N = *(size_t*)vp;                                    \
    typeof(inst) st = vp + sizeof(N);                           \
    for (size_t i = 0; i < N; i++)                              \
      free(st[i]);                                              \
    free(alloc_p);                                              \
  } while (0)

/**
 * Member functions
 **/

#define sparse_table_query(inst, l, r)                          \
  ({                                                            \
    typeof(**inst) (*f)(typeof(**inst), typeof(**inst));        \
    void* vp = inst;                                            \
    f = *(void**)vp;                                            \
    vp += sizeof(f);                                            \
    typeof(inst) st = vp + sizeof(size_t);                      \
    int j = 63 - __builtin_clzll(r - l + 1);                    \
    f(st[l][j], st[r-(1<<j)+1][j]);                             \
   })

#define sparse_table_accum(inst, l, r, initial)                 \
  ({                                                            \
    typeof(**inst) result = initial;                            \
    typeof(**inst) (*f)(typeof(**inst), typeof(**inst));        \
    size_t L = l, R = r;                                        \
    void* vp = inst;                                            \
    f = *(void**)vp;                                            \
    vp += sizeof(f);                                            \
    size_t N = *(size_t*)vp;                                    \
    int K = 63 - __builtin_clzll(N);                            \
    typeof(inst) st = vp + sizeof(size_t);                      \
    for (int j = K; j >= 0; j--) {                              \
      if ((1 << j) <= R - L + 1) {                              \
        result = f(result, st[L][j]);                           \
        L += 1 << j;                                            \
      }                                                         \
    }                                                           \
    result;                                                     \
   })

#endif

