#include <string>
#include<iostream> 

class HasPtr
{
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) { std::cout << "1: "; }
    HasPtr(const HasPtr& hp) : ps(new std::string(*hp.ps)), i(hp.i) {std::cout << "2: "; }
    std::ostream & print(std::ostream & os)
    {
        os << *ps << " " << i;
        return os;
    }
    // 复制运算符
    HasPtr & operator=(const HasPtr & hp);

    // 析构函数
    ~HasPtr() 
    {
        delete ps;
    }
private:
    std::string *ps;
    int i;
};

HasPtr & HasPtr::operator=(const HasPtr& hp)
{
    *ps = *(hp.ps);
    i = hp.i;
    std::cout << "3: ";
    return *this;
}

int main()
{
	HasPtr a("12345"), c("67890"); // 1: 1: 
    std::cout << std::endl;
	a.print(std::cout) << std::endl; // 12345 0
	HasPtr b = a; // 2:
	b.print(std::cout) << std::endl;
    b = c; // 3:
	b.print(std::cout) << std::endl;
	return 0;
}