#ifndef STRVEC_H
#define STRVEC_H

#include <iostream>
#include <memory>
#include <utility>
#include <initializer_list>

class StrVec
{
    friend bool operator==(const StrVec &lhs, const StrVec &rhs);
    friend bool operator!=(const StrVec &lhs, const StrVec &rhs);
    friend bool operator<(const StrVec &lhs, const StrVec &rhs);
	friend bool operator>(const StrVec &lhs, const StrVec &rhs);
public:

    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) { }
    StrVec(std::initializer_list<std::string> li);
    StrVec(const StrVec &); // 拷贝构造函数 （测试加sv与不加sv的区别）
    StrVec& operator=(const StrVec &);
    ~StrVec();

    StrVec(StrVec &&) noexcept;
    StrVec& operator=(StrVec &&) noexcept;
    StrVec& operator=(std::initializer_list<std::string> li);
    
    void push_back(const std::string &);
    void push_back(std::string &&);
    size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
	std::string *end() const { return first_free; } 

    void reserve(size_t);
    void resize(size_t n, const std::string &t = std::string());
private:

    static std::allocator<std::string> alloc; // 分配元素
    // 被添加元素的函数所用
    void chk_n_alloc()
    {
        if (size() == capacity())
            reallocate();
    }
    // 工具函数，被拷贝构造函数，赋值运算符和析构函数所用
    std::pair<std::string *, std::string *> alloc_n_copy(const std::string *, const std::string *);
    void free(); // 销毁元素并释放元素
    void reallocate(); // 获得更多内存并拷贝已有元素

    std::string *elements; //指向数组首元素的指针
    std::string *first_free; // 指向数组第一个空闲元素的指针
    std::string *cap; // 指向数组尾后位置的指针
};

bool operator==(const StrVec &lhs, const StrVec &rhs);
bool operator!=(const StrVec &lhs, const StrVec &rhs);
bool operator<(const StrVec &lhs, const StrVec &rhs);
bool operator<=(const StrVec &lhs, const StrVec &rhs);
bool operator>(const StrVec &lhs, const StrVec &rhs);
bool operator>=(const StrVec &lhs, const StrVec &rhs);

#endif