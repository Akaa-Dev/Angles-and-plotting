/*
* Program: angles.c
* Author : Emmanuel Anokwuru
* Date :   18-12-2020
*/
#define _CRT_SECURE_NO_WARNINGS
# define DEBUG 0
# define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
# define PI 3.1415
#define XMIN -PI
#define XMAX +PI
#define XSTEP (2*PI/ROWS)
#define XEXTRA 0.01
#define CONSTDEV 1e-6 // constant deviation
#define COLUMNS 80
#define ROWS 40
#define print printf



double norm_angle(double x) {
	while(x< -M_PI || x > M_PI){
		if (x < -M_PI) {
			x = x + (2 * M_PI);
			if (DEBUG)printf("%lf \n", x);
		}
        if(x>M_PI){
			x = x - (2 * M_PI);
		if (DEBUG)printf("%lf \n", x);
		}
	}
	return x;
}

double sinus(double x, double deviation) {
    x= norm_angle(x);
	// s0 = -1^(0)*x^(2*0+1) / (2*0+1)! = 1*x / 1! = x 
	//calculating for k =0 
	double sk = x; 
	double sum = sk;
	double k=1.0;
	while (sk > 0 && sk > deviation || sk<0 && sk<-deviation) {
		sk = sk * (-x * x / (2 * k * (2 * k + 1)));
		sum += sk;
		k++;
	}
	return sum;
}
void plot_value(double value, double y_min, double y_max) {
	double range = y_max - y_min;
	int column = (value - y_min) / (range) * COLUMNS; // between 0 .. 80
	for (int i = 0; i < column; i++) {
		printf(" ");
	}
	printf("*\n");
}

void plot_function_by_key(char ch) {
	if (DEBUG) printf("### plot_function_by_key('%c')\n", ch);
	int index = 0;
	double x, y, y_min = 0.0, y_max = 0.0;
	double x_array[100], y_array[100];
	// loop over range of x values:
	for (x = XMIN; x <= XMAX + XEXTRA; x = x + XSTEP) { // #steps is ROWS
		
		switch (ch) { // depend on key pressed
		case 'f': y = sinus(x,CONSTDEV); break; // plotting key value for the sinus function
	//	case 's': y = sin(x); break;
	//  case 'c': y = cos(x); break;
	//	case 't': y = tan(x); break;
	//	case 'l': y = x; break;
	//	case 'q': y = x * x; break;
		default: y = 0;
		}
		//if (DEBUG) printf("x=%.3lf y=%.3lf\n", x, y);
		x_array[index] = x; // store into table
		y_array[index] = y; // store into table
		y_min = (y < y_min) ? y : y_min;
		y_max = (y > y_max) ? y : y_max;
		index++; // increase the index
	}
	int num_values = index; // so many elements in the table
	if (DEBUG) printf("num_values=%d, y_min=%.3f, y_max=%.3f\n", num_values, y_min, y_max);
	for (index = 0; index < num_values; index++) { // #steps is ROWS
		x = x_array[index]; // read out values from table
		y = y_array[index];
		//if (DEBUG) printf("x=%.3lf y=%.3lf\n", x, y);
		printf("x=%6.3lf ", x);
		plot_value(y, y_min, y_max);
	}
	if (DEBUG) printf("### plot_function_by_key() finished.\n");
}

void do_plotting_frontend() {
	if (DEBUG) printf("### do_plotting_frontend()\n");
	char ch; // character from keyboard
	int key_pressed = ' '; // keyboard key value
	// loop:
	while (key_pressed != '.') {
		//print("Please select function to plot (keys a..z, .=quit)\n");
		print("Type in f to plot the sinus value,press . to quit: \n");
		key_pressed = getch();
		ch = key_pressed; // char <- int conversion
		if (DEBUG) print("Key pressed was '%c'=%04d=0x%04X\n", ch, key_pressed, key_pressed);
		plot_function_by_key(ch);
	}
	if (DEBUG) printf("### do_plotting_frontend() finished.\n");
}

int main(void) {
	double x;

	// Printing radiants to degree
	for (x = -10; x < 10.1; x += 2.0) {
		printf(" The angle %12.8lf ( radiants ) corresponds to %12.8lf \n", x, norm_angle(x));
	}

	
	for (x =-M_PI; x <= M_PI;x+=M_PI/10) {
		printf("sinus(%lf)=%lf\n", x, sinus(x, CONSTDEV));
	}

	// plotting the graph
	do_plotting_frontend();

	return 0;
}

