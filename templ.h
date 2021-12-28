// generic
#define GRAPHLEN 5

struct Tempdata {
	float cel;
	float fahr;
	unsigned short celsius;
};

// temp.c
float cputemp(int core);

// pretty.c
unsigned short getbit(int num, int position);
void prettyprint(struct Tempdata t);

// util.c
float celtofahr(float celsius);
void leftrot(float arr[], int len);
void prints16(char result[5][6], int segc);
