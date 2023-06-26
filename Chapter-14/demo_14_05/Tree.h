#ifndef TREE_H
#define TREE_H

class Tree
{
    friend bool operator==(const Tree &a, const Tree &b);

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

#endif