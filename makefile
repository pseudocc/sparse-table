CC = gcc
CFLAGS = -I./include -fpic

all: libsparse-table.so

libsparse-table.so: libsparse-table-i32.so
	cp $< $@

libsparse-table-%.so: sparse-table-%.o
	$(CC) -shared -o $@ $^

sparse-table-i8.o: sparse-table.c
	$(CC) $(CFLAGS) -c $< -o $@ -D__SPARSE_TABLE_TYPE=int8_t

sparse-table-i16.o: sparse-table.c
	$(CC) $(CFLAGS) -c $< -o $@ -D__SPARSE_TABLE_TYPE=int16_t

sparse-table-i32.o: sparse-table.c
	$(CC) $(CFLAGS) -c $< -o $@ -D__SPARSE_TABLE_TYPE=int32_t

sparse-table-i64.o: sparse-table.c
	$(CC) $(CFLAGS) -c $< -o $@ -D__SPARSE_TABLE_TYPE=int64_t

clean:
	rm -f *.o *.so

.PHONY: clean
