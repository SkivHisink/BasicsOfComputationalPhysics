#include <iomanip>
#include <iostream>
#include <limits>
#include "Algorithms.hpp"

int main(void)
{
	std::cout << "Task 1.1 : Find computer epsilon" << std::endl;
	//float epsilon calculation
	std::cout << "	Float epsilon calculating and comparing:" << std::endl;
	std::cout << "		Founded epsilon with v1 = " << epsilon_float_search_v1() << ". Real epsilon = " << std::numeric_limits<float>::epsilon() << std::endl;
	std::cout << "		Founded epsilon with v2 = " << epsilon_float_search_v2() << ". Real epsilon = " << std::numeric_limits<float>::epsilon() << std::endl;
	std::cout << "		Founded epsilon with v3 = " << epsilon_float_search_v3() << ". Real epsilon = " << std::numeric_limits<float>::epsilon() << std::endl;
	//double epsilon calculation
	std::cout << "	Double epsilon calculating and comparing:" << std::endl;
	std::cout << "		Founded epsilon with v1 = " << epsilon_double_search_v1() << ". Real epsilon = " << std::numeric_limits<double>::epsilon() << std::endl;
	std::cout << "		Founded epsilon with v2 = " << epsilon_double_search_v2() << ". Real epsilon = " << std::numeric_limits<double>::epsilon() << std::endl;
	std::cout << "		Founded epsilon with v3 = " << epsilon_double_search_v3() << ". Real epsilon = " << std::numeric_limits<double>::epsilon() << std::endl;
	std::cout << "-----" << std::endl;
	/// Найти число разрядов в мантиссе
	std::cout << "Task 1.2 : Find number of digit in mantissa" << std::endl;
	std::cout << "	For float: " << calc_mantissa<float>() << std::endl;
	std::cout << "	For double: " << calc_mantissa<double>() << std::endl;
	std::cout << "-----" << std::endl;
	/// Найти максимальнуюи минимальную степени
	std::cout << "Task 1.3 : Find max and min pow of 10" << std::endl;
	std::cout << "	For float: max = " << calc_max_pow<float>()<<", min = "<<calc_min_pow<float>() << std::endl;
	std::cout << "	For double: max = " << calc_max_pow<double>()<<", min = "<<calc_min_pow<double>() << std::endl;
	std::cout << " Real double exponent 10:max = " << std::numeric_limits<double>::max_exponent10<<", min = "<<std::numeric_limits<double>::min_exponent10 << std::endl;
	std::cout << " Real float max exponent 10:max = " << std::numeric_limits<double>::max_exponent10 << ", min = " << std::numeric_limits<double>::min_exponent10 << std::endl;
	std::cout << "-----" << std::endl;
	/// Найти максимальнуюи минимальную степени
	std::cout << "Task 1.3 : Find max and min pow of 2" << std::endl;
	std::cout << "	For float: max = " << calc_max_pow_of_two<float>() << ", min = " << calc_min_pow_of_two<float>() << std::endl;
	std::cout << "	For double: max = " << calc_max_pow_of_two<double>() << ", min = " << calc_min_pow_of_two<double>() << std::endl;
	std::cout << " Real double exponent 2:max = " << std::numeric_limits<double>::max_exponent << ", min = " << std::numeric_limits<double>::min_exponent << std::endl;
	std::cout << " Real float max exponent 2:max = " << std::numeric_limits<float>::max_exponent << ", min = " << std::numeric_limits<float>::min_exponent << std::endl;
	std::cout << "-----" << std::endl;
	/// Comparing
	/// Запишем некоторые размышления.
	/// Пусть у нас будет 3 точки: 1, 1+epsilon,1 + 2 * epsilon.
	/// При 1 + epsilon /2 наше значение находится между первыми двумя точками, причём 1 чётная,
	/// поскольку её младший бит равен 0, а 1 + epsilon нечётное отсюда происходит округление в меньшую сторону согласно стандарту IEEE 754.
	/// В ситуации 1 + epsilon + epsilon / 2 мы сначала попадаем в точку 1 + epsilon и начинаем находится между нечётным и чётным, округление идёт в чётную сторону поэтому мы получаем,
	/// что 1 + epsilon + epsilon / 2 == 1 + 2 * epsilon
	float* arr = comparing<float>();
	std::cout << "Task 1.4 : Compare numbers: 1, 1 + epsilon / 2, 1 + epsilon, 1 + epsilon + epsilon / 2" << std::endl;
	std::cout << "	For float:" << std::setprecision(10) << arr[0] << ", " << arr[1] << ", " << arr[2] << ", " << arr[3] << std::endl;
	delete[] arr;
	double* arr_d = comparing<double>();
	std::cout << "	For double:" << std::setprecision(18) << arr_d[0] << ", " << arr_d[1] << ", " << arr_d[2] << ", " << arr_d[3] << std::endl;
	delete[] arr_d;
	return 0;
}
