#include<iostream> 
#include "Message.h"

int main()
{
	Folder f1;
	Message m1("qwerty");
	m1.save(f1);
	Message m2(m1);
	m2 = m2;
	m2.save(f1);
	f1.show(std::cout);
	Message * mp = new Message("asdfgh");
	Folder f2 = f1;
	f2 = f2;
	mp->save(f2);
	f2.show(std::cout);
	delete mp;
	m1.remove(f1);
	m1.remove(f2);
	f2.show(std::cout);
	return 0;
} 
/*
	创建一个空的文件夹 f1。
	创建一条消息 m1，内容为 "qwerty"，并将其存放在 f1 文件夹中。
	使用拷贝构造函数创建另一条消息 m2，内容和 m1 相同，并将其存放在 f1 文件夹中。
	将 m2 赋值给 m2 自身，没有实际效果。
	将 m2 存放在 f1 文件夹中。
	打印 f1 文件夹中的消息内容和数量。
	使用 new 运算符创建一条动态分配的消息 mp，内容为 "asdfgh"。
	创建一个新的文件夹 f2，并将其初始化为 f1 的副本。
	将 f2 赋值给 f2 自身，没有实际效果。
	将 mp 指向的消息存放在 f2 文件夹中。
	打印 f2 文件夹中的消息内容和数量。
	使用 delete 运算符删除动态分配的消息 mp。
	从 m1 所在的文件夹 f1 中删除 m1。
	打印 f2 文件夹中的消息内容和数量。
	请注意，代码中的 m2 = m2; 和 f2 = f2; 都是自赋值操作，它们不会产生实际效果。
*/