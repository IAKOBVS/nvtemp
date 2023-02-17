#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "nvtemp.h"
#include <assert.h>

#include </opt/cuda/include/nvml.h>

#define NANO_TO_MILI 1000000
#define LOOP_INTERVAL 200 * NANO_TO_MILI

int nanosleep(const struct timespec *requested_time, struct timespec *remaining);

int main()
{
	struct timespec interval;
	interval.tv_nsec = LOOP_INTERVAL;
	nvmlDevice_t device;
	if (system("sudo nvidia-settings -a \"[gpu:0]/GPUFanControlState=1\""))
		goto ERROR;
	if (nvmlInit() == NVML_SUCCESS);
	else goto ERROR;
	if (nvmlDeviceGetHandleByIndex(0, &device) == NVML_SUCCESS);
	else goto ERROR_SHUTDOWN;
	int tmp = 0;
	unsigned int temp;
	unsigned int speed = 33;
	for (char buf[57];;) {
		if (nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, (unsigned int *)&temp) == NVML_SUCCESS);
		else goto ERROR_SHUTDOWN;
		if (abs(tmp - (int)temp) > 2) {
			switch (temp) { TEMP_THEN_SPEED(speed); }
			sprintf(buf, "sudo nvidia-settings -a \"[fan:0]/GPUTargetFanSpeed=%d\"", speed);
			system(buf);
			tmp = temp;
		}
		nanosleep(&interval, NULL);
	}
	if (nvmlShutdown() == NVML_SUCCESS);
	else goto ERROR_SHUTDOWN;
	system("sudo nvidia-settings -a \"[gpu:0]/GPUFanControlState=0\"");
	return 0;

ERROR_SHUTDOWN:
	nvmlShutdown();
ERROR:
	if (system("sudo nvidia-settings -a \"[gpu:0]/GPUFanControlState=0\""))
		goto ERROR;
	perror("");
	return 1;
}
