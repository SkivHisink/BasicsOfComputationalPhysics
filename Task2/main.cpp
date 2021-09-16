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
const double u = 10;
const double a = 5;
double function_x(double x)
{
	return -sqrt(2 * (u - x)) * tan(sqrt(2 * (u - x)) * a) + sqrt(2 * x);
}

double derivative_function(double x)
{
	return tan(sqrt(2 * (u - x)) * a) / sqrt(2 * (u - x)) * a + a / pow(cos(sqrt(2 * (u - x)) * a), 2) + 1 / sqrt(2 * x);
}

double for_method_of_simple_iteration(double x)
{
	return 1000;
}
int main(void)
{
	double left = u - pow(M_PI, 2) / (8 * a * a);
	double precision = 1e-15;
	if (left <= 0) left = precision;
	std::vector<double> newton_solves;
	std::vector<double> simple_iteration_solves;
	std::cout << Newton_method(left, u, precision, function_x, derivative_function).solve(newton_solves) << std::endl;
	std::cout << Newton_method(left, u, precision, function_x, for_method_of_simple_iteration).solve(simple_iteration_solves) << std::endl;

	left = u - pow(M_PI, 2) / (8 * a * a) + 1e-9;
	std::vector<double> dichotomy_solves;
	std::cout << Dichotomy_method(left, u - 1e-15, precision, function_x, nullptr).solve(dichotomy_solves) << std::endl;
#ifndef _DEBUG
	plt::named_plot("newton", newton_solves);
	plt::named_plot("dichotomy", dichotomy_solves);
	plt::legend();
	plt::show();
#endif
	std::vector<double> tan_y;
	std::vector<double> tan_x;
	double x = 0;//u - 25 * M_PI / (8 * a * a);
	if (x < 0)
	{
		x = 0;
	}
	double wtf = u - 1e-9;
	for (int i = 1; i > 0;)
	{
		tan_x.push_back(x);
		tan_y.push_back(function_x(x));
		x += 0.001;
		if (x > wtf)
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
		tan_y.push_back(tan(sqrt(2 * (u - x)) * a));
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