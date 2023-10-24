#include <stdint.h>

enum DELILAH_FILTER_OPS {
  DELILAH_FILTER_EQ,
  DELILAH_FILTER_NEQ,
  DELILAH_FILTER_LT,
  DELILAH_FILTER_LE,
  DELILAH_FILTER_GT,
  DELILAH_FILTER_GE,
  DELILAH_FILTER_BW,   /*BETWEEN:                  (comp0,comp1)*/
  DELILAH_FILTER_BWI,  /*BETWEEN inclusive:        [comp0,comp1]*/
  DELILAH_FILTER_BWLI, /*BETWEEN low inclusive:    [comp0,comp1)*/
  DELILAH_FILTER_BWHI, /*BETWEEN high inclusive:   (comp0,comp1]*/
};
