#ifndef __SPARSE_TABLE_H
#error "sparse-table/common.h should only be included by " \
  "sparse-table/generic.h or sparse-table/macro.h!"
#endif

#ifndef __SPARSE_TABLE_COMMON_H
#define __SPARSE_TABLE_COMMON_H

#include <stdlib.h>

#define sparse_table(type) type**

#endif