#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define COMMAND "/opt/vc/bin/vcgencmd measure_temp"
#define PREAMBLELEN 5

float parsetemp(char output[16]) {
        short outputlen = strlen(output);
        output[outputlen - 3] = '\0';

        char *rawfloat = output + PREAMBLELEN;
        return atof(rawfloat);
}

float gettemp(void) {
        FILE *vcgencmd;
        char path[1035];

        vcgencmd = popen(COMMAND, "r");
        if(vcgencmd == NULL) {
                printf("Failed to run command.\n");
                return -1;
        }

        char output[16];

        while(fgets(path, sizeof(path), vcgencmd) != NULL) {
                snprintf(output, sizeof(output), "%s", path);
        }

        pclose(vcgencmd);

        float result = parsetemp(output);

        return result;
}
