#include <memory>
#include <utility>
#include <algorithm>
#include <iostream>
#include "String.h"

std::allocator<char> String::alloc;

void String::chk_n_alloc()
{
    if (size() == capacity()) {
        reallocate();
    }
}

void String::push_back(char c)
{
    chk_n_alloc();
    alloc.construct(first_free++, c);
}

std::pair<char *, char *> String::alloc_n_copy(const char *b, const char *e)
{
    char *data = alloc.allocate(e - b);
    return {data, std::uninitialized_copy(b, e, data)};
}

void String::free()
{
    if (elements) {
        std::for_each(elements, first_free, [](char &c){
            alloc.destroy(&c);
        });
        alloc.deallocate(elements, capacity());
    }
}

void String::reallocate()
{
    size_t newCapacity = size() ? size() * 2 : 1;
    reverse(newCapacity);
}

void String::reverse(size_t n)
{
    if (n < capacity())
        return;
    char *newData = alloc.allocate(n);
    char *dest = newData;
    char *elem = elements;
    for (size_t i = 0; i != size(); i++) {
        alloc.construct(dest++, std::move(*elem++));
    }
    free();
    elements = newData;
    first_free = dest;
    cap = elements + n;
}

void String::resize(size_t n, char c)
{
    if (n == size())
        return;
    if (n < size()) {
        while (size() != n) {
            alloc.destroy(--first_free);
        }
        return;
    }
    if (n > capacity()) {
        reverse(n);
    }
    while (size() != n) {
        alloc.construct(first_free++, c);
    }
}

String::String(const String &s)
{
    std::cout << "String(const String & s)" << std::endl;
    std::pair<char*, char*> newData = alloc_n_copy(s.elements, s.first_free);
    elements = newData.first;
    first_free = cap = newData.second;
}

String & String::operator=(const String & rhs)
{
    std::cout << "String & operator=(const String & rhs)" << std::endl;
    std::pair<char*, char*> newData = alloc_n_copy(rhs.elements, rhs.first_free);
    free();
    elements = newData.first;
    first_free = cap = newData.second;
    return *this;
}

String::String(const char *ps)
{
    const char *p = ps;
    while (*p != '\0')
        p++;
    std::pair<char*, char*> newData = alloc_n_copy(ps, p);
    elements = newData.first;
    first_free = cap = newData.second;
}