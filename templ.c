#include <stdio.h>
#include <signal.h>
#include "templ.h"

volatile sig_atomic_t stop;

void inthand(int signum) {
	stop = 1;
}

int main(int argc, char *argv[]) {
	printf("temp logger\n");

	unsigned short celsius = 1;
	if(argc > 1) {
		if(argv[1][0] == 'f') celsius = 0;
	}

	printf("displaying temp in %s\n", celsius ? "celsius" : "fahrenheit");

	signal(SIGINT, inthand);

	while(!stop) {
		float t = gettemp();
		if(celsius == 0) t = celtofahr(t);

		printf("%.1f%c\n", t, celsius ? 'C' : 'F');
		sleep(1);
	}

	printf("exiting...\n");

	return 0;
}
