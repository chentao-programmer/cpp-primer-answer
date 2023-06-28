#include<iostream>
#include<string>
#include<utility>
#include "StrVec.h"

int main()
{
	StrVec v;
	v.push_back("123");
	v.push_back("456");
	v.push_back("789");
	v = v;
	v = {"123", "456", "789"};
	StrVec v1 = v;
	for(std::string * p = v1.begin(); p != v1.end(); ++p)
		std::cout << *p << " ";
	std::cout << std::endl;
	v[1] = "12";
	std::cout << v[0] << " "<< v[1] << std::endl;
	return 0;
}