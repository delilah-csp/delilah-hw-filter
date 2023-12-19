#include "filter.h"

uint64_t filter(struct delilah_array *in, uint64_t *out, uint64_t num,
                uint64_t op, uint64_t comp1, uint64_t comp2) {
#pragma HLS INTERFACE m_axi port = in offset = slave bundle = gmem
#pragma HLS INTERFACE m_axi port = out offset = slave bundle = gmem
#pragma HLS INTERFACE s_axilite port = num bundle = control
#pragma HLS INTERFACE s_axilite port = op bundle = control
#pragma HLS INTERFACE s_axilite port = comp1 bundle = control
#pragma HLS INTERFACE s_axilite port = comp2 bundle = control
#pragma HLS INTERFACE s_axilite port = return bundle = control

  uint64_t c = 0, i, j;

  switch (op) {
  case DELILAH_FILTER_EQ:
  Vector_Loop_EQ:
    for (i = 0; i < num; i++) {
      struct delilah_array arr = in[i];
    Value_Loop_EQ:
      for (j = 0; j < 1024; j++) {
#pragma HLS UNROLL factor = 32
#pragma HLS PIPELINE
        if (arr.value[j] == comp1)
          out[c++] = arr.value[j];
      }
    }
    break;

  case DELILAH_FILTER_NEQ:
  Vector_Loop_NEQ:
    for (i = 0; i < num; i++) {
      struct delilah_array arr = in[i];
    Value_Loop_NEQ:
      for (j = 0; j < 1024; j++) {
#pragma HLS UNROLL factor = 32
#pragma HLS PIPELINE
        if (arr.value[j] != comp1)
          out[c++] = arr.value[j];
      }
    }
    break;

  case DELILAH_FILTER_LT:
  Vector_Loop_LT:
    for (i = 0; i < num; i++) {
      struct delilah_array arr = in[i];
    Value_Loop_LT:
      for (j = 0; j < 1024; j++) {
#pragma HLS UNROLL factor = 32
#pragma HLS PIPELINE
        if (arr.value[j] < comp1)
          out[c++] = arr.value[j];
      }
    }
    break;

  case DELILAH_FILTER_LE:
  Vector_Loop_LE:
    for (i = 0; i < num; i++) {
      struct delilah_array arr = in[i];
    Value_Loop_LE:
      for (j = 0; j < 1024; j++) {
#pragma HLS UNROLL factor = 32
#pragma HLS PIPELINE
        if (arr.value[j] <= comp1)
          out[c++] = arr.value[j];
      }
    }
    break;

  case DELILAH_FILTER_GT:
  Vector_Loop_GT:
    for (i = 0; i < num; i++) {
      struct delilah_array arr = in[i];
    Value_Loop_GT:
      for (j = 0; j < 1024; j++) {
#pragma HLS UNROLL factor = 32
#pragma HLS PIPELINE
        if (arr.value[j] > comp1)
          out[c++] = arr.value[j];
      }
    }
    break;

  case DELILAH_FILTER_GE:
  Vector_Loop_GE:
    for (i = 0; i < num; i++) {
      struct delilah_array arr = in[i];
    Value_Loop_GE:
      for (j = 0; j < 1024; j++) {
#pragma HLS UNROLL factor = 32
#pragma HLS PIPELINE
        if (arr.value[j] >= comp1)
          out[c++] = arr.value[j];
      }
    }
    break;

  case DELILAH_FILTER_BW:
  Vector_Loop_BW:
    for (i = 0; i < num; i++) {
      struct delilah_array arr = in[i];
    Value_Loop_BW:
      for (j = 0; j < 1024; j++) {
#pragma HLS UNROLL factor = 32
#pragma HLS PIPELINE
        if (arr.value[j] > comp1 && arr.value[j] < comp2)
          out[c++] = arr.value[j];
      }
    }
    break;

  case DELILAH_FILTER_BWI:
  Vector_Loop_BWI:
    for (i = 0; i < num; i++) {
      struct delilah_array arr = in[i];
    Value_Loop_BWI:
      for (j = 0; j < 1024; j++) {
#pragma HLS UNROLL factor = 32
#pragma HLS PIPELINE
        if (arr.value[j] >= comp1 && arr.value[j] <= comp2)
          out[c++] = arr.value[j];
      }
    }
    break;

  case DELILAH_FILTER_BWLI:
  Vector_Loop_BWLI:
    for (i = 0; i < num; i++) {
      struct delilah_array arr = in[i];
    Value_Loop_BWLI:
      for (j = 0; j < 1024; j++) {
#pragma HLS UNROLL factor = 32
#pragma HLS PIPELINE
        if (arr.value[j] >= comp1 && arr.value[j] < comp2)
          out[c++] = arr.value[j];
      }
    }
    break;

  case DELILAH_FILTER_BWHI:
  Vector_Loop_BWHI:
    for (i = 0; i < num; i++) {
      struct delilah_array arr = in[i];
    Value_Loop_BWHI:
      for (j = 0; j < 1024; j++) {
#pragma HLS UNROLL factor = 32
#pragma HLS PIPELINE
        if (arr.value[j] > comp1 && arr.value[j] <= comp2)
          out[c++] = arr.value[j];
      }
    }
    break;

  default:
    c = UINT64_MAX;
    break;
  }

  return c;
}
