#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 4096

enum DELILAH_FILTER_OPS {
  DELILAH_FILTER_EQ,
  DELILAH_FILTER_NEQ,
  DELILAH_FILTER_LE,
  DELILAH_FILTER_GE,
  DELILAH_FILTER_BWI, /*BETWEEN inclusive:        [comp0,comp1]*/
};
