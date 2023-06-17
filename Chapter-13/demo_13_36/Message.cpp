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
}

Message::Message(const Message &m) : contents(m.contents), folders(m.folders)
{
	add_to_Folders(m); // 将本Message添加到指向m的Floder中
}

void Message::remove_from_Folders()
{
	for(Folder * f : folders)
		f->remMsg(this); // 从该Floder中删除本Message
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
	add_to_Folders(rhs);
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
	for(Folder *f : rhs.folders)
		f->remMsg(&rhs);
		
	swap(lhs.folders, rhs.folders);
	swap(lhs.contents, rhs.contents);
	
	for(Folder *f : lhs.folders)
		f->addMsg(&lhs);
	for(Folder *f : rhs.folders)
		f->addMsg(&rhs);
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
}

Folder::Folder(const Folder &f) : messages(f.messages)
{
	add_to_Messages(f);
}

void Folder::remove_from_Messages()
{
	for(Message * m : messages)
		m->remFolder(this);
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
	return *this;
}

void Folder::show(std::ostream & os)
{
	os << "Folder:" << std::endl;
	for(Message * m : messages)
		m->print(os) << std::endl; 
}