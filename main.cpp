#include <iostream>
#include <unordered_map>
#include "Product.hpp"
#include "Cart.hpp"
#include "Shop.hpp"

void show_price(int new_price)
{
    std::cout << new_price / 100 << ",";
    if (new_price % 100 < 10)
        std::cout << 0;
    std::cout << new_price % 100;
}

void Instruction(Shop new_shop, Cart new_cart)
{
    for (;;)
    {
        std::cout << "\nWitaj w sklepie. Wybierz dostepna z ponizszych opcji:\n"
            "1 - lista dostepnych produktow\n"
            "2 - dodaj produkt do koszyka\n"
            "3 - usun produkt z koszyka\n"
            "4 - pokaz stan koszyka\n"
            "5 - zaladuj zapis stanu koszyka\n"
            "6 - zaplac\n";

        char choice = '0';
        std::cin >> choice;

        if (choice == '1')
            new_shop.show_articles();
        if (choice == '2')
            new_shop.add_product(new_cart);
        if (choice == '3')
            new_cart.remove_product();
        if (choice == '4')
            new_cart.show_cart();
        if (choice == '5')
            new_cart.load_cart();
        if (choice == '6')
            new_shop.pay(new_cart);
    }
}

int main()
{
    Product Pomidor("Pomidor", 95, 8), Ogorek("Ogorek", 500, 8), Marchewka("Marchewka", 150, 8), Cebula("Cebula", 50, 8), Rzodkiewka("Rzodkiewka", 200, 8);
    Product Banan("Banan", 2000, 23), Jablko("Jablko", 500, 23), Gruszka("Gruszka", 600, 23), Truskawka("Truskawka", 1500, 23), Pozeczka("Pozeczka", 450, 23);
    Product Papryka("Papryka", 900, 8), Pieczarka("Pieczarka", 350, 8), Agrest("Agrest", 1000, 23), Borowka("Borowka", 3000, 23), Reklamowka("Reklamowka", 20, 90);
    Product ShopTable[15] = { Pomidor, Ogorek, Marchewka, Cebula, Rzodkiewka, Banan, Jablko, Gruszka, Truskawka, Pozeczka, Papryka, Pieczarka, Agrest, Borowka, Reklamowka };

    Shop Warzywniak(ShopTable);
    Cart Koszyk;

    Instruction(Warzywniak, Koszyk);

    return 0;
}