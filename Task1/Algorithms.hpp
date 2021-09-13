#pragma once
#define FLOAT_CONDITION(x) (1.0f+x!=1.0f && 1.0f+x/2==1.0f)
#define RIGHT_FLOAT_CONDITION(x) !(1.0f+x/2>1.0f)
#define NUMBER_OF_ITERATIONS 1000000
#include <bitset>
namespace {
	template<typename T>
	T floating_simple_search(bool(*condition)(T))
	{
		T epsilon = static_cast<T>(1);
		for (int i = 0; i < NUMBER_OF_ITERATIONS; ++i)
		{
			if (condition(epsilon))
			{
				return epsilon;
			}
			epsilon /= static_cast<T>(2);
		}
		return static_cast<T>(-1);
	}

	template<typename T>
	T BSearch(T l_val, T r_val, bool(*l_condition)(T), bool(*r_condition)(T), T precision)
	{
		T m_val;
		for (int i = 0; i < NUMBER_OF_ITERATIONS; ++i)
		{
			m_val = (l_val + r_val) / static_cast<T>(2);
			if (std::abs(m_val - l_val) < precision || std::abs(m_val - r_val) < precision)
			{
				return m_val;
			}
			if (l_condition(m_val))
			{
				l_val = m_val;
			}
			else if (r_condition(m_val))
			{
				r_val = m_val;
			}
		}
		return static_cast<T>(-1);
	}
	template<typename T>
	int calc_mantissa()
	{
		int mantissa = 0;
		for (int i = 0; i < NUMBER_OF_ITERATIONS; ++i)
		{
			if (static_cast<T>(1) + static_cast<T>(std::pow(2, -1 * mantissa)) == static_cast<T>(1))
			{
				return mantissa - 1;
			}
			++mantissa;
		}
		return -1;
	}

	template<typename T>
	int calc_min_pow()
	{
		int min_pow = -1;
		T prev = 1;
		for (int i = 0; i < NUMBER_OF_ITERATIONS; ++i)
		{
			T temp = static_cast<T>(std::pow(10, min_pow));
			if (temp >= prev)
			{
				return min_pow + 2;
			}
			prev = static_cast<T>(std::pow(10, min_pow));
			--min_pow;
		}
		return -1;
	}

	template<typename T>
	int calc_max_pow()
	{
		int max_pow = 1;
		T prev = 0;
		for (int i = 0; i < NUMBER_OF_ITERATIONS; ++i)
		{
			T temp = static_cast<T>(std::pow(10, max_pow));
			if (temp <= prev)
			{
				return max_pow - 2;
			}
			prev = temp;
			++max_pow;
		}
		return -1;
	}

	template<typename T>
	int calc_min_pow_of_two()
	{
		int min_pow = -1;
		T prev = 1;
		for (int i = 0; i < NUMBER_OF_ITERATIONS; ++i)
		{
			T temp = static_cast<T>(std::pow(2, min_pow));
			if (temp >= prev)
			{
				return min_pow;
			}
			prev = temp;
			--min_pow;
		}
		return -1;
	}

	template<typename T>
	int calc_max_pow_of_two()
	{
		int max_pow = 1;
		T prev = 0;
		for (int i = 0; i < NUMBER_OF_ITERATIONS; ++i)
		{
			T temp = static_cast<T>(std::pow(2, max_pow));
			if (temp >= prev)
			{
				return max_pow;
			}
			prev = temp;
			++max_pow;
		}
		return -1;
	}
	template<typename T>
	T* comparing()
	{
		T epsilon = std::numeric_limits<T>::epsilon();
		T* array = new T[4];
		array[0] = static_cast<T>(1);
		array[1] = static_cast<T>(static_cast<T>(1 + epsilon / static_cast <T>(2)));
		array[2] = static_cast<T>(static_cast<T>(1 + epsilon));
		array[3] = static_cast<T>(static_cast<T>(1 + epsilon + epsilon / static_cast <T>(2)));
		return array;
	}
}

static float epsilon_float_search_v1()
{
	auto condition = [](float epsilon) {return 1.0f + epsilon != 1.0f && 1.0f + epsilon / 2 == 1.0f; };
	//auto condition = [](float epsilon) {return 1.0f + x / 2 > 1.0f; };
	return floating_simple_search<float>(condition);
}
/// <summary>
/// Due to IEEE 754 format we need 1 in mantissa and 104 shifted to 23
/// https://en.wikipedia.org/wiki/IEEE_754-1985
/// </summary>
/// <returns></returns>
static float epsilon_float_search_v2()
{
	float epsilon;
	// 0000 0000 - 0 byte
	// 0000 0000 - 1 byte
	// 0000 0000 - 2 byte
	// 0000 0000 - 3 byte
	*reinterpret_cast<int*>(&epsilon) = 1;
	// 0011 0100 - 0 byte
	// 0000 0000 - 1 byte
	// 0000 0000 - 2 byte
	// 0000 0000 - 3 byte
	*reinterpret_cast<int*>(&epsilon) = *reinterpret_cast<int*>(&epsilon) | 104 << 23;
	return epsilon;
}

float epsilon_float_search_v3()
{
	auto left_condition = [](float epsilon) {return 1.f + epsilon / 2.f == 1.f; };
	auto right_condition = [](float epsilon) {return 1.f + epsilon != 1.f; };
	return BSearch<float>(0.f, 2.f, left_condition, right_condition, 1e-39f);
}

double epsilon_double_search_v1()
{
	auto condition = [](double epsilon) {return 1.0 + epsilon != 1.0 && 1.0 + epsilon / 2 == 1.0; };
	//auto condition = [](float epsilon) {return 1.0 + x / 2 > 1.0; };
	return floating_simple_search<double>(condition);
}
/// <summary>
/// Due to IEEE 754 format we need 1 in mantissa and 971 shifted to 52
/// https://en.wikipedia.org/wiki/IEEE_754-1985
/// </summary>
/// <returns></returns>
double epsilon_double_search_v2()
{
	double epsilon;
	*reinterpret_cast<unsigned long long*>(&epsilon) = 1;
	*reinterpret_cast<unsigned long long*>(&epsilon) = *reinterpret_cast<unsigned long long*>(&epsilon) | 971ULL << 52;
	return epsilon;
}

double epsilon_double_search_v3()
{
	auto left_condition = [](double epsilon) {return 1. + epsilon / 2. == 1.; };
	auto right_condition = [](double epsilon) {return 1. + epsilon != 1.; };
	return BSearch<double>(0., 2., left_condition, right_condition, 1e-32);
}
