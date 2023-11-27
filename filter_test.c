#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t filter(uint64_t *in, uint64_t *out, uint64_t num, uint64_t op,
                uint64_t comp1, uint64_t comp2);

int main() {

  uint64_t *in = malloc(2048 * sizeof(uint64_t));
  uint64_t *out = malloc(2048 * sizeof(uint64_t));

  printf("HLS Filter Example\n");
  printf("OP: EQ(2)\n");
  printf("Initial array: [0,1,2,3,4,5,6,7,8,9,0,1,2,3,...]\n");

  uint64_t i;
  for (i = 0; i < 2048; i++)
    in[i] = i % 10;
  for (i = 0; i < 2048; i++)
    out[i] = 0;

  uint64_t matches = filter(in, out, 2, 0, 2, 0);

  printf("Resulting array: [");
  for (i = 0; i < matches; i++) {
    printf("%ld, ", out[i]);
  }
  printf("NULL]\n");
  printf("There should be 2048 / 10 + 1 = 205 results. There is %ld.\n",
         matches);
}
