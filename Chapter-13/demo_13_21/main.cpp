#include<iostream> 
#include<string>
#include<fstream> 
#include "TextQuery.h"

void runQueries(std::ifstream & infile)
{
	TextQuery tq1(infile);
	TextQuery tq = tq1; 
	while(true)
	{
		std::cout << "enter word to look for, or q to quit: ";
		std::string s;
		if(!(std::cin >> s) || s == "q")
			break;
		print(std::cout, tq.query(s)) << std::endl;
	} 
} 

int main()
{
	std::ifstream ifs("1.txt");
	runQueries(ifs);
	
	return 0;	 
}

