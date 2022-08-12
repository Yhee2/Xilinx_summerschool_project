#include <math.h>
#include"cordic.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

double abs_double(double var){
	if ( var < 0)
	var = -var;
	return var;


}
int main(int argc, char **argv)
{	

	COS_SIN_TYPE s;			//sine
	COS_SIN_TYPE c;			//cos
	THETA_TYPE radian; 		//radian versuin of degree

	double zs, zc; 			// sine and cos values calculated from math.

	//Error checking
	double Total_Error_Sin=0.0;
	double Total_error_Cos=0.0;
	double error_sin=0.0, error_cos=0.0;


	for(int i=1;i<NUM_DEGREE;i++) {
			radian = i*M_PI/180;
			cordic_wrap(radian, &s, &c);
			zs = sin((double)radian);
			zc = cos((double)radian);
			error_sin=(abs_double((double)s-zs)/zs)*100.0;
			error_cos=(abs_double((double)c-zc)/zc)*100.0;
			Total_Error_Sin=Total_Error_Sin+error_sin;
			Total_error_Cos=Total_error_Cos+error_cos;
			printf("sin_cordic = %f,cos_cordic = %f,sin_real = %f,cos_real = %f \n",(double)s,(double)c,zs,zc);
	}


	printf ("Average_Error_Sin=%f%%, Average_error_Cos=%f%%, \n", Total_Error_Sin/90, Total_error_Cos/90);
	return 0;
}
