#include "libresistance.h"
#include <stdio.h>

float calc_resistance(int count, char conn, float *array) {
  float R = 0.0; // resistance

  if (conn == 'P') { // parallel
    for (int i = 0; i < count; ++i) {
      if (array[i] == 0.0) {
        return 0;
      } else if (array[i] < 0.0) {
        printf("error: resistance cannot be negative\n");
        return -1;
      } else {
        R += 1.0/array[i];
      }
      R *= 1.0/(R*R); // invert
    }
  } else if (conn == 'S') { // serial
    for (int i = 0; i < count; ++i) {
      if (array[i] < 0.0) {
        printf("error: resistance cannot be negative\n");
        return -1;
      }
      R += array[i];
    }
  } else { // invalid input
    printf("error: invalid value for conn\n");
    return -1;
  }
  return R;
}
