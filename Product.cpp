#include "Product.hpp"

int Product::get_netto() const
{
    return netto;
}

int Product::get_VAT() const
{
    return VAT;
}

std::string Product::get_name() const
{
    return name;
}

bool Product::operator == (const Product &new_object) const
{
    return name == new_object.get_name();
}