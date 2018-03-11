#include <math.h>
#include "libcomponent.h"

static float round_to(float f, int dec)
{
  f *= pow(10, dec);
  f = round(f);
  f /= pow(10, dec);
  return f;
}

static float get_resistence(float in, int last)
{
  if(in == 0)
    return 0;
  float e12[12] = {1, 1.2, 1.5, 1.8, 2.2, 2.7, 3.3, 3.9, 4.7, 5.6, 6.8, 8.2};
  float comp = last ? 0.9 : 1 ;
  int i;
  int p = log10(in);

  for(i = 11; in/round_to(e12[i]*pow(10, p), 2) < comp; --i);

  return round_to(e12[i]*pow(10, p), 2);
}

int e_resistance(float orig_resistance, float *res_array )
{
  int i;
  for(i = 0; i < 3; ++i)
    res_array[i] = 0;

  for(i = 0; i < 3 && orig_resistance > 0; ++i) {
    res_array[i] = get_resistence(orig_resistance, i == 2);
    orig_resistance -= res_array[i];
  }

  return i;
}

