/*
 * File: SierpinskiTriangle.cpp
 * ----------------------------
 * Name: [Javier Palomares]
 * Section: [Elmer Le]
 * Draws the Sierpinski Triangle of arbitrary order and length
 */

#include <iostream>
#include <cmath>
#include "graphics.h"
#include "simpio.h"
using namespace std;

// Mathematical constant
const double PI = 3.14159265358979323846;

void drawSierpinskiTriangle(double x, double y, int order, double length);
void drawTriangle(double x, double y, double length);

/* Main program */
int main() {
    initGraphics();
	int order = getInteger("Enter the order: ");
	double length = getReal("Enter the edge length: ");
	
	// Bottom left corner of the "big" triangle
	double x = getWindowWidth() / 2 - length / 2 * cos(PI / 3);
	double y = getWindowHeight() / 2 + length / (2 * sqrt(PI / 3));
	
	drawSierpinskiTriangle(x,y,order,length);						  
   return 0;
}

/* Draws the SierpinskiTriangle */
void drawSierpinskiTriangle(double x, double y, int order, double length){
	if(order == 0){
		drawTriangle(x, y, length);
	}
	else {
		length /= 2;
		order--;
		// A Sierpinski triangle of order n is 3 triangles of order n - 1
		drawSierpinskiTriangle(x , y, order, length);
		drawSierpinskiTriangle(x + length * cos(PI / 3), y - length * sin(PI / 3),  order, length);
		drawSierpinskiTriangle(x + length, y, order, length);
		
	}
}

/* Draws a single triangle */
void drawTriangle(double x, double y, double length){
	// Equilateral triangles have angles PI / 3 = 60 degrees
	
	// Bottom Left corner
	double x0 = x;
	double y0 = y;
	
	// Bottom right corner
	double x1 = x0 + length;
	double y1 = y0;
	
	// Top corner
	double x2 = x0 + length * cos(PI / 3);
	double y2 = y0 - length * sin(PI / 3);
	
	// Lines connecting the corners
	drawPolarLine(x0,y0,length,0);
	drawPolarLine(x1,y1,length,120);
	drawPolarLine(x2,y2,length,240);
}
