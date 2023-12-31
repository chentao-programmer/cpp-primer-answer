#include <iostream>
#include <string>
#include <vector>
#include <list>

template<typename T, typename U>
T find(T begin, T end, const U &value)
{
    while (begin != end) {
        if (*begin == value) {
            return begin;
        }
        begin++;
    }
    return end;
}

int main()
{
	std::vector<int> v1{1,2,34,5,66,77,56457,436,2,523,6,235};
	std::list<int> l1{1,2,34,5,66,77,56457,436,2,523,6,235};
	std::cout << *find(v1.begin(), v1.end(), 6) << std::endl;
	std::cout << *find(l1.cbegin(), l1.cend(), 6) << std::endl;
	return 0;
}