#include <iostream>
#include <string>

using namespace std;

class HasPtr
{
public:
    HasPtr(const string & s = string()) : ps(new string()), i(0), use(new size_t(1)) { }
    HasPtr(const HasPtr & p) : ps(new string(*p.ps)), i(p.i), use(p.use) { ++(*use); }
    HasPtr & operator=(const HasPtr & p);
    ~HasPtr();
    ostream & print(ostream & os) {
        cout << *ps << " " << i << " " << *use;
        return os;
    }
private:
    string *ps;
    int i;
    size_t *use; // 用来记录有多少个对象共享ps
};

HasPtr & HasPtr::operator=(const HasPtr & rhs)
{
    ++(*rhs.use);
    if (--*(use) == 0) {
        delete ps;
        delete use;
    }
    ps = rhs.ps;
    i = rhs.i;
    use = rhs.use;
    return *this;
}

HasPtr::~HasPtr()
{
    if (--(*use)) {
        delete ps;
        delete use;
    }
}

int main()
{
	HasPtr a("12345"), c("67890");
	a.print(std::cout) << std::endl;
	HasPtr b = a;
	b.print(std::cout) << std::endl;
	b = c;
	b.print(std::cout) << std::endl;
	return 0;
}
