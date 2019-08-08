#pragma once

#include <string>

class Product
{
public:

    Product(std::string new_name = "NULL", int new_price = 0, int new_tax = 0)
        : name(new_name), netto(new_price), VAT(new_tax) {}

    int get_netto() const;
    int get_VAT() const;
    std::string get_name() const;
    bool operator == (const Product &new_object) const;

private:

    const int netto, VAT; // CENA PODANA JEST W GROSZACH
    const std::string name;
};