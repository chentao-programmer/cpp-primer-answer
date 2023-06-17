#include <iostream>
#include <string>

using namespace std;

class Employee
{
public:
    Employee() : number(++gen) { }
    Employee(const string& s) : name(s), number(++gen) { }
    ostream & show(ostream & os);
    Employee(const Employee & e) = delete;
    Employee & operator=(Employee & e) = delete;
    ~Employee() = default;

private:
    string name;
    int number;
    static int gen;
};

ostream & Employee::show(ostream & os)
{
    os << name << " " << number;
    return os;
}

int Employee::gen = 0;

int main()
{
	Employee e("qwer"),e2;
	//Employee e1 = e;
    Employee e1("qwerty");
	e.show(cout) << endl;
	e1.show(std::cout) << std::endl;
	e2.show(std::cout) << std::endl;
	return 0;
}