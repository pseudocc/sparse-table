#ifndef __SPARSE_TABLE_H
#define __SPARSE_TABLE_H

#include "./common.h"

typedef struct opaque* sparse_table_t;

#ifndef __SPARSE_TABLE_TYPE
#error "__SPARSE_TABLE_TYPE is not defined."
#endif

#ifndef __SPARSE_TABLE_SOURCE_TYPE
#define __SPARSE_TABLE_SOURCE_TYPE __SPARSE_TABLE_TYPE
#endif

#if __SPARSE_TABLE_TYPE == __SPARSE_TABLE_SOURCE_TYPE
#define __SPARSE_TABLE_TYPE_SUFFIX __SPARSE_TABLE_TYPE
#else
#define __SPARSE_TABLE_TYPE_SUFFIX
#endif

/**
 * Constructor
 **/

sparse_table_t sparse_table_new(
  __SPARSE_TABLE_SOURCE_TYPE* array,
  size_t n_elems,
  __SPARSE_TABLE_TYPE (*method)(__SPARSE_TABLE_TYPE, __SPARSE_TABLE_TYPE)
);

/**
 * Destructor
 **/

void sparse_table_free(sparse_table_t instance);


/**
 * Member functions
 **/

__SPARSE_TABLE_TYPE
sparse_table_query(sparse_table_t instance, size_t l, size_t r);

__SPARSE_TABLE_TYPE
sparse_table_accum(
  sparse_table_t instance,
  size_t l,
  size_t r,
  __SPARSE_TABLE_TYPE initial
);

#endif