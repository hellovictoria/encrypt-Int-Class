/* encrypt data from sensor, & print the temperature 
**
** Author: Xiao Yang
**
*/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include "safeopts1.h"

#define GPIO_DIRECTION_PATH "/sys/class/gpio/gpio%d/direction"
#define GPIO_VALUE_PATH "/sys/bus/iio/devices/iio:device1/in_voltage%d_raw"
#define GPIO_EXPORT_PATH "/sys/class/gpio/export"
#define PLUP_DIRECTION_PATH "/sys/class/gpio/gpio%d/direction"
#define TRIG_ALL_DIRECTION_PATH "/sys/class/gpio/gpio%d/direction"
#define BUFOUT_DIRECTION_PATH "/sys/class/gpio/gpio%d/direction"
#define BUFFER 60

int main()
{
//GPIO Pin 13
	int gpio_pin = 201;
	int bufout_pin = 233;
	int plup_pin = 209;
	int trig_all_pin = 214;
    int analog_nu=1;
//Path Variables
	char gpio_exp_path[BUFFER];
	char gpio_direction_path[BUFFER];
	char gpio_value_path[BUFFER];
	char bufout_direction_path[BUFFER];
	char plup_direction_path[BUFFER]; 
	char trig_all_direction_path[BUFFER];
//analog data
    FILE * encry_fp;
    char * ecypted_code;
//digital data
    int temp_value;
//Files
	int fd_export, fd_val, fd_dir;
	int err = 0;
//Set GPIO Paths
	snprintf(gpio_exp_path, BUFFER, GPIO_EXPORT_PATH, gpio_pin); //
	snprintf(gpio_direction_path, BUFFER, GPIO_DIRECTION_PATH, gpio_pin);
	snprintf(gpio_value_path, BUFFER, GPIO_VALUE_PATH, analog_nu);
	snprintf(bufout_direction_path, BUFFER, BUFOUT_DIRECTION_PATH, bufout_pin);
	snprintf(plup_direction_path, BUFFER, PLUP_DIRECTION_PATH, plup_pin);
	snprintf(trig_all_direction_path, BUFFER, TRIG_ALL_DIRECTION_PATH, trig_all_pin);

/*
	printf("%s", gpio_exp_path);
	printf("\n");
	printf("%s", gpio_direction_path);
	printf("\n");
	printf("%s", gpio_value_path);
	printf("\n");
	printf("%s", bufout_direction_path);
	printf("\n");
	printf("%s", plup_direction_path);
	printf("\n");
	printf("%s", trig_all_direction_path);
	printf("\n");
*/

// Export GPIO
	fd_export = open(gpio_exp_path, O_WRONLY);
	if(fd_export < 0){
		perror("Can't Open Export File");
		return -1;
	}else
	{
		char buf[15];
		sprintf(buf,"%d",gpio_pin);
		write(fd_export, buf, sizeof(buf));
		sprintf(buf,"%d",bufout_pin);
		write(fd_export, buf, sizeof(buf));
		sprintf(buf,"%d",plup_pin);
		write(fd_export, buf, sizeof(buf));
		sprintf(buf,"%d",trig_all_pin);
		write(fd_export, buf, sizeof(buf));
		close(fd_export);
	}

//Set Direction
	fd_dir = open(trig_all_direction_path, O_WRONLY);
	if(fd_dir < 0){
		perror("Can't Open TRIG_ALL Direction File");
	}else{
		write(fd_dir,"low", sizeof("low"));
		//printf("Set trig_all_direction %d value as LOW\n", trig_all_pin);
		close(fd_dir);
	}
	fd_dir = open(bufout_direction_path, O_WRONLY);
	if(fd_dir < 0){
		perror("Can't Open BUFOUT Direction File");
	}else{
		write(fd_dir,"low", sizeof("low"));
		//printf("Set bufout_direction %d value as High\n", bufout_pin);
		close(fd_dir);
	}
        fd_dir = open(plup_direction_path, O_WRONLY);
        if(fd_dir < 0){
                perror("Can't Open PLUP Direction File");
        }else{
                write(fd_dir,"in", sizeof("in"));
		        //printf("Set plup_direction %d value as in\n", plup_pin);
                close(fd_dir);
        }
        fd_dir = open(trig_all_direction_path, O_WRONLY);
        if(fd_dir < 0){
                perror("Can't Open TRIG_ALL Direction File");
        }else{
                write(fd_dir,"high", sizeof("high"));
		        //printf("Set trig_all_direction %d value as High\n", trig_all_pin);
                close(fd_dir);
        }

// encrypt & print 
        encry_fp=ecyfopen(gpio_value_path,"r");
        ecypted_code=(char *)malloc(encrylen * sizeof(char));
        fread(ecypted_code,encrylen,1,encry_fp);
        printf("\noutput encrypted code:\n%s\n",ecypted_code);

        dcyprint_Temp(gpio_value_path,"r");

// Close the Files
    	return 0;
}


/** End of GPIO Program **/
