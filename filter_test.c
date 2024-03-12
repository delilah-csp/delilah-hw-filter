#include "filter.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t filter(filter_t *in, filter_t *out, uint32_t num, uint8_t op,
                filter_t comp1, filter_t comp2);

int main() {

  filter_t *in = malloc(2 * BUF_SIZE * sizeof(filter_t));
  filter_t *out = malloc(2 * BUF_SIZE * sizeof(filter_t));

  printf("HLS Filter Example\n");
  printf("OP: EQ(2)\n");
  printf("Initial array: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, ...]\n");

  uint32_t i;
  for (i = 0; i < 2 * BUF_SIZE; i++)
    in[i] = i % 10;
  for (i = 0; i < 2 * BUF_SIZE; i++)
    out[i] = 0;

  uint32_t matches = filter(in, out, 2, 0, 2, 0);

  printf("Resulting array: [");
  for (i = 0; i < matches; i++) {
    printf("%d, ", out[i]);
  }
  printf("NULL]\n");
  printf("There should be 512 / 10 = 51 results. There is %d.\n", matches);
}
