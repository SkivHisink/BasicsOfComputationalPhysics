#include "Entity.h"
#include <cmath>
bool Entity::check_result(double current, double previous)
{
	return abs(current - previous) < precision;
}

double Entity::solve()
{
	if (!is_valid()) {
		return WRONG_SOLUTION;
	}
	double prev = get_initial_value();
	for (size_t i = 0; i < number_of_iteration; ++i)
	{
		auto curr = get_next_value(prev);
		if (abs(curr) > 1e-20 && !std::isnormal(curr)) {
			break;
		}
		if (check_result(curr, prev)) {
			return curr;
		}
		prev = curr;
	}
	return WRONG_SOLUTION;
}