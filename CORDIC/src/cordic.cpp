#include "cordic.h"

void cordic(THETA_TYPE theta, COS_SIN_TYPE *s, COS_SIN_TYPE *c)
{
  COS_SIN_TYPE current_cos = 0.60735;
  COS_SIN_TYPE current_sin = 0.0;

  for (int j = 0; j < NUM_ITERATIONS; j++) {
#pragma HLS PIPELINE

      COS_SIN_TYPE cos_shift = current_cos >> j;
      COS_SIN_TYPE sin_shift = current_sin >> j;

    if(theta >= 0) {
        // Perform the rotation
        current_cos = current_cos - sin_shift;
        current_sin = current_sin + cos_shift;

        // Determine the new theta
        theta = theta - cordic_phase[j];
    }
	else {
        // Perform the rotation
        current_cos = current_cos + sin_shift;
        current_sin = current_sin - cos_shift;

        // Determine the new theta
        theta = theta + cordic_phase[j];
    }
  }

  *s = current_sin;  *c = current_cos;
}

void cordic_wrap(THETA_TYPE theta, COS_SIN_TYPE *s, COS_SIN_TYPE *c)
{
#pragma HLS INTERFACE m_axi port=s offset=slave depth=1
#pragma HLS INTERFACE m_axi port=c offset=slave depth=1
#pragma HLS INTERFACE s_axilite port=theta bundle=CTRL
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL
cordic(theta, s, c);

}
