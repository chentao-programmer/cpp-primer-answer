#ifndef SHARED_PTR2_H
#define SHARED_PTR2_H

#include <functional>
#include <memory>
#include <stdexcept>

template <typename T> class shared_ptr2; // 前向声明，类模板中声明 shared_ptr2 类

template <typename T>
void swap(shared_ptr2<T> &rhs, shared_ptr2<T> &lhs); // swap 函数的前向声明，用于交换两个 shared_ptr2 对象的内容

template <typename T>
class shared_ptr2
{
public:
    //std::function<void (T*)> fp = nullptr 是用于指定删除函数的可选参数。如果不传递删除函数，默认为 nullptr，表示使用标准的 delete 运算符进行资源释放。
    shared_ptr2() : p(nullptr), ip(nullptr), delFun(nullptr) { }
    shared_ptr2(T* tp, std::function<void (T*)> fp = nullptr) : p(tp), ip(new int(1)), delFun(fp) { }
    shared_ptr2(shared_ptr2 &&sp, std::function<void (T*)> fp = nullptr);
    shared_ptr2(const shared_ptr2 &sp, std::function<void (T*)> fp = nullptr);
    shared_ptr2 & operator=(const shared_ptr2 &);
    shared_ptr2 & operator=(shared_ptr2 &&);
    ~shared_ptr2();
    void swap(shared_ptr2 &sp);

    T* get() const { return p; }
    T & operator*() const;
    T * operator->() const;
    explicit operator bool() const; // 将 shared_ptr2 转换为布尔值，用于判断指针是否为空。

    bool unique() const; // 返回指针是否是 shared_ptr2 的唯一所有者。
    int use_count() const; // 返回当前指针的引用计数。
    void reset(T* sptr = nullptr, std::function<void (T*)> fp = nullptr);

private:
    void destory();

    T *p;    // 指向动态分配对象的原始指针
    int *ip; // 指向引用计数的指针
    std::function<void (T*)> delFun; // 存储指向删除函数（deleter）的可调用对象
};

template <typename T>
shared_ptr2<T>::~shared_ptr2()
{
    destory();
}

template <typename T>
void shared_ptr2<T>::destory()
{
    // 如果 ip 和 p 都不为 nullptr，并且引用计数为 0
    if (ip != nullptr && p != nullptr && --*ip == 0) {
        // 如果存在删除函数 delFun，则调用删除函数释放资源，否则使用 delete 运算符释放资源
        delFun ? delFun(p) : delete p;

        p = nullptr;
        delete ip;
        ip = nullptr;
        delFun = nullptr;
    }
}

template <typename T>
shared_ptr2<T>::shared_ptr2(const shared_ptr2 &sp, std::function<void (T *)> fp) : p(sp.p), ip(sp.ip)
{
    ++*ip;
    if (fp == nullptr) {
        delFun = sp.delFun;
    }
    else {
        delFun = fp;
    }
}

template <typename T>
shared_ptr2<T> & shared_ptr2<T>::operator=(const shared_ptr2 & rhs)
{
    if (p != rhs.p) {
        destory();
        p = rhs.p;
        ip = rhs.ip;
        delFun = rhs.delFun;
        ++*ip;
    }
    return *this;
}

template <typename T>
shared_ptr2<T>::shared_ptr2(shared_ptr2 &&sp, std::function<void(T*)> fp) : p(std::move(sp.p)), ip(std::move(sp.ip))
{
    if (fp == nullptr) {
        fp = sp.delFun;
    }
    else {
        delFun = fp;
    }
    sp.p = nullptr;
    sp.ip = nullptr;
    sp.delFun = nullptr;
}

template <typename T>
shared_ptr2<T> & shared_ptr2<T>::operator=(shared_ptr2 && rhs)
{
    if (p != rhs.p) {
        destory();
        p = std::move(rhs.p);
        ip = std::move(rhs.ip);
        delFun = std::move(rhs.delFun);
        rhs.p = nullptr;
        rhs.ip = nullptr;
        rhs.delFun = nullptr;
    }
    else if (this != &rhs) {
        rhs.destory();
    }
    return *this;
}

template <typename T>
int shared_ptr2<T>::use_count() const
{
    if (ip != nullptr) {
        return *ip;
    }
    throw std::runtime_error("no count!");
}

template <typename T>
bool shared_ptr2<T>::unique() const
{
    if (use_count() == 1) {
        return true;
    }
    return false;
}

template <typename T>
T & shared_ptr2<T>::operator*() const
{
    if (p == nullptr) {
        throw std::runtime_error("no object!");
    }
    return *p;
}

template <typename T>
T * shared_ptr2<T>::operator->() const
{
    return & this->operator*();
}

template <typename T>
shared_ptr2<T>::operator bool() const
{
    if (p == nullptr) {
        return false;
    }
    return true;
}

template <typename T>
void shared_ptr2<T>::swap(shared_ptr2 & sp)
{
    using std::swap;
    swap(p, sp.p);
    swap(ip, sp.ip);
    swap(delFun, sp.delFun);
}

template <typename T>
void swap(shared_ptr2<T> &lhs, shared_ptr2<T> &rhs)
{
    lhs.swap(rhs);
}

template <typename T>
void shared_ptr2<T>::reset(T *sptr, std::function<void(T*)> fp)
{
    destory();
    p = sptr;
    if (p != nullptr) {
        ip = new int(1);
    }
    delFun = fp;
}

#endif