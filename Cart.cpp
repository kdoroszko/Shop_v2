#include "Cart.hpp"

std::unordered_map<Product, int> Cart::getcart_map()
{
    return cart_map;
}

void Cart::add_product(const Product new_product, const int new_qty) //Dlaczego dziala .find() na stringu, skoro cart_map sklada sie z Product i int?!
{
    auto it = cart_map.find(new_product.get_name());

    if (it != cart_map.end())
    {
        if (it->second + new_qty > max_qty_of_prod)
            std::cout << "Nie zmiesci sie tyle w koszyku.\n";
        else
        {
            it->second += new_qty;
            std::cout << "Dodales do koszyka " << new_product.get_name() << ", w ilosci: " << new_qty << '\n';
        }

        return;
    }

    if (cart_map.size() >= cart_capacity)
    {
        std::cout << "W koszyku jest juz 10 roznych produktow. Aby dodac kolejny usun przynajmniej jeden produkt z koszyka.\n";
        return;
    }

    if (new_qty > max_qty_of_prod)
        std::cout << "Nie zmiesci sie tyle w koszyku.\n";
    else
    {
        cart_map.emplace(new_product, new_qty);
        std::cout << "Dodales do koszyka " << new_product.get_name() << ", w ilosci: " << new_qty << '\n';
    }
}

void Cart::remove_product()
{
    int counter = 1;
    std::unordered_map<int, std::string> counter_name;

    std::cout << "\nW koszyku znajduja sie produkty wypisane ponizej:\n";
    for (auto& elem : cart_map)
    {
        counter_name.emplace(counter, (elem.first).get_name());
        std::cout << counter++ << " - " << (elem.first).get_name() << '\n';
    }

    int choice = 0;
    std::cout << "\nWybierz produkt, ktory chcesz usunac z koszyka: ";
    std::cin >> choice;

    if (choice < 1 || choice > cart_map.size())
    {
        std::cout << "\nWprowadziles liczbe spoza zakresu! Wybierz jeszcze raz.\n";
        remove_product();
    }

    auto it = counter_name.find(choice);

    std::cout << "\nUsunales z koszyka: " << it->second << '\n';
    auto it_for_delete = cart_map.find(it->second);
    cart_map.erase(it_for_delete);
}

void Cart::save_cart() const
{
    std::string file_name;

    std::cout << "Podaj nazwe pliku do zapisu stanu koszyka: ";
    std::cin >> file_name;
    file_name += ".txt";

    std::ofstream cart_save_file(file_name.c_str());

    for (auto& elem : cart_map)
    {
        cart_save_file << (elem.first).get_name() << '\n';
        cart_save_file << (elem.first).get_netto() << '\n';
        cart_save_file << (elem.first).get_VAT() << '\n';
        cart_save_file << elem.second << '\n';
    }
}

void Cart::show_cart() const
{
    int amount = 0, counter = 1;

    std::cout << "\nZawartosc koszyka:\n";
    for (auto& elem : cart_map)
    {
        std::cout << counter++ << " - " << (elem.first).get_name() << " - " << elem.second << " szt.\n";
        amount += elem.second * ((elem.first).get_netto() * (100 + (elem.first).get_VAT()) / 100);
    }

    std::cout << "\nLaczna kwota produktow w koszyku wynosi: ";
    show_price(amount);
    std::cout << " PLN\n";

    char x = 'n';
    std::cout << "\nJesli chcesz zapisac stan koszyka do pliku tekstowego, wpisz \"t\" i zatwierdz: ";
    std::cin >> x;

    if (x == 't' || x == 'T')
        save_cart();
}

void Cart::recreate_cart_from_file(std::ifstream* new_stream)
{
    int line_no = 1;

    std::string load_data;

    while (getline(*new_stream, load_data))
    {
        static std::string temp_name = "NULL";
        static int temp_netto = 0;
        static int temp_VAT = 0;

        if (line_no == 1)
            temp_name = load_data;
        if (line_no == 2)
            temp_netto = atoi(load_data.c_str());
        if (line_no == 3)
            temp_VAT = atoi(load_data.c_str());
        if (line_no == 4)
        {
            Product temp_product(temp_name, temp_netto, temp_VAT);
            cart_map.emplace(temp_product, atoi(load_data.c_str()));
        }

        if (line_no == 4)
            line_no = 1;
        else line_no++;
    }
}

void Cart::load_cart()
{
    std::string file_name;

    std::cout << "\nPodaj nazwe pliku do odczytu stanu koszyka: ";
    std::cin >> file_name;
    file_name += ".txt";

    std::ifstream cart_load_file(file_name.c_str());

    if (cart_load_file.good() == false)
    {
        std::cout << "\nPlik zapisu o podanej nazwie nie istnieje.\n";
        return;
    }

    cart_map.clear();

    recreate_cart_from_file(&cart_load_file);
}