#include "composite.h"
#include <iostream>

using namespace std;

void GetInfo(Component *component) {
    cout << component->Operation() << endl;
}

void Buy(Component *component1) {
    cout <<"Стоимость " << component1->GetName() << ": " << component1->GetPrice() << "р" << endl;
}

int main() {
    Component *simple = new Food("Гамбургер", 190);
    cout << "===========================" << endl;
    cout << "Создание простого блюда:\n";
    cout << "===========================" << endl;

    GetInfo(simple);

    Component *menu = new Category("Меню");

    Component *category1 = new Category("Салаты");
    Component *category2 = new Category("Бургеры");
    Component *category3 = new Category("Напитки");
    Component *category4 = new Category("Комбо №1");

    Component *subcategory1 = new Category("Холодные напитки");
    Component *subcategory2 = new Category("Горячие напитки");

    Component *food_1 = new Food("Цезарь", 220);
    Component *food_2 = new Food("Оливье", 240);
    Component *food_3 = new Food("Чизбургер", 230);
    Component *food_4 = new Food("Сок", 110);
    Component *food_5 = new Food("Латте", 220);

    category1->Add(food_1);
    category1->Add(food_2);
    category2->Add(food_3);
    category4->Add(food_3);
    category4->Add(food_1);
    category4->Add(food_4);

    subcategory1->Add(food_4);
    subcategory2->Add(food_5);

    menu->Add(category1);
    menu->Add(category2);

    category3->Add(subcategory1);
    category3->Add(subcategory2);

    menu->Add(category3);
    menu->Add(category4);

    cout << "===========================" << endl;
    cout << "Сформированное меню:\n";
    cout << "===========================" << endl;

    GetInfo(menu);

    cout << "===========================" << endl;
    cout << "Покупка комбо:\n";
    cout << "===========================" << endl;

    Buy(category4);

    delete simple;
    delete menu;
    delete category1;
    delete category2;
    delete category3;
    delete category4;
    delete subcategory1;
    delete subcategory2;
    delete food_1;
    delete food_2;
    delete food_3;
    delete food_4;
    delete food_5;

    return 0;
}
