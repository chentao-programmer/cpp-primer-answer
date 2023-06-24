#include<set>
#include<string>
#include<iostream>
#include "Message.h"
/* save和remove成员函数 */
// 将本Message存放在给定的Folder中
void Message::save(Folder &f)
{
	folders.insert(&f); //将给定的Floder添加到我们的Floder列表中
	f.addMsg(this); // 将本Message添加到f的Message集合中
}

// remove删除本Message
void Message::remove(Folder &f)
{
	folders.erase(&f); //将给定的Floder从我们的Floder列表中移除
	f.remMsg(this); // 将本Message从f的Message集合中删除
}

// 将本Message添加到指向m的Floder中
void Message::add_to_Folders(const Message &m)
{
	for(Folder * f : m.folders)
		f->addMsg(this);
	std::cout << "Added message to folders" << std::endl; // debug
}

Message::Message(const Message &m) : contents(m.contents), folders(m.folders)
{
	add_to_Folders(m); // 将本Message添加到指向m的Floder中
}

void Message::remove_from_Folders()
{
	for(Folder * f : folders)
		f->remMsg(this); // 从该Floder中删除本Message
	std::cout << "Remove message from folders" << std::endl; // debug
}

Message::~Message()
{
	remove_from_Folders();
}

/*先从左侧运算对象的floders中删除此Message的指针，然后再将指针添加到右侧运算对象的floders中*/
// 拷贝赋值运算符
Message & Message::operator=(const Message &rhs)
{
	remove_from_Folders();
	contents = rhs.contents;
	folders = rhs.folders;
	std::cout << "Message members assgined" << std::endl; // debug
	add_to_Folders(rhs);
	return *this;
}

void Message::move_Folders(Message *m)
{
	folders = std::move(m->folders); // 使用set的移动赋值运算符
	for (Folder * f : folders)
	{		
		f->remMsg(m);	// 从Folder中删除旧Message
		f->addMsg(this);// 将本Message添加到Folder中
	}
	m->folders.clear(); // 确保销毁m是无害的
}

Message::Message(Message &&m) : contents(std::move(m.contents))
{
	move_Folders(&m);
}

Message & Message::operator=(Message && rhs)
{
	if (this != &rhs)
	{
		remove_from_Folders();
		contents = std::move(rhs.contents);
		move_Folders(&rhs);
	}
	std::cout << "Message members moved" << std::endl; // debug
	return *this;
}

void Message::addFolder(Folder *f)
{
	folders.insert(f);
}

void Message::remFolder(Folder *f)
{
	folders.erase(f);
}

void swap(Message &lhs, Message &rhs)
{
	using std::swap;
	for(Folder *f : lhs.folders)
		f->remMsg(&lhs);
	std::cout << "clear folder" << std::endl; // debug

	for(Folder *f : rhs.folders)
		f->remMsg(&rhs);
	std::cout << "clear folder" << std::endl; // debug

	swap(lhs.folders, rhs.folders);
	swap(lhs.contents, rhs.contents);
	std::cout << "Folder members swaped" << std::endl; // debug

	for(Folder *f : lhs.folders)
		f->addMsg(&lhs);
	std::cout << "Added messages to folder" << std::endl; // debug

	for(Folder *f : rhs.folders)
		f->addMsg(&rhs);
	std::cout << "Added messages to folder" << std::endl; // debug
}

std::ostream & Message::print(std::ostream & os) const
{
	os << contents << " " << folders.size();
	return os; 
}

void Folder::addMsg(Message *m)
{
	messages.insert(m);
}

void Folder::remMsg(Message *m)
{
	messages.erase(m);
}

void Folder::add_to_Messages(const Folder &f)
{
	for(Message * m : f.messages)
		m->addFolder(this);
	std::cout << "Added messages to folder" << std::endl; // debug
}

Folder::Folder(const Folder &f) : messages(f.messages)
{
	add_to_Messages(f);
}

void Folder::remove_from_Messages()
{
	for(Message * m : messages)
		m->remFolder(this);
	std::cout << "clear folder" << std::endl; // debug
}

Folder::~Folder()
{
	remove_from_Messages();
}

Folder & Folder::operator=(const Folder &f)
{
	remove_from_Messages();
	messages = f.messages;
	add_to_Messages(f);
	std::cout << "Folder members assigned" << std::endl; // debug
	return *this;
}

void Folder::show(std::ostream & os)
{
	os << "Folder:" << std::endl;
	for(Message * m : messages)
		m->print(os) << std::endl; 
}

void Folder::move_Message(Folder * f)
{
	messages = std::move(f->messages);
	for (Message *m : messages)
	{
		m->remFolder(f);
		m->addFolder(this);
	}
	f->messages.clear();
}

Folder::Folder(Folder &&f)
{
	move_Message(&f);
}

Folder & Folder::operator=(Folder && rhs)
{
	if (this != &rhs)
	{
		remove_from_Messages();
		move_Message(&rhs);
	}
	std::cout << "Message members moved" << std::endl; // debug
	return *this;
}