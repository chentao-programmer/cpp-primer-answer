#ifndef QUOTE_H
#define QUOTE_H

#include <iostream>
#include <string>

class Quote
{
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price) { }

    std::string isbn() const { return bookNo; }

    virtual double net_price(std::size_t n) const;
    virtual std::ostream & debug(std::ostream &os) const;
    virtual ~Quote() = default;

private:
    std::string bookNo;

protected:
    double price = 0.0;
};

class Disc_quote : public Quote
{
public:
    Disc_quote() = default;
    Disc_quote(const std::string &book, double p, std::size_t q, double disc) : Quote(book, p), quantity(q), discount(disc) { }

    std::ostream & debug(std::ostream &os) const override;
    double net_price(std::size_t n) const = 0;

protected:
    std::size_t quantity = 0;
    double discount = 0.0;
};

class Bulk_quote : public Disc_quote
{
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string &book, double price, std::size_t qty, double dis) : Disc_quote(book, price, qty, dis) { }

    double net_price(std::size_t ) const override;
};

double print_total(std::ostream &os, const Quote &item, std::size_t n);

#endif