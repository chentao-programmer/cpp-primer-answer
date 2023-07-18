#include<iostream>
#include<memory>
#include "DebugDelete.h"

int main()
{
    // 使用 std::unique_ptr 创建一个指向 int 类型对象的智能指针 u1，并同时传入自定义的删除器 DebugDelete
	std::unique_ptr<int, DebugDelete> u1(new int(3), DebugDelete());
	std::cout << *u1 << std::endl;
    // 使用 reset() 将 u1 重置，会触发 DebugDelete 删除器的调用，并释放动态分配的内存
	u1.reset();
    // 在此处，u1 已经不再指向任何对象，因为 reset() 将其重置为 nullptr
    // 在此之后，u1 的生命周期结束时不会再触发删除器的调用
    
	std::unique_ptr<double, DebugDelete> u2(new double(3.0), DebugDelete());
	std::cout << *u2 << std::endl;
	u2.reset();
	
	int * i = new int(4);
	DebugDelete()(i);
	
	return 0;
}