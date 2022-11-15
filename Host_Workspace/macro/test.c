/*
 * test.c
 *
 *  Created on: Nov 10, 2022
 *      Author: renatosoriano
 */

#include <stdio.h>

//#define AREA_CIR
#define AREA_TRI

#if !defined(AREA_CIR) && !defined(AREA_TRI)
	#warning "No macros defined."
#endif

int main()
{

#ifdef AREA_CIR
	printf("This is circle area calculation program\n");
   float radius = 0;
   fflush(stdout);
   printf("Enter the radius :");
   fflush(stdout);
   scanf("%f", &radius);
   printf("Area of circle  = %f\n",(3.1415 * radius * radius));
   fflush(stdout);
#endif


#ifdef AREA_TRI
   printf("This is Triangle area calculation program\n");
   float base, height;
   fflush(stdout);
   printf("Enter base and height: ");
   fflush(stdout);
   scanf("%f%f",&base, &height);
   printf("Area of triangle = %f\n", (0.5 * base * height));
#endif


   return 0;

}


