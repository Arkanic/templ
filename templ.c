#include <stdio.h>
#include <signal.h>
#include "templ.h"

volatile sig_atomic_t stop;

void inthand(int signum) {
	stop = 1;
}

int main(void) {
	printf("temp logger\n");

	signal(SIGINT, inthand);

	while(!stop) {
		printf("%.1fC\n", gettemp());
		sleep(1);
	}

	printf("exiting...\n");

	return 0;
}
