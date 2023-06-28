#include <iostream>
#include "Sales_data.h"

int main()
{
	Sales_data a(std::cin);
	std::string s = "12345";
	std::cout << (a = s) << std::endl;
	return 0;
}