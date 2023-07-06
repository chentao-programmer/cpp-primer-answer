#include <iostream>

template <typename T, unsigned U>
void print(const T (&arr)[U])
{
    for (const T &iter : arr) {
        std::cout << iter << " ";
    }
}

int main()
{
    int arr1[4] = {1, 2, 3, 4};
    double arr2[5] = {1,2,3,45,6};
	print(arr1);
    std::cout << std::endl;
	print(arr2); 
    return 0;
}