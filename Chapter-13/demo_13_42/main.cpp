#include<iostream> 
#include<string>
#include<fstream> 
#include "TextQuery.h"

void runQueries(std::ifstream & infile)
{
    // infile是一个ifstream, 指向我们要处理的文件
	TextQuery tq(infile); // 保存文件并建立查询map
	while(true)
	{
		std::cout << "enter word to look for, or q to quit: " << std::endl;
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


