#ifndef UNIQUE_PTR2
#define UNIQUE_PTR2

#include <iostream>
#include <stdexcept>

class unique_ptr2_delete
{
public:
    unique_ptr2_delete() = default;
    template <typename F> void operator()(F *p) { std::cout << "unique_ptr2_delete!" << std::endl; delete p; }
};

template <typename T, typename F> class unique_ptr2;

template <typename T, typename F>
void swap(unique_ptr2<T, F> &lhs, unique_ptr2<T, F> &rhs);

template <typename T, typename F = unique_ptr2_delete>
class unique_ptr2
{
public:
    unique_ptr2() : p(nullptr), delFun(unique_ptr2_delete()) { }
    unique_ptr2(T *up, F fun = unique_ptr2_delete()) : p(up), delFun(fun) { }
    unique_ptr2(F upd) : p(nullptr), delFun(upd) { }
    ~unique_ptr2();

    explicit operator bool() const;
    T & operator*() const;
    T * operator->() const;
    T * get() const;
    void swap(unique_ptr2 &lhs);

    unique_ptr2 & operator=(T *up);
    unique_ptr2(const unique_ptr2 &up) = delete;
    unique_ptr2 & operator=(const unique_ptr2 &lhs) = delete;
    unique_ptr2(unique_ptr2 &&);
    unique_ptr2 & operator=(unique_ptr2 &&);
    
    T* release();
    void reset(T *up = nullptr);
private:
    T *p;
    F delFun;
};

template <typename T, typename F>
unique_ptr2<T, F>::~unique_ptr2()
{
    delFun(p);
}

template <typename T, typename F>
unique_ptr2<T, F>::operator bool() const
{
    if (p == nullptr) {
        return false;
    }
    return true;
}

template <typename T, typename F>
T & unique_ptr2<T, F>::operator*() const
{
    if (p == nullptr) {
        throw std::runtime_error("no object!");
    }
    return *p;
}

template <typename T, typename F>
T * unique_ptr2<T, F>::operator->() const
{
    if (p == nullptr) {
        throw std::runtime_error("no object!");
    }
    return & this->operator*();
}

template <typename T, typename F>
T * unique_ptr2<T, F>::get() const
{
    return p;
}

template <typename T, typename F>
void unique_ptr2<T, F>::swap(unique_ptr2<T, F> &up)
{
    using std::swap;
    swap(p, up.p);
    swap(delFun, up.delFun);
}

template <typename T, typename F>
unique_ptr2<T, F> & unique_ptr2<T, F>::operator=(T * up)
{
    if (up != nullptr) {
        throw std::runtime_error("Prohibition of assignment!");
    }
    p = nullptr;
    return *this;
}

template <typename T, typename F>
unique_ptr2<T, F>::unique_ptr2(unique_ptr2<T, F> &&up)
{
    p = std::move(up.p);
    delFun = std::move(up.delFun);
    up.p = nullptr;
}

template <typename T, typename F>
unique_ptr2<T, F> & unique_ptr2<T, F>::operator=(unique_ptr2<T, F> &&up)
{
    if (this != &up) {
        delFun(p);
        p = std::move(up.p);
        delFun = std::move(up.delFun);
        up.p = nullptr;
    }
    return *this;
}

template <typename T, typename F>
T* unique_ptr2<T, F>::release()
{
    T * temp = p;
    p = nullptr;
    return temp;
}

template <typename T, typename F>
void unique_ptr2<T, F>::reset(T *up)
{
    if (p != nullptr) {
        delFun(p);
    }
    p = up;
}

#endif