#include<iostream>
#include<vector>
#include<utility>
#include "String.h"

int main()
{
	String s1("12345");
	String s = s1;
	std::cout << s << std::endl;
	s[1] = 'q';
	std::cout << s[0] << " "<< s[1] << std::endl;
	std::cout << s << std::endl;
	return 0;
}