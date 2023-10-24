#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t filter(uint64_t *in, uint64_t *out, uint64_t num, uint64_t op,
                uint64_t comp1, uint64_t comp2);

int main() {

  uint64_t *in = malloc(9 * sizeof(uint64_t));
  uint64_t *out = malloc(9 * sizeof(uint64_t));

  printf("HLS Filter Example\n");
  printf("Initial array [0,1,2,3,4,3,2,1,0]\n");
  printf("OP: EQ(2)\n");

  in[0] = 0;
  in[1] = 1;
  in[2] = 2;
  in[3] = 3;
  in[4] = 4;
  in[5] = 3;
  in[6] = 2;
  in[7] = 1;
  in[8] = 0;

  out[0] = 0;
  out[1] = 0;

  uint64_t matches = filter(in, out, 9, 0, 2, 0);

  printf("Resulting array [");
  for (uint64_t i = 0; i < matches; i++) {
    printf("%ld, ", out[i]);
  }
  printf("NULL]\n");
}
