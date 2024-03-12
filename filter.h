#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 256

typedef uint32_t filter_t;

enum DELILAH_FILTER_OPS {
  DELILAH_FILTER_EQ,
#ifdef DELILAH_FILTER_ADVANCED
  DELILAH_FILTER_NEQ,
  DELILAH_FILTER_LE,
  DELILAH_FILTER_GE,
  DELILAH_FILTER_BWI, /*BETWEEN inclusive:        [comp0,comp1]*/
#endif
};
