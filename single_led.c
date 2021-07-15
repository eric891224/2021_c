//gcc -Wall -o "%e" "%f" -lwiringPi
//gcc -Wall -o test test.c -lwiringPi

/*
 +-----+-----+---------+------+---+---Pi 3B+-+---+------+---------+-----+-----+
 | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |
 +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+
 |     |     |    3.3v |      |   |  1 || 2  |   |      | 5v      |     |     |
 |   2 |   8 |   SDA.1 |   IN | 1 |  3 || 4  |   |      | 5v      |     |     |
 |   3 |   9 |   SCL.1 |   IN | 1 |  5 || 6  |   |      | 0v      |     |     |
 |   4 |   7 | GPIO. 7 |   IN | 1 |  7 || 8  | 0 | IN   | TxD     | 15  | 14  |
 |     |     |      0v |      |   |  9 || 10 | 1 | IN   | RxD     | 16  | 15  |
 |  17 |   0 | GPIO. 0 |   IN | 1 | 11 || 12 | 0 | IN   | GPIO. 1 | 1   | 18  |
 |  27 |   2 | GPIO. 2 |   IN | 0 | 13 || 14 |   |      | 0v      |     |     |
 |  22 |   3 | GPIO. 3 |   IN | 0 | 15 || 16 | 0 | IN   | GPIO. 4 | 4   | 23  |
 |     |     |    3.3v |      |   | 17 || 18 | 0 | IN   | GPIO. 5 | 5   | 24  |
 |  10 |  12 |    MOSI |   IN | 0 | 19 || 20 |   |      | 0v      |     |     |
 |   9 |  13 |    MISO |   IN | 0 | 21 || 22 | 0 | IN   | GPIO. 6 | 6   | 25  |
 |  11 |  14 |    SCLK |   IN | 0 | 23 || 24 | 1 | IN   | CE0     | 10  | 8   |
 |     |     |      0v |      |   | 25 || 26 | 1 | IN   | CE1     | 11  | 7   |
 |   0 |  30 |   SDA.0 |   IN | 1 | 27 || 28 | 1 | IN   | SCL.0   | 31  | 1   |
 |   5 |  21 | GPIO.21 |   IN | 1 | 29 || 30 |   |      | 0v      |     |     |
 |   6 |  22 | GPIO.22 |   IN | 1 | 31 || 32 | 0 | IN   | GPIO.26 | 26  | 12  |
 |  13 |  23 | GPIO.23 |   IN | 0 | 33 || 34 |   |      | 0v      |     |     |
 |  19 |  24 | GPIO.24 |   IN | 0 | 35 || 36 | 0 | IN   | GPIO.27 | 27  | 16  |
 |  26 |  25 | GPIO.25 |   IN | 0 | 37 || 38 | 0 | IN   | GPIO.28 | 28  | 20  |
 |     |     |      0v |      |   | 39 || 40 | 0 | IN   | GPIO.29 | 29  | 21  |
 +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+
 | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |
 +-----+-----+---------+------+---+---Pi 3B+-+---+------+---------+-----+-----+
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>

#define len(array) (sizeof(array)/sizeof(array[0]))
#define led1 8
/*#define led2 9
#define led3 7
#define led4 1*/
 
/*single led functions
void blink_1(int pin)
{
	for (;;)
	{
		digitalWrite(pin,0);
		delay(1000);
		digitalWrite(pin,1);
		delay(1000);
	}
}

void lit_1(int pin)
{
	for(;;)
	{
		digitalWrite(pin,0);
		delay(1);
		digitalWrite(pin,1);
		delay(1);	
	}
}

void single_pwm(int pin, int freq, int dc)
{
	double T = 1/(double)freq;
	int on_duration = T*(dc/100.)*1000;
	int off_duration = (T*1000-on_duration);
	digitalWrite(pin,1);
	delay(on_duration);
	digitalWrite(pin,0);
	delay(off_duration); 
}

void mypwm_1(int pin, int freq)
{	
	printf("conducting pwm\n");
	single_pwm(pin,freq,0);
	int dc;
	while (1)
	{
		for (dc=0;dc<=100;dc++)
		{
			single_pwm(pin,freq,dc);
		}
		for (dc=100;dc>=0;dc--)
		{
			single_pwm(pin,freq,dc);
		}
		delay(10);
	}
}*/

void blink(int v[], int len){
	int i;
	printf("%d leds are blinking\n", len);
	while (1)
	{
		for (i=0;i<len;i++)
		{
			digitalWrite(v[i],1);
		} 
		delay(1000);
		for (i=0;i<len;i++)
		{
			digitalWrite(v[i],0);
		}
		delay(1000);
	}
}

void single_pwm(int led_array[], int freq, int dc, int len){
	double T = 1/(double)freq;
	int on_duration = T*(dc/100.)*1000;
	int off_duration = (T*1000-on_duration);
	
	int i;
	for (i=0;i<len;i++){
		digitalWrite(led_array[i],1);
	}
	delay(on_duration);
	for (i=0;i<len;i++){
		digitalWrite(led_array[i],0);	
	}
	delay(off_duration); 
}

void mypwm(int led_array[], int freq, int len){
	printf("%d leds are conducting pwm\n", len);
	int dc;
	while (1){
		for (dc=0;dc<=100;dc++){
			single_pwm(led_array,freq,dc,len);
		}
		for (dc=100;dc>=0;dc--){
			single_pwm(led_array,freq,dc,len);
		}
		delay(10);
	}
}

void setup(int led_array[],int len){
	if (wiringPiSetup()==-1)
	{
		printf("not working\n");
		exit(1);
	}else 
	{
		printf("working\n");
		
		for (int i=0;i<len;i++)
		{
			pinMode(led_array[i],OUTPUT);
		}
	}
}

int main(int argc, char **argv){	
	int led_array[] = {led1};
	int length = len(led_array);
	
	setup(led_array, length);
	
	blink(led_array, length);
	//mypwm(led_array, 60, length);	
	
	return 0;
}

