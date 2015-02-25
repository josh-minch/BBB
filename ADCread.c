#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PIN_NUMBER_IN_FILE_NAME 43
#define NUMBER_OF_SENSORS 5

void read_pins(long int array[]);
int find_max_element(long int array[]);

int main() {

	//system("echo BB-ADC > /sys/devices/bone_capemgr.*/slots");

	int i;
	int location;
	long int value_array[NUMBER_OF_SENSORS];

	read_pins(value_array);
	location = find_max_element(value_array);

	for (i = 0; i < 5; i++) {
		printf("pin %i has voltage %li\n", i, value_array[i]);
	}
	printf("location is at sensor %i\n", location);

	return 0;
}

void read_pins(long int array[]) {

	FILE *input_handle = NULL;
	char input_value[] = "/sys/bus/iio/devices/iio:device0/in_voltage0_raw";

	char value_str[7];
	long int value_int;
	int i;

	for (i = 0; i < 5; i++) {

		input_value[PIN_NUMBER_IN_FILE_NAME] = i + '0';

		if( (input_handle = fopen(input_value, "r")) != NULL ) {

			fread(&value_str, 6, 6, input_handle);
			value_int = strtol(value_str, NULL, 0);
			array[i] = value_int;
		}
	}

	return;
 }

int find_max_element(long int array[]) {

	int i;
	long int max = 0;
	int location = -1;

	for (i = 0; i < NUMBER_OF_SENSORS; i++) {

		if (array[i] > max) {
			max = array[i];
			location = i;
		}
	}

	return location;
}


