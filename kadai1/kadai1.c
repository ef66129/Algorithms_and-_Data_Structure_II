/*
Copyright (c) 2015 EF66_129
Released under the MIT license
http://opensource.org/licenses/mit-license.php
*/

#include <stdio.h>
#include <math.h>

int main(void)
{
	int data[] = {17, 39, 1, 9, 5, 24, 2, 11, 23, 6};
	int i, sum = 0;
	double avg, var = 0.0;

	for (i = 0; i < 10; i++) {
		sum += data[i];
	}
	avg = sum / 10.0;

	for (i = 0; i < 10; i++) {
		var += pow(avg - data[i], 2.0);
	}
	var /= 9.0;


	printf("平均: %f¥n", avg);
	printf("分散: %f¥n", var);

	return 0;
}
