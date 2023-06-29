#include <iostream>
#include <functional>
#include <algorithm>
#include <map>
#include <string>
#include <sstream>

int add(int a, int b) 
{
    return a + b;
}

struct divide
{
    int operator()(int a, int b) {
        return a / b;
    }
};

int main()
{
    auto mod = [](int a, int b) {
        return a % b;
    };

    std::map<std::string, std::function<int(int, int)>> binops = {
        {"+", add}, {"-", std::minus<int>()}, {"/", divide()}, {"*", [](int a, int b) { return a * b; }}, {"%", mod}
    };
    std::string line;
    while (std::cin >> line) {
        int i, j;
        char o;
		std::istringstream is(line);
		is >> i;
		is >> o;
		is >> j;
		std::string op{o};
		std::cout << binops[op](i, j) << std::endl; 
    }
    return 0;
}