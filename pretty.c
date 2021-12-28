// pretty print (large 16-segment display)

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "alpha.h"
#include "color.h"
#include "templ.h"

#define c(p, c) getbit(segc, p) ? c : ' '

#define GWIDTH 30
#define MAXTEMP 120
#define WPT GWIDTH / MAXTEMP

const int numbers[10] = {D0, D1, D2, D3, D4, D5, D6, D7, D8, D9};

void prints16(char result[5][6], int segc) { // char result[y][x + \0]
	snprintf(result[0], sizeof(result[0]), " %c %c ", c(15, '-'), c(14, '-'));
	snprintf(result[1], sizeof(result[1]), "%c%c%c%c%c", c(13, '|'), c(12, '\\'), c(11, '|'), c(10, '/'), c(9, '|'));
	snprintf(result[2], sizeof(result[2]), " %c %c ", c(8, '-'), c(7, '-'));
	snprintf(result[3], sizeof(result[3]), "%c%c%c%c%c", c(6, '|'), c(5, '/'), c(4, '|'), c(3, '\\'), c(2, '|'));
	snprintf(result[4], sizeof(result[4]), " %c %c ", c(1, '-'), c(0, '-'));
}

void printgraph(float data[GRAPHLEN]) {
	printf(BLUE);
	for(short i = 0; i < GRAPHLEN; i++) {
		for(short j = 0; j < (int)(data[i]); j++) {
			printf("*");
		}
		printf("\n");
	}
	printf(RESET);
}

float data[GRAPHLEN] = {0.0, 0.0, 0.0, 0.0, 0.0};

void prettyprint(struct Tempdata t) {
	printf("\e[1;1H\e[2J");

	float temp = t.celsius ? t.cel : t.fahr;

	leftrot(data, GRAPHLEN);
	data[GRAPHLEN - 1] = t.cel;

	char stemp[8];
	snprintf(stemp, sizeof(stemp), "%.1f", temp);
	char seg[8][5][6];

	short i;
	for(i = 0; i < strlen(stemp); i++) {
		char c = stemp[i];

		int segc;
		if(isdigit(c)) {
			int d = c - '0';
			segc = numbers[d];
		} else if(c == '.') {
			segc = DFULLSTOP;
		}

		prints16(seg[i], segc);
	}
	prints16(seg[i], t.celsius ? DC : DF);

	for(short y = 0; y < CHARH; y++) {
		for(short x = 0; x < strlen(stemp) + 1; x++) {
			printf("%s ", seg[x][y]);
		}

		printf("\n");
	}

	printgraph(data);
}
