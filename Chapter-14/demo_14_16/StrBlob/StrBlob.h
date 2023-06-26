#ifndef STRBLOB_H
#define STRBLOB_H

#include <vector>
#include <string>
#include <initializer_list>
#include <memory>

class StrBlob;
class StrBlobPtr;
class ConstStrBlobPtr;

bool operator==(const StrBlob &lhs, const StrBlob &rhs);

bool operator!=(const StrBlob &lhs, const StrBlob &rhs);

/*
    strBlob是一个简单的字符串容器，使用了智能指针shared_ptr来管理内部的vector<string>对象，同时还定义了迭代器类StrBlobPtr与ConstStrBlobPtr，用于遍历容器的元素。
*/
class StrBlob
{
    friend class StrBlobPtr;
    friend class ConstStrBlobPtr;
    friend bool operator==(const StrBlob &lhs, const StrBlob &rhs);
    friend bool operator!=(const StrBlob &lhs, const StrBlob &rhs);
public:
    typedef std::vector<std::string>::size_type size_type;

    // 默认构造函数
    StrBlob();
    // 初始化列表构造函数
    StrBlob(std::initializer_list<std::string> li);
    // 拷贝构造函数
    StrBlob(const StrBlob &sb);
    // 重载赋值运算符
    StrBlob & operator=(const StrBlob &sb);

    // 移动构造函数
    StrBlob(StrBlob &&sb) noexcept;
    // 移动赋值运算符
    StrBlob & operator=(StrBlob && sb) noexcept;

    inline size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const std::string &s) { data->push_back(s); }
    void push_back(std::string &&s);
    void pop_back();

    const std::string & front() const;
    std::string & front();
    const std::string & back() const;
    std::string & back();

    // 返回容器的迭代器StrBlobPtr的起始和结束位置。
    StrBlobPtr begin();
    StrBlobPtr end();
    // 返回容器的常量迭代器ConstStrBlobPtr的起始和结束位置。
    ConstStrBlobPtr cbegin() const;
    ConstStrBlobPtr cend() const;
private:
    // 成员变量data，指向vector<string>的shared_ptr，用于存储字符串数据
    std::shared_ptr<std::vector<std::string>> data;
    // 辅助函数，用于检查给定的索引是否有效。
    void check(size_type i, const std::string &msg) const;
};

// 迭代器类，用于遍历StrBlob容器的元素。
class StrBlobPtr
{
    friend bool compare(const StrBlobPtr &p1, const StrBlobPtr &p2);
    friend bool operator==(const StrBlobPtr &lhs, const StrBlobPtr &rhs);
    friend bool operator==(const StrBlobPtr &lhs, const StrBlobPtr &rhs);

public:
    // 默认构造函数
    StrBlobPtr() : curr(0) { }
    // 带参构造函数，使用StrBlob对象和初始位置创建迭代器。
    StrBlobPtr(StrBlob &a, std::size_t sz = 0) : wptr(a.data), curr(sz) { }

    // 返回当前迭代器指向位置的字符串引用。
    std::string & deref() const;
    // 将迭代器向前移动一个位置，并返回自身的引用。
    StrBlobPtr & incr();
    // 将迭代器向前移动指定的步数，并返回自身的引用。
    StrBlobPtr & add(StrBlob::size_type num);
private:
    /*
        成员变量：
            wptr：指向StrBlob容器的std::weak_ptr，用于检测容器是否被销毁。
            curr：当前迭代器指向的位置。
    */
    std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string &) const;
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;
};

// 常量迭代器类，与StrBlobPtr类似，但是不允许修改容器的元素。
class ConstStrBlobPtr
{
	friend bool compare(const ConstStrBlobPtr &p1, const ConstStrBlobPtr &p2);
    friend bool operator==(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);
    friend bool operator!=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);

public:
	ConstStrBlobPtr() : curr(0) { }
	ConstStrBlobPtr(const StrBlob &a, std::size_t sz = 0) : wptr(a.data), curr(sz) { }
	
	std::string & deref() const;
	ConstStrBlobPtr & incr();
	
private:
	std::shared_ptr<std::vector<std::string>> check(std::size_t , const std::string &) const;
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr;
};

#endif