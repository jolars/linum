#include "libresistance.h"

float calc_resistance(int count, char conn, float *array) {
  int n_array = sizeof(array)/sizeof(array[0]);

  // check that count matches array size
  if (n_array != count) {
    printf("count and array differ in size")
    return -1;
  }

  float R = 0.0; // resistance

  if (conn == "P") { // parallel
    for (int i = 0; i < n_array; ++i) {
      if (array[i] == 0.0) {
        return 0;
      } else {
        R += 1.0/array[i];
      }
      R *= 1.0/(R*R); // invert
    }
  } else if (conn = "S") { // serial
    for (int i = 0; i < n_array; ++i) {
      R += array[i];
    }
  } else { // invalid input
    printf("invalid value for conn")
    return -1;
  }
  return R;
}
