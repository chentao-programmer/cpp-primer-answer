#include <iostream>

class Base
{
public:
    void pub_men();
    void memfunc(Base &b) { b = *this; }
protected:
    int prot_mem;
private:
    char priv_mem;
};

struct Pub_Derv : public Base
{
	int f() { return prot_mem; }
	//char g() { return priv_mem; }
	void memfcn(Base &b) { b = *this; }
};

struct Priv_Derv : private Base
{
	int f1() const { return prot_mem; }
	void memfcn(Base &b) { b = *this; }
};

struct Prot_Derv : protected Base
{
	int f() const { return prot_mem; }
	void memfcn(Base &b) { b = *this; }
};

struct Derived_from_Public : public Pub_Derv
{
	int use_base()	{ return prot_mem; }
	void memfcn(Base &b) { b = *this; }
};

struct Derived_from_Private : public Priv_Derv
{
	//int use_base()	{ return prot_mem; }
	//void memfcn(Base &b) { b = *this; }
};

struct Derived_from_Protected : public Prot_Derv
{
	int use_base()	{ return prot_mem; }
	void memfcn(Base &b) { b = *this; }
};

int main()
{
    /*代码尝试将指向Base类的指针p指向Derived_from_Private类的对象dd2，但是这个操作是非法的，因为Derived_from_Private类使用了私有继承（private inheritance）。私有继承意味着基类的公有和保护成员在派生类中变为私有成员，而基类的私有成员在派生类中不可访问。由于Derived_from_Private类以私有继承方式继承Base类，它继承了Base类的所有成员，但这些成员在Derived_from_Private类中都变为私有成员，因此无法通过指向Base类的指针访问这些成员。*/
	Pub_Derv d1;
	Priv_Derv d2;
	Prot_Derv d3;
	Derived_from_Public dd1;
	Derived_from_Private dd2;
	Derived_from_Protected dd3;
	Base *p = &d1;
	//p = &d2;
	p = &dd1;
	//p = &dd2;
	//p = &dd3;
	
	return 0;
} 