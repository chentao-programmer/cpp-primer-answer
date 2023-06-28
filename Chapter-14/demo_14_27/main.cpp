#include<iostream>
#include<string>
#include<utility>
#include "StrBlob.h"

int main()
{
	StrBlob b1;
	std::string s;
	while(std::cin >> s)
		b1.push_back(std::move(s));
	StrBlob b2 = b1;
	StrBlobPtr pn = b1.begin();
	const StrBlobPtr pn1 = b1.begin();
	std::cout << pn[0] << " " << pn1[0] << " " << b1.cbegin()++[0] << std::endl;
	return 0;
} 
