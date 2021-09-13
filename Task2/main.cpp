#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include "Newton_method.h"
#include "Dichotomy_method.h"
#ifndef _DEBUG
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;
#endif
const double u = 1;
const double a = 2;
double function(double x)
{
	return -sqrt(2 * (u - x)) * tan(sqrt(2 * (u - x)) * a) + sqrt(2 * x);
}

double derivative_function(double x)
{
	return tan(sqrt(2 * (u - x)) * a) / sqrt(2 * (u - x)) * a + a / pow(cos(sqrt(2 * (u - x)) * a), 2) + 1 / sqrt(2 * x);
}
int main(void)
{
	double left = u - pow(M_PI, 2) / (8 * a * a);
	std::vector<double> newton_solves;
	std::cout << Newton_method(left, u, 1e-8, function, derivative_function).solve(newton_solves) << std::endl;
	left = u - pow(M_PI, 2) / (8 * a * a) + 1e-9;
	std::vector<double> dichotomy_solves;
	std::cout << Dichotomy_method(left, u - 1e-9, 1e-8, function, nullptr).solve(dichotomy_solves) << std::endl;
	std::vector<double> tan_y;
	std::vector<double> tan_x;
	double x = u - 25 * M_PI / (8 * a * a);
	if(x<0)
	{
		x = 0;
	}
	double wtf = u - 1e-9;
	for(int i=1;i>0;)
	{
		tan_x.push_back(x);
		tan_y.push_back(function(x));
		x += 0.001;
		if(x > wtf)
		{
			break;
		}
	}
#ifndef _DEBUG
	plt::scatter(tan_x, tan_y);
	plt::show();
#endif
	//
	tan_x.clear();
	tan_y.clear();
	x = u - 25 * M_PI / (8 * a * a);
	if (x < 0)
	{
		x = 0;
	}
	for (int i = 1; i > 0;)
	{
		tan_x.push_back(x);
		tan_y.push_back(tan(sqrt(2*(u-x)) * a));
		x += 0.001;
		if (x > u - 1e-9)
		{
			break;
		}
	}
	x = u - 25 * M_PI / (8 * a * a);
	if (x < 0)
	{
		x = 0;
	}

	std::vector<double> tanus_y;
	std::vector<double> tanus_x;
	for (int i = 1; i > 0;)
	{
		tanus_x.push_back(x);
		tanus_y.push_back(sqrt(x/(u-x)));
		x += 0.001;
		if (x > u - 1e-9)
		{
			break;
		}
	}
#ifndef _DEBUG
	plt::scatter(tan_x, tan_y);
	plt::scatter(tanus_x, tanus_y);
	plt::show();
#endif
}