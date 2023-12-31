#include<string>
#include<iostream> 

class HasPtr
{
	friend void swap(HasPtr & lhs, HasPtr & rhs);
public:
	HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) { }
	HasPtr(const HasPtr & hp): ps(new std::string(*hp.ps)), i(hp.i) { }
	std::ostream & print(std::ostream & os)
	{
		os << *ps << " " << i;
		return os;
	}
	
	HasPtr & operator=(const HasPtr & rhs);
	
	~HasPtr() { delete ps; }
	
private:
	std::string *ps;
	int i;
};

HasPtr & HasPtr::operator=(const HasPtr & rhs)
{
	std::string * newp = new std::string(*rhs.ps);
	delete ps;
	ps = newp;
	i = rhs.i;
	return *this;
}

void swap(HasPtr & lhs, HasPtr & rhs)
{
	using std::swap;
	swap(lhs.ps, rhs.ps);
	swap(lhs.i, rhs.i);
	std::cout << "void swap(HasPtr & lhs, HasPtr & rhs)" << std::endl;
}

// void swap(HasPtr & lhs, HasPtr & rhs)
// {
// 	std::swap(lhs.ps, rhs.ps);
// 	std::swap(lhs.i, rhs.i);
// 	std::cout << "void swap(HasPtr & lhs, HasPtr & rhs)" << std::endl;
// }

int main()
{
	HasPtr a("12345"), c("67890");
	a.print(std::cout) << std::endl;
	HasPtr b = a;
	b.print(std::cout) << std::endl;
	b = c;
	b.print(std::cout) << std::endl;
	swap(a,c);
	a.print(std::cout) << std::endl;
	c.print(std::cout) << std::endl;
	return 0;
}

