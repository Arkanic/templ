#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#include "templ.h"

#define hasarg(arg) !strcmp(argv[j], arg)

void showhelp(void) {
	printf(
"--celsius                Show temperature in celsius (default)\n"
"--fahrenheit             Show temperature in fahrenheit\n"
"--pretty                 Show pretty 16-seg numbers (default)\n"
"--standard               Show simple text temperature\n"
"--help                   Show this message\n"
	);
}

volatile sig_atomic_t stop;

void inthand(int signum) {
	stop = 1;
}

int main(int argc, char *argv[]) {
	printf("temp logger\n");

	unsigned short celsius = 1;
	unsigned short pretty = 1;

	for(int j = 1; j < argc; j++) {
		int more = j + 1 < argc;

		if(hasarg("--celsius")) celsius = 1;
		else if(hasarg("--fahrenheit")) celsius = 0;
		else if(hasarg("--pretty")) pretty = 1;
		else if(hasarg("--standard")) pretty = 0;
		else if(hasarg("--help")) {
			showhelp();
			exit(0);
		} else {
			fprintf(stderr, "Not enough args for option '%s'.\n\n", argv[j]);
			showhelp();
			exit(1);
		}
	}

	printf("displaying temp in %s\n", celsius ? "celsius" : "fahrenheit");

	signal(SIGINT, inthand);

	while(!stop) {
		float t = cputemp(0);
		if(celsius == 0) t = celtofahr(t);

		if(pretty) {
			prettyprint(t, celsius);
		} else {
			printf("%.1f%c\n", t, celsius ? 'C' : 'F');
		}

		sleep(1);
	}

	printf("exiting...\n");

	return 0;
}
