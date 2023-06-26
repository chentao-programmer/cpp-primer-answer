#ifndef TREE_H
#define TREE_H

#include <iostream>

class Tree
{
    friend bool operator==(const Tree &a, const Tree &b);
    friend bool operator!=(const Tree &a, const Tree &b);
    friend std::ostream & operator<<(std::ostream &os, const Tree &t);
    friend std::istream & operator>>(std::istream &is, Tree &t);

public:
    Tree() : Tree(0, nullptr, nullptr) { }
    Tree(int d) : Tree(d, nullptr, nullptr) { }
    Tree(int d, Tree *left, Tree *right) : data(d), left(left), right(right) { } 
private:
    int data = 0;
    Tree *left = nullptr;
    Tree *right = nullptr;
};

bool operator==(const Tree &a, const Tree &b)
{
    return a.data == b.data && a.left == b.left && a.right == b.right;
}

bool operator!=(const Tree &a, const Tree &b)
{
    return !(a == b);
}

std::ostream & operator<<(std::ostream &os, const Tree &t)
{
    os << t.data;
    return os;
}

std::istream & operator>>(std::istream &is, Tree &t)
{
    is >> t.data;
    if (!is) {
        t.data = 0;
    }
    return is;
}
#endif