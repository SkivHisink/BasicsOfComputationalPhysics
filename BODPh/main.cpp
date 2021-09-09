//It's test workspace for testing some features not for tasks
#include <iostream>
#include <bitset>

int main()
{
	std::cout << "Test workspace. It's not tasks." << std::endl;
	float in = 1.0f;
	for (int i = 0; i < 10000; ++i) {
		in /= 2;
		if(1.0f+in!=1.0f && 1.0f+in/2.0f==1.0f)
		{
			std::cout<<"Epsilon is: " << in<<std::endl;
			break;
		}
	}
	float test = 1e-37f;
	std::cout << test << std::endl;
	std::cout << std::numeric_limits<float>::epsilon() << std::endl;
	test = std::numeric_limits<float>::epsilon();
	int* p = (int*)&test;
	std::bitset<32> bits(*p);
	std::cout << bits << std::endl;
	std::cout << std::numeric_limits<double>::epsilon() << std::endl;
	test = std::numeric_limits<double>::epsilon();
	p = (int*)&test;
	std::bitset<32> bitss(*p);
	std::cout << bitss << std::endl;
}