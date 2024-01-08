#include "filter.h"

uint64_t filter(struct delilah_array_in *in, struct delilah_array_out *out,
                uint64_t num, uint64_t op, uint64_t comp1, uint64_t comp2) {
#pragma HLS INTERFACE m_axi port = in offset = slave bundle = gmem
#pragma HLS INTERFACE m_axi port = out offset = slave bundle = gmem
#pragma HLS INTERFACE s_axilite port = num bundle = control
#pragma HLS INTERFACE s_axilite port = op bundle = control
#pragma HLS INTERFACE s_axilite port = comp1 bundle = control
#pragma HLS INTERFACE s_axilite port = comp2 bundle = control
#pragma HLS INTERFACE s_axilite port = return bundle = control

  uint64_t c = 0, i, j;
  struct delilah_array_out buf;

  switch (op) {
  case DELILAH_FILTER_EQ:
  Vector_Loop_EQ:
    for (i = 0; i < num; i++) {
      struct delilah_array_in arr = in[i];
    Value_Loop_EQ:
      for (j = 0; j < BUF_SIZE_IN; j++) {
#pragma HLS UNROLL factor = 32
#pragma HLS PIPELINE
        if (arr.value[j] == comp1) {
          buf.value[c++ % BUF_SIZE_OUT] = arr.value[j];
          if (c % BUF_SIZE_OUT == 0) {
            out[c / BUF_SIZE_OUT] = buf;
          }
        }
      }
    }
    break;

  case DELILAH_FILTER_NEQ:
  Vector_Loop_NEQ:
    for (i = 0; i < num; i++) {
      struct delilah_array_in arr = in[i];
    Value_Loop_NEQ:
      for (j = 0; j < BUF_SIZE_IN; j++) {
#pragma HLS UNROLL factor = 32
#pragma HLS PIPELINE
        if (arr.value[j] != comp1) {
          buf.value[c++ % BUF_SIZE_OUT] = arr.value[j];
          if (c % BUF_SIZE_OUT == 0) {
            out[c / BUF_SIZE_OUT] = buf;
          }
        }
      }
    }
    break;

  case DELILAH_FILTER_LE:
  Vector_Loop_LE:
    for (i = 0; i < num; i++) {
      struct delilah_array_in arr = in[i];
    Value_Loop_LE:
      for (j = 0; j < BUF_SIZE_IN; j++) {
#pragma HLS UNROLL factor = 32
#pragma HLS PIPELINE
        if (arr.value[j] <= comp1) {
          buf.value[c++ % BUF_SIZE_OUT] = arr.value[j];
          if (c % BUF_SIZE_OUT == 0) {
            out[c / BUF_SIZE_OUT] = buf;
          }
        }
      }
    }
    break;

  case DELILAH_FILTER_GE:
  Vector_Loop_GE:
    for (i = 0; i < num; i++) {
      struct delilah_array_in arr = in[i];
    Value_Loop_GE:
      for (j = 0; j < BUF_SIZE_IN; j++) {
#pragma HLS UNROLL factor = 32
#pragma HLS PIPELINE
        if (arr.value[j] >= comp1) {
          buf.value[c++ % BUF_SIZE_OUT] = arr.value[j];
          if (c % BUF_SIZE_OUT == 0) {
            out[c / BUF_SIZE_OUT] = buf;
          }
        }
      }
    }
    break;

  case DELILAH_FILTER_BWI:
  Vector_Loop_BWI:
    for (i = 0; i < num; i++) {
      struct delilah_array_in arr = in[i];
    Value_Loop_BWI:
      for (j = 0; j < BUF_SIZE_IN; j++) {
#pragma HLS UNROLL factor = 32
#pragma HLS PIPELINE
        if (arr.value[j] >= comp1 && arr.value[j] <= comp2) {
          buf.value[c++ % BUF_SIZE_OUT] = arr.value[j];
          if (c % BUF_SIZE_OUT == 0) {
            out[c / BUF_SIZE_OUT] = buf;
          }
        }
      }
    }
    break;

  default:
    c = UINT64_MAX;
    break;
  }

  if ((c % BUF_SIZE_OUT) != 0)
    out[c / BUF_SIZE_OUT] = buf;

  return c;
}
