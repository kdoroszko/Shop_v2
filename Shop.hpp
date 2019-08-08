#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "Cart.hpp"
#include "Product.hpp"

void show_price(int newprice);

class Shop
{
public:

    Shop(Product* new_products_array);

    void show_articles() const;
    int shopping_list(Cart& new_cart);
    void pay(Cart& new_cart);
    void add_product(Cart& new_cart);

private:

    std::vector<Product> products_in_shop;
    static const int product_qty = 15;
};