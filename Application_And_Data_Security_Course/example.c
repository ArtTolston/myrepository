#include<stdio.h>
#include<stdlib.h>
//#include "secure_allocation_lib.h"

int main() {
	int* buf[4];

	for(int i = 0; i < 4; i++) {
		buf[i] = (int*) malloc(10);
		printf("%d\n", *buf[i]);
	}

	for(int i = 0; i < 2; i++) {
		free(buf[i]);
	}
	

	sec_stats();

	sec_emergency_clean();

	sec_stats();

	return 0;
}
