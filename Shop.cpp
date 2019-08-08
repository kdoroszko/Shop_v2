#include "Shop.hpp"

Shop::Shop(Product* new_products_array)
{
    for (int i = 0; i < product_qty; ++i)
        products_in_shop.emplace_back(new_products_array[i]);
}

void Shop::show_articles() const
{
    std::cout << "\nDostepne produkty:\n";

    for (auto& elem : products_in_shop)
    {
        std::cout << elem.get_name() << " - ";
        show_price(elem.get_netto() * (100 + elem.get_VAT())/ 100);
        std::cout << " PLN\n";
    }

    char x = '1';
    std::cout << "\nAby wrocic do menu glownego wybierz ZERO: ";
    std::cin >> x;
    if (x == '0')
        return;
    else show_articles();
}

int Shop::shopping_list(Cart& new_cart)
{
    int amount = 0, total_amount = 0;

    std::cout << "\nPodsumowanie Twoich zakupow:\n\n";

    for (auto& elem : new_cart.getcart_map())
    {
        amount = elem.second * ((elem.first).get_netto() * (100 + (elem.first).get_VAT()) / 100);
        total_amount += amount;

        std::cout << (elem.first).get_name() << " - " << elem.second << " szt. - ";
        show_price(elem.second * (elem.first).get_netto());
        std::cout << " PLN netto - ";
        show_price(amount);
        std::cout << " PLN brutto, w tym VAT " << (elem.first).get_VAT() << "%\n";
    }

    (new_cart.getcart_map()).clear();

    return total_amount;
}

void Shop::pay(Cart& new_cart)
{
    std::cout << "\nDo zaplaty: ";
    show_price(shopping_list(new_cart));
    std::cout << " PLN\n";

    std::cout << "\nNacisnij dowolny przycisk i zatwierdz, aby wyjsc z programu.";
    int pause_no = 0;
    std::cin >> pause_no;
    exit(0);
}

void Shop::add_product(Cart& new_cart)
{
    std::cout << "\nWybierz produkt, ktory chcesz kupic. Nastepnie zostaniesz poproszony o podanie ilosci."
        " Pamietaj! Nie mozesz w koszyku miec wiecej niz 10 produktow, a te ktore sa w koszyku"
        " nie moga byc w ilosci wiekszej niz 25.\n";

    int counter = 1;
    std::unordered_map<int, std::string> counter_name;

    for (auto& elem : products_in_shop)
    {
        counter_name.emplace(counter, elem.get_name());
        std::cout << counter++ << " - " << elem.get_name() << '\n';
    }

    int what_to_buy = 0, pcs = 0;
    std::cin >> what_to_buy;
    std::cout << "Podaj ilosc: ";
    std::cin >> pcs;

    auto it = counter_name.find(what_to_buy);

    for (auto& elem : products_in_shop)
        if (elem.get_name() == it->second)
            new_cart.add_product(elem, pcs);
}