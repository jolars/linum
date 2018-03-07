#include <stdlib.h>
#include <stdio.h>
#include "libresistance.h"
#include "libpower.h"
#include "libcomponent.h"

void clearInputBuffer() {
  char c;
  while((c = getchar()) != '\n' && c != EOF);
}

int main() {
  float volt;
  char conn;
  int n_comp;

  printf("Ange spänningskälla i V: ");
  scanf("%f", &volt);
  clearInputBuffer();

  printf("Ange koppling [P | S]: ");
  scanf("%c", &conn);
  clearInputBuffer();

  printf("Antal komponenter: ");
  scanf("%d", &n_comp);
  clearInputBuffer();

  // input components
  float* comp_array = (float*) malloc(n_comp * sizeof(float));
  if (comp_array == NULL) { // check that malloc worked for comp_array
    fprintf(stderr, "Failed to allocate memory\n");
    exit(1);
  }  
  for (int i = 0; i < n_comp; ++i) {
    printf("Komponent %d i ohm: ", i + 1);
    scanf("%f", &comp_array[i]);
    clearInputBuffer();
  }

  // compute and print resistance
  float resistance = calc_resistance(n_comp, conn, comp_array);
  free(comp_array);
  printf("Ersättningsresistans:\n%.1f ohm\n", resistance);

  // compute power
  float power = calc_power_r(volt, resistance);
  printf("Effekt:\n%.2f W\n", power);

  // figure out what three resistors to use
  float* res_array = (float*) malloc(3 * sizeof(float));
  if (res_array == NULL) { // check that malloc worked for res_array
    fprintf(stderr, "Failed to allocate memory\n");
    exit(1);
  }
  int n_res = e_resistance(resistance, res_array);
  printf("Ersättningsresistanser i E12-serien kopplade i serie:\n");
  for (int i = 0; i < n_res; ++i) {
    printf("%.0f\n", res_array[i]);
  }

  return 0;
}
