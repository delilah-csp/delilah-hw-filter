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
    uint64_t *lin = in + 1024 * i;
    for (uint64_t j = 0; j < 1024; j++) {
      switch (op) {
      case DELILAH_FILTER_EQ:
        if (lin[j] == comp1)
          out[c++] = lin[j];
        break;
      case DELILAH_FILTER_NEQ:
        if (lin[j] != comp1)
          out[c++] = lin[j];
        break;
      case DELILAH_FILTER_LT:
        if (lin[j] < comp1)
          out[c++] = lin[j];
        break;
      case DELILAH_FILTER_LE:
        if (lin[j] <= comp1)
          out[c++] = lin[j];
        break;
      case DELILAH_FILTER_GT:
        if (lin[j] > comp1)
          out[c++] = lin[j];
        break;
      case DELILAH_FILTER_GE:
        if (lin[j] >= comp1)
          out[c++] = lin[j];
        break;
      case DELILAH_FILTER_BW:
        if (lin[j] > comp1 && in[j] < comp2)
          out[c++] = lin[j];
        break;
      case DELILAH_FILTER_BWI:
        if (lin[j] >= comp1 && in[j] <= comp2)
          out[c++] = lin[j];
        break;
      case DELILAH_FILTER_BWLI:
        if (lin[j] >= comp1 && in[j] < comp2)
          out[c++] = lin[j];
        break;
      case DELILAH_FILTER_BWHI:
        if (lin[j] > comp1 && in[j] <= comp2)
          out[c++] = lin[j];
        break;
      default:
        c = UINT64_MAX;
        break;
      }
    }
  }

  return c;
}
