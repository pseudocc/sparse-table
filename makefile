CC = gcc
LD = gcc
CFLAGS = -fpic
INCL = -I./include

TEST_OBJ = sparse-table.o \
	test/generic.o \
	test/macro.o \
	test/unit-test.o \

all: libsparse-table.so

libsparse-table.so: libsparse-table-i32.so
	cp $< $@

libsparse-table-%.so: sparse-table-%.o
	$(CC) $(INCL) -shared -o $@ $^

sparse-table-i8.o: sparse-table.c
	$(CC) $(CFLAGS) $(INCL) -c $< -o $@ -D__SPARSE_TABLE_TYPE=int8_t

sparse-table-i16.o: sparse-table.c
	$(CC) $(CFLAGS) $(INCL) -c $< -o $@ -D__SPARSE_TABLE_TYPE=int16_t

sparse-table-i32.o: sparse-table.c
	$(CC) $(CFLAGS) $(INCL) -c $< -o $@ -D__SPARSE_TABLE_TYPE=int32_t

sparse-table-i64.o: sparse-table.c
	$(CC) $(CFLAGS) $(INCL) -c $< -o $@ -D__SPARSE_TABLE_TYPE=int64_t

%.o: %.c
	$(CC) $(INCL) -c $< -o $@ -g

unit-test: $(TEST_OBJ)
	$(LD) -o $@ $^

clean:
	rm -f *.o *.so $(TEST_OBJ) unit-test

.PHONY: clean
