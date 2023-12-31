#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <iostream>
#include <string>

struct Sales_data;

Sales_data operator+(const Sales_data &sa, const Sales_data &sb);

std::istream & operator>>(std::istream &is, Sales_data &sa);

std::ostream & operator<<(std::ostream &os, Sales_data &sa);

bool operator==(const Sales_data &lhs, const Sales_data &rhs);

bool operator!=(const Sales_data &lhs, const Sales_data &rhs);

class Sales_data
{
    friend Sales_data operator+(const Sales_data &sa, const Sales_data &sb);
    friend std::istream & operator>>(std::istream &is, Sales_data &sa);
    friend std::ostream & operator<<(std::ostream &os, Sales_data &sa);
    friend bool operator==(const Sales_data &lhs, const Sales_data &rhs);

public:
    Sales_data() = default;
    Sales_data(const Sales_data &s) : ISBN(s.ISBN) { }
    Sales_data(const Sales_data &s, int a, double t) : ISBN(s.ISBN), amount(a), totalPrice(t * a) { }
    Sales_data(std::istream &is)
    {
        is >> *this;
    }

    std::string isbn() const
    {
        return ISBN;
    }

    Sales_data & operator+=(const Sales_data &sa);

private:
    std::string ISBN;
    double totalPrice = 0.0;
    int amount = 0;

    inline double avg_price() const;
};

#endif