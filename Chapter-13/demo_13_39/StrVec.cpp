#include <string>
#include <memory>
#include <utility>
#include "StrVec.h"

std::allocator<std::string> StrVec::alloc;

void StrVec::push_back(const std::string &s)
{
	chk_n_alloc(); //确保有空间容纳新元素
    // 在first_free指向的元素中构造s的副本
	alloc.construct(first_free++, s);
}

std::pair<std::string*, std::string*> StrVec::alloc_n_copy(const std::string *b, const std::string *e)
{
    std::string * data = alloc.allocate(e - b);
    return {data, std::uninitialized_copy(b, e, data)};
}

void StrVec::free()
{
	if(elements)
	{
		for(std::string * p = first_free; p != elements; )
			alloc.destroy(--p);
		alloc.deallocate(elements, cap - elements);
	}
}

StrVec::StrVec(const StrVec & s)
{
    std::pair<std::string*, std::string*> newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::~StrVec()
{
    free();
}

StrVec & StrVec::operator=(const StrVec &s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());
    free();
    elements = newdata.first;
    first_free = cap = newdata.second;
    return *this;
}

void StrVec::reallocate()
{
    // 分配当前大小两倍的内存空间
	size_t newcapacity = size() ? 2 * size() : 1;
	reserve(newcapacity);
}

void StrVec::reserve(size_t n)
{
	if(n <= capacity())
		return;
    // 分配新内存
	std::string * newdata = alloc.allocate(n);
    // 将就内存移动到新内存
	std::string * dest = newdata;  // 指向新数组中下一个空闲位置
	std::string * elem = elements; // 指向旧数组中下一个位置
	for(size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*elem++));
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + n;
}

void StrVec::resize(size_t n, const std::string &t)
{
    if (n == size())
        return;
    if (n < size())
    {
        while (size() != n)
        {
            alloc.destroy(--first_free);
        }
        return;
    }
    if (n > capacity())
        reserve(n);
    while (n != size())
    {
        alloc.construct(first_free++, t);
    }
}
