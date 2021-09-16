

#include <functional>
#include <iostream>
#include <string>

double Trapezoid_method(const double left_boundary_, const double right_boundary_,
	const double precision_, const std::function<double(double)>& function_,
	const std::function<double(double)>& derivative_)
{
	return (function_(left_boundary_) + function_(right_boundary_)) / 2 * (right_boundary_ - left_boundary_);
}
double Compound_Trapezoid_method(const double left_boundary_, const double right_boundary_,
	const double precision_, const std::function<double(double)>& function_, int number_of_parts)
{
	double result = 0.;
	double part = (right_boundary_ - left_boundary_) / number_of_parts;
	for (int i = 0; i < number_of_parts - 1; ++i)
	{
		double x_1 = left_boundary_ + part * i;
		double x_2 = x_1 + part;// left_boundary_ + part * (i + 1);
		result += (function_(x_1) + function_(x_2)) *
			(x_2 - x_1) / 2;
	}
	return result;
}
double Simpson_method(const double left_boundary_, const double right_boundary_,
	const double precision_, const std::function<double(double)>& function_, int number_of_parts)
{
	return (right_boundary_ - left_boundary_) /
		6 * (function_(left_boundary_) +
			4 * function_((left_boundary_ + right_boundary_) / 2) +
			function_(right_boundary_));
}
double Simpson_Kortes_method(const double left_boundary_, const double right_boundary_,
	const double precision_, const std::function<double(double)>& function_, int number_of_parts)
{
	double N = 2 * number_of_parts;
	double result = 0.;
	double part = (right_boundary_ - left_boundary_) / N;
	result += (function_(left_boundary_) + function_(right_boundary_));
	for (int i = 1; i < N / 2; ++i)
	{
		double x_1 = left_boundary_ + 2 * part * i;
		double x_2 = x_1 - part;
		if (i < (N / 2 - 1))
			result += 2 * function_(x_1);
		result += 4 * function_(x_2);
	}
	return part * result / 3;
}

double function_x(double x)
{
	return x;
}

double function_special_1(double x)
{
	return sin(x) + pow(cos(x), 2);
}

double function_task_1(double x)
{
	return 1 / (1 + pow(x, 2));
}

double function_task_2(double x)
{
	return pow(x, 1 / 3) * exp(sin(x));
}

void test(const double left_boundary_, const double right_boundary_,
	const double precision_, const std::function<double(double)>& function_, int number_of_parts, const std::string& answer)
{
	std::cout << "Trapezoid_method:" << Trapezoid_method(left_boundary_, right_boundary_, 0, function_, nullptr) << std::endl;
	std::cout << "Compound_Trapezoid_method:" << Compound_Trapezoid_method(left_boundary_, right_boundary_, 0, function_, number_of_parts) << std::endl;
	std::cout << "Simpson_method:" << Simpson_method(left_boundary_, right_boundary_, 0, function_, number_of_parts) << std::endl;
	std::cout << "Simpson_Kortes_method:" << Simpson_Kortes_method(left_boundary_, right_boundary_, 0, function_, number_of_parts) << std::endl;
	std::cout << "Correct anwser is " << answer << std::endl;
	std::cout << "--------------" << std::endl;
}
int main(void)
{
	//For x
	test(0, 10, 0, function_x, 40, "50");
	//For sin(x) + pow(cos(x), 2)
	test(0, 3, 0, function_special_1, 40, "3.4201");
	///Task
	//For 1/(1+x^2)
	test(-1, 1, 0, function_task_1, 40, "1.5708");
	//For pow(x, 1 / 3) * exp(sin(x))
	test(0, 1, 0, function_task_2, 500, "1.295874");
}
