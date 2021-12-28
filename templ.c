#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#include "color.h"
#include "templ.h"

#define hasarg(arg) !strcmp(argv[j], arg)

#define COLD 20.0
#define NORMAL 40.0
#define WARM 60.0
#define HOT 80.0

const char *colororder[] = {BLUE, GREEN, YELLOW, RED};

int getcolor(float tempc) {
	int c = 0;

	if(tempc <= HOT) c = 3;
	if(tempc <= WARM) c = 2;
	if(tempc <= NORMAL) c = 1;
	if(tempc <= COLD) c = 0;

	if(tempc >= HOT) c = 3;
	if(tempc <= COLD) c = 0;

	return c;
}

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
		struct Tempdata t;
		t.cel = cputemp(0);
		t.fahr = celtofahr(t.cel);
		t.celsius = celsius;

		int color = getcolor(t.cel);

		if(pretty) {
			printf(colororder[color]);
			prettyprint(t);
			printf(RESET);
		} else {
			printf("%.1f%c\n", t.celsius ? t.cel : t.fahr, t.celsius ? 'C' : 'F');
		}

		sleep(1);
	}

	printf("exiting...\n");

	return 0;
}
