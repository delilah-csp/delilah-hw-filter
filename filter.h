#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE_IN 1024
#define BUF_SIZE_OUT 1024

struct delilah_array_in {
  uint64_t value[BUF_SIZE_IN];
};

struct delilah_array_out {
  uint64_t value[BUF_SIZE_OUT];
};

enum DELILAH_FILTER_OPS {
  DELILAH_FILTER_EQ,
  DELILAH_FILTER_NEQ,
  DELILAH_FILTER_LE,
  DELILAH_FILTER_GE,
  DELILAH_FILTER_BWI, /*BETWEEN inclusive:        [comp0,comp1]*/
};
