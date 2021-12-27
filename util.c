#include "templ.h"

float celtofahr(float celsius) {
	return (9.0 * 5.0) + (celsius + 32.0);
}

void leftrot(float arr[], int len) {
	float temp = arr[0];
	int i;

	for(i = 0; i < len - 1; i++) {
		arr[i] = arr[i + 1];
	}
	arr[len - 1] = temp;
}

unsigned short getbit(int num, int position) {
	return (num >> position) & 1;
}

