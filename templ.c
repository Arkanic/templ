#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#include "color.h"
#include "templ.h"

#define hasarg(arg) (!strcmp(argv[j], arg))

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

struct Options {
	unsigned short celsius;
	unsigned short pretty;
};

void showhelp(void) {
	printf(
"--celsius,    -c         Show temperature in celsius (default)\n"
"--fahrenheit, -f         Show temperature in fahrenheit\n"
"--pretty,     -p         Show pretty 16-seg numbers (default)\n"
"--standard,   -s         Show simple text temperature\n"
"--help,       -h         Show this message\n"
	);
}

volatile sig_atomic_t stop;

void inthand(int signum) {
	stop = 1;
}

int main(int argc, char *argv[]) {
	printf("temp logger\n");

	struct Options opts;
	opts.celsius = 1;
	opts.pretty = 1;

	for(int j = 1; j < argc; j++) {
		int more = j + 1 < argc;

		if(hasarg("--celsius") || hasarg("-c")) opts.celsius = 1;
		else if(hasarg("--fahrenheit") || hasarg("-f")) opts.celsius = 0;
		else if(hasarg("--pretty") || hasarg("-p")) opts.pretty = 1;
		else if(hasarg("--standard")|| hasarg("-s")) opts.pretty = 0;
		else if(hasarg("--help") || hasarg("-h")) {
			showhelp();
			exit(0);
		} else {
			fprintf(stderr, "Not enough args for option '%s'.\n\n", argv[j]);
			showhelp();
			exit(1);
		}
	}

	printf("displaying temp in %s\n", opts.celsius ? "celsius" : "fahrenheit");

	signal(SIGINT, inthand);

	while(!stop) {
		struct Tempdata t;
		t.cel = cputemp(0);
		t.fahr = celtofahr(t.cel);
		t.celsius = opts.celsius;

		int color = getcolor(t.cel);

		if(opts.pretty) {
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
