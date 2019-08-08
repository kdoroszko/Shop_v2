#pragma once

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <functional>
#include <cstddef>
#include "Product.hpp"

void show_price(int new_price);

template <>
class std::hash<Product>
{
public:

    std::size_t operator () (const Product &new_object) const
    {
        std::size_t result = 2166136261;

        for (std::size_t i = 0, ie = (new_object.get_name()).size(); i != ie; ++i)
            result = (result * 16777619) ^ (new_object.get_name())[i];

        return result ^ (new_object.get_netto() << 1);
    }
};

//struct Hash_fn
//{
//public:
//
//    std::size_t operator () (Product const &new_object) const noexcept
//    {
//        std::size_t h1 = std::hash<Product>{}(new_object.get_name());
//        std::size_t h2 = std::hash<int>{}(new_object.get_netto());
//
//        return h1 ^ (h2 << 1);
//    }
//};

class Cart
{
public:

    std::unordered_map<Product, int> getcart_map();
    void add_product(const Product new_product, const int new_qty);
    void remove_product();
    void save_cart() const;
    void show_cart() const;
    void recreate_cart_from_file(std::ifstream* new_stream);
    void load_cart();

private:

    std::unordered_map<Product, int/*, Hash_fn*/> cart_map;
    static const int cart_capacity = 10;
    static const int max_qty_of_prod = 25;
};