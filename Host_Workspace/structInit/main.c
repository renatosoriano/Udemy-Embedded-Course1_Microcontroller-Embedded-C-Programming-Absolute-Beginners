/*
 * main.c
 *
 *  Created on: Nov 7, 2022
 *      Author: renatosoriano
 */

#include<stdint.h>
#include<stdio.h>

struct carModel
{
	uint8_t carSpeed;
	uint32_t carPrice;
};

int main(void)
{
	struct carModel  carBMW = {0};
	printf("Sizeof of struct carModel is %llu\n",sizeof(struct carModel));

    getchar();

	return 0;
}










