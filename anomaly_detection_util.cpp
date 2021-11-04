/*
 * animaly_detection_util.cpp
 *
 * Author: Roni Weiss id: 318349750 and Aviv Shitrit id: 206333007 hi roni hi
 */




#include <cmath>
#include <math.h>
#include <iostream>
#include "anomaly_detection_util.h"

float avg(float* x, int size) {
	float avg = 0;
	for (int i = 0; i < size; ++i)
	{
		avg += x[i];
	}
	return avg / size;
}

float mean(float* x, int size)
{
	float mean = 0;
	for (int i = 0; i < size; ++i)
	{
		mean += x[i];
	}
	mean = mean / size;
	return mean;
}

// returns the variance of X and Y
float var(float* x, int size) {
	float var1 = 0;
	float newMean = mean(x, size);

	for (int i = 0; i < size; ++i)
	{
		//var1 += (x[i] - newMean)* (x[i] - newMean);
		var1 += pow(x[i], 2);
	}
	float avg_sq = pow(avg(x, size), 2);
	float var = (var1 / size) - avg_sq;
	//var1 = var1 / size;
	//std::cout << var1;
	return var;
}

// returns the covariance of X and Y
// calculate mean for X and Y and then (x - mean(x)*(y - mean(y)
// try to think about negative cov
float cov(float* x, float* y, int size) {
	float meanX = mean(x, size);
	float meanY = mean(y, size);
	float sum = 0;
	float cov = 0;
	for (int i = 0; i < size; ++i)
	{
		sum += (x[i] - meanX) * (y[i] - meanY);
	}
	cov = sum / size;
	return cov;
	return 0;
}

// standard deviation - sqrt of the variance.
float standardDev(float var)
{
	return sqrt(var);
}

// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size) {
	float newCov = cov(x, y, size);
	float varX = var(x,size);
	float varY = var(y,size);
	float stdX = standardDev(varX);
	float stdY = standardDev(varY);
	float pearson = newCov / (stdX * stdY);
	return pearson;
}

// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size) {
	float* x = new float[size];
	float* y = new float[size];
	for (int i = 0; i < size; ++i) {
		x[i] = points[i]-> x;
		y[i] = points[i]-> y;
	}
	float a = cov(x, y, size) / var(x, size);
	float b = avg(y, size) - a * avg(x, size);
	delete[] x;
	delete[] y;
	return Line(a, b);
}

// returns the deviation between point p and the line equation of the points
// using linear_reg to calculate a line.
// use dev to calculate the deviation between point p and line.
float dev(Point p, Point** points, int size) {
	Line l = linear_reg(points, size);
//	return dev(p, l);
	float f_x = (l.a * p.x) + l.b;
	return std::abs(p.y - f_x);
}

// returns the deviation between point p and the line
// calculate the Y value of the point (using X value of the point in the line equation)
// substract the Y Value of the point from the Y value that we found (using abs).
float dev(Point p, Line l) {
//	float tempY = p.x * l.a + l.b;
	//	float y = std::abs(double(tempY - p.y));
//	double val = tempY - p.y;
//	double y = std::abs(val);
	//float val = tempY - p.y;
//	float y = std::abs(val);
	//return y;

	float f_x = (p.x * l.a) + l.b;
	float dev = std::abs(f_x - p.y);
	return dev;
}



