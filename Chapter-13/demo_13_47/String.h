#ifndef DEMO_STRING_H
#define DEMO_STRING_H

#include <memory>
#include <utility>

class String
{
public:
    String() : elements(nullptr), first_free(nullptr), cap(nullptr) { }
    String(const char *);
    String(const String &);
    String & operator=(const String&);
    ~String() { free(); }

    void push_back(char c);
    size_t size() { return first_free - elements; }
    size_t capacity() { return cap - elements; }
    char * begin() { return elements; }
    char * end() { return first_free; }

    void reverse(size_t n);
    void resize(size_t n, char c = '\0');

private:
    void chk_n_alloc();
    std::pair<char *, char *> alloc_n_copy(const char *, const char *);
    void free();
    void reallocate();

    static std::allocator<char> alloc;
    
    char * elements;
    char * first_free;
    char * cap;
};

#endif