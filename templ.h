// generic
#define GRAPHLEN 5

// temp.c
float cputemp(int core);

// pretty.c
unsigned short getbit(int num, int position);
void prettyprint(float temp, unsigned short celsius);

// util.c
float celtofahr(float celsius);
void leftrot(float arr[], int len);
void prints16(char result[5][6], int segc);
