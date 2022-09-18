# SPARSE TABLE

Sparse table is a data structure for fast queries on a static data set.

## Interfaces

1. Function-like Macros

2. Shared Library

Both these 2 ways share almost the same interfaces:

- `sparse_table_new`
    create the sparse_table instance.

    time complexity: O(n * log(n))
    space complexity: O(n)

    parameters:
    - type: (function-like macro only) element type of the sparse table.
    - array: the static data set.
    - n: number of elements in array.
    - method: function pointer, like: min, max, gcd, sum, etc..

- `sparse_table_free`
    free all the resources created by `sparse_table_new`.

    parameter:
    - inst: the sparse\_table instance.

- `sparse_table_query`
    query the result for range [l, r]. operation should not cares overlapping
    ranges for quick calculation, like: min, max, gcd.

    time complexity: O(1)

    parameter:
    - inst: the sparse\_table instance.
    - l: lower bound.
    - r: upper bound.

- `sparse_table_accum`
    accumulate the result for range [l, r]. this is supposed to calculate sum or
    other arithmetics or bitwise operations.

    time complexity: O(log(n))

    parameter:
    - inst: the sparse\_table instance.
    - l: lower bound.
    - r: upper bound.
    - initial: initial value for the accumulation.

**BE AWARE:** for memeber function `query` and `accum`, parameter `l` and `r` are
not validated. when `l > r` the return value will be non-sense.
