#include "filter.h"

uint64_t filter(uint64_t *in, uint64_t *out, uint64_t num, uint64_t op,
                uint64_t comp1, uint64_t comp2) {
#pragma HLS INTERFACE m_axi port = in offset = slave bundle = gmem
#pragma HLS INTERFACE m_axi port = out offset = slave bundle = gmem
#pragma HLS INTERFACE s_axilite port = num bundle = control
#pragma HLS INTERFACE s_axilite port = op bundle = control
#pragma HLS INTERFACE s_axilite port = comp1 bundle = control
#pragma HLS INTERFACE s_axilite port = comp2 bundle = control
#pragma HLS INTERFACE s_axilite port = return bundle = control

  uint64_t c = 0, // Overall result counter
      k = 0,      // Vector result counter
      i,          // Vector iterator
      j;          // Value iterator

  uint64_t in_buf[BUF_SIZE];
  uint64_t out_buf[BUF_SIZE];

  switch (op) {
  case DELILAH_FILTER_EQ:
  Vector_Loop_EQ:
    for (i = 0; i < num; i++) {
      memcpy(in_buf, &in[i * BUF_SIZE], BUF_SIZE * sizeof(uint64_t));
    Value_Loop_EQ:
      for (j = 0; j < BUF_SIZE; j++) {
#pragma HLS UNROLL factor = 128
#pragma HLS PIPELINE
        if (in_buf[j] == comp1)
          out_buf[k++] = in_buf[j];
      }
      if (k <=
          BUF_SIZE) // This will always be true, but helps the compiler optimise
        memcpy(out + c, out_buf, k * sizeof(uint64_t));
      c += k;
      k = 0;
    }
    break;

  case DELILAH_FILTER_NEQ:
  Vector_Loop_NEQ:
    for (i = 0; i < num; i++) {
      memcpy(in_buf, &in[i * BUF_SIZE], BUF_SIZE * sizeof(uint64_t));
    Value_Loop_NEQ:
      for (j = 0; j < BUF_SIZE; j++) {
#pragma HLS UNROLL factor = 128
#pragma HLS PIPELINE
        if (in_buf[j] != comp1)
          out_buf[k++] = in_buf[j];
      }
      if (k <=
          BUF_SIZE) // This will always be true, but helps the compiler optimise
        memcpy(out + c, out_buf, k * sizeof(uint64_t));
      c += k;
      k = 0;
    }
    break;

  case DELILAH_FILTER_LE:
  Vector_Loop_LE:
    for (i = 0; i < num; i++) {
      memcpy(in_buf, &in[i * BUF_SIZE], BUF_SIZE * sizeof(uint64_t));
    Value_Loop_LE:
      for (j = 0; j < BUF_SIZE; j++) {
#pragma HLS UNROLL factor = 128
#pragma HLS PIPELINE
        if (in_buf[j] <= comp1)
          out_buf[k++] = in_buf[j];
      }
      if (k <=
          BUF_SIZE) // This will always be true, but helps the compiler optimise
        memcpy(out + c, out_buf, k * sizeof(uint64_t));
      c += k;
      k = 0;
    }
    break;

  case DELILAH_FILTER_GE:
  Vector_Loop_GE:
    for (i = 0; i < num; i++) {
      memcpy(in_buf, &in[i * BUF_SIZE], BUF_SIZE * sizeof(uint64_t));
    Value_Loop_GE:
      for (j = 0; j < BUF_SIZE; j++) {
#pragma HLS UNROLL factor = 128
#pragma HLS PIPELINE
        if (in_buf[j] >= comp1)
          out_buf[k++] = in_buf[j];
      }
      if (k <=
          BUF_SIZE) // This will always be true, but helps the compiler optimise
        memcpy(out + c, out_buf, k * sizeof(uint64_t));
      c += k;
      k = 0;
    }
    break;

  case DELILAH_FILTER_BWI:
  Vector_Loop_BWI:
    for (i = 0; i < num; i++) {
      memcpy(in_buf, &in[i * BUF_SIZE], BUF_SIZE * sizeof(uint64_t));
    Value_Loop_BWI:
      for (j = 0; j < BUF_SIZE; j++) {
#pragma HLS UNROLL factor = 128
#pragma HLS PIPELINE
        if (in_buf[j] >= comp1 && in_buf[j] <= comp2)
          out_buf[k++] = in_buf[j];
      }
      if (k <=
          BUF_SIZE) // This will always be true, but helps the compiler optimise
        memcpy(out + c, out_buf, k * sizeof(uint64_t));
      c += k;
      k = 0;
    }
    break;

  default:
    c = UINT64_MAX;
    break;
  }

  return c;
}
