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

  uint64_t c = 0;
  for (uint64_t i = 0; i < num; i++) {
    switch (op) {
    case DELILAH_FILTER_EQ:
      if (in[i] == comp1)
        out[c++] = in[i];
      break;
    case DELILAH_FILTER_NEQ:
      if (in[i] != comp1)
        out[c++] = in[i];
      break;
    case DELILAH_FILTER_LT:
      if (in[i] < comp1)
        out[c++] = in[i];
      break;
    case DELILAH_FILTER_LE:
      if (in[i] <= comp1)
        out[c++] = in[i];
      break;
    case DELILAH_FILTER_GT:
      if (in[i] > comp1)
        out[c++] = in[i];
      break;
    case DELILAH_FILTER_GE:
      if (in[i] >= comp1)
        out[c++] = in[i];
      break;
    case DELILAH_FILTER_BW:
      if (in[i] > comp1 && in[i] < comp2)
        out[c++] = in[i];
      break;
    case DELILAH_FILTER_BWI:
      if (in[i] >= comp1 && in[i] <= comp2)
        out[c++] = in[i];
      break;
    case DELILAH_FILTER_BWLI:
      if (in[i] >= comp1 && in[i] < comp2)
        out[c++] = in[i];
      break;
    case DELILAH_FILTER_BWHI:
      if (in[i] > comp1 && in[i] <= comp2)
        out[c++] = in[i];
      break;
    default:
      c = UINT64_MAX;
      break;
    }
  }

  return c;
}
