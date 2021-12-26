#include <stdio.h>
#include <stdlib.h>

const char *hwmon[] = {
	"/sys/devices/platform/coretemp.0/hwmon/hwmon3/temp1_input",
	"/sys/devices/platform/coretemp.0/hwmon/hwmon1/temp1_input",
	"/sys/devices/platform/coretemp.0/hwmon/hwmon2/temp1_input",
	"/sys/class/hwmon/hwmon2/temp1_input",
	"/sys/class/hwmon/hwmon0/temp1_input"
};

float cputemp(int core) {
	float tc = 0.0;
	FILE *fd;
	u_int32_t val = 0;

	for(int i = 0; i < sizeof(hwmon) && !fd; i++) {
		fd = fopen(hwmon[i], "r");
	}
	if(!fd) return tc;

	if(fscanf(fd, "%d", &val)) tc = val / 1000.0;
	fclose(fd);

	return tc;
}
