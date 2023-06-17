#include <iostream>
#include <vector>

using namespace std;

struct X
{
    // 构造函数
    X() { cout << "X()" << endl; }
    // 拷贝构造函数
    // const X&与const& X没有差别都表示对常量的引用
    X(const X&) { cout << "X(const X&)" << endl; }
    // 赋值运算符
    // *this表示当前对象的指针解引用。在成员函数内部，this指针是一个隐式参数，指向调用该成员函数的对象的地址。
    X & operator=(const X&) { cout << "X & operator=(const x&)" << endl; return *this; }
    // 析构函数
    ~X() { cout << "~X()" << endl; }
};

X fun1(X x1)
{
	return x1;
}

X & fun2(X & x1)
{
	return x1;
}

int main()
{
    X x1;
    X x2(x1);
    X x3 = x1;
    x2 = x1;

    std::cout << std::endl;

    X & x10  = x1;
    x2 = fun1(x1);
	x2 = fun2(x1);

    std::cout << std::endl;
    vector<X> vx1(3);
    vector<X> vx2(3, x1);
    return 0;
}