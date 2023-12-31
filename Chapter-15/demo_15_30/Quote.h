#ifndef QUOTE_H
#define QUOTE_H

#include <iostream>
#include <string>
#include <utility>
#include <set>
#include <memory>

class Quote
{
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price) { }

    std::string isbn() const { return bookNo; }

    virtual double net_price(std::size_t n) const;
    virtual std::ostream & debug(std::ostream &os) const;
    virtual ~Quote() = default;
    
    virtual Quote * clone() const & { return new Quote(*this); }
    virtual Quote * clone() && { return new Quote(std::move(*this)); }

    Quote(const Quote &q) = default;
    Quote(Quote &&q) = default;
    Quote & operator=(const Quote &) = default;
    Quote & operator=(Quote &&) = default;

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

    Bulk_quote * clone() const & override { return new Bulk_quote(*this); }
    Bulk_quote * clone() && override { return new Bulk_quote(std::move(*this)); }

    double net_price(std::size_t ) const override;
};

class Basket
{
public:
    void add_item(const Quote &sale) { items.insert(std::shared_ptr<Quote>(sale.clone())); }
    void add_item(Quote &&sale){ items.insert(std::shared_ptr<Quote>(std::move(sale).clone())); }
	double total_receipt(std::ostream &) const;

private:
    static bool compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote> &rhs) {
        return lhs->isbn() < rhs->isbn();
    }

    std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{compare};
};
double print_total(std::ostream &os, const Quote &item, std::size_t n);

#endif