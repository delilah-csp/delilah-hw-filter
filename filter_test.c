#include "filter.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t filter(filter_t *in, filter_t *out, uint64_t num, uint64_t op,
                filter_t comp1, filter_t comp2);

int main() {

  filter_t *in = malloc(2 * BUF_SIZE * sizeof(filter_t));
  filter_t *out = malloc(2 * BUF_SIZE * sizeof(filter_t));

  printf("HLS Filter Example\n");
  printf("OP: EQ(2)\n");
  printf("Initial array: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, ...]\n");

  uint64_t i;
  for (i = 0; i < 2 * BUF_SIZE; i++)
    in[i] = i % 10;
  for (i = 0; i < 2 * BUF_SIZE; i++)
    out[i] = 0;

  uint64_t matches = filter(in, out, 2, 0, 2, 0);

  printf("Resulting array: [");
  for (i = 0; i < matches; i++) {
    printf("%ld, ", out[i]);
  }
  printf("NULL]\n");
  printf("There should be 8192 / 10 = 819 results. There is %ld.\n", matches);
}
