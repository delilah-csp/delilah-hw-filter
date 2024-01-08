#include "filter.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t filter(struct delilah_array_in *in, struct delilah_array_out *out,
                uint64_t num, uint64_t op, uint64_t comp1, uint64_t comp2);

int main() {

  struct delilah_array_in *in = malloc(2 * 1024 * sizeof(uint64_t));
  struct delilah_array_out *out = malloc(2 * 1024 * sizeof(uint64_t));

  printf("HLS Filter Example\n");
  printf("OP: EQ(2)\n");
  printf("Initial array: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, ...]\n");

  uint64_t i;
  for (i = 0; i < 2 * 1024; i++)
    in->value[i] = i % 10;
  for (i = 0; i < 2 * 1024; i++)
    out->value[i] = 0;

  uint64_t matches = filter(in, out, 2, 0, 2, 0);

  printf("Resulting array: [");
  for (i = 0; i < matches; i++) {
    printf("%ld, ", out[i / BUF_SIZE_OUT].value[i % BUF_SIZE_OUT]);
  }
  printf("NULL]\n");
  printf("There should be 2048 / 10 + 1 = 205 results. There is %ld.\n",
         matches);
}
