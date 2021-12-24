#define COMMAND "/opt/vc/bin/vcgencmd measure_temp"
#define PREAMBLELEN 5

float parsetemp(char output[16]);
float gettemp(void);
