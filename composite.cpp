#include <algorithm>
#include <iostream>
#include <list>
#include <string>

using namespace std;

class Component {
    protected:
        Component *parent_;
    public:
        virtual ~Component() {}
        void SetParent(Component *parent) {
            this->parent_ = parent;
        }
        Component *GetParent() const {
            return this->parent_;
        }

        virtual void Add(Component *component) {}
        virtual void Remove(Component *component) {}

        virtual bool IsCategory() const {
            return false;
        }

        virtual string Operation() const = 0;
};

class Food : public Component {
    string food_name;
    int food_price;

    public:
        Food(string name, int price) {
            food_name = name;
            food_price = price;
        }

        int GetPrice() {
            return food_price;
        }

        string Operation() const override {
            return "\n        '" + food_name + "'\n" + "        Цена: " + to_string(food_price) + "р \n";
        }
};

class Category : public Component {

    protected:
        list<Component *> children_;

    public:
        string category_name;

        Category(string name) {
            category_name = name;
        }

        void Add(Component *component) override {
            this->children_.push_back(component);
            component->SetParent(this);
        }

        void Remove(Component *component) override {
            children_.remove(component);
            component->SetParent(nullptr);
        }
        bool IsCategory() const override {
            return true;
        }

        string Operation() const override {
            string result;
            for (const Component *c : children_) {
                if (c == children_.back()) {
                    result += c->Operation();
                } else {
                    result += c->Operation();
                }
            }
            return "\n" + category_name + ":" + result ;
        }
};

void GetInfo(Component *component) {
    cout << component->Operation();
}

void ClientCode2(Component *component1, Component *component2) {
    if (component1->IsCategory()) {
        component1->Add(component2);
    }
    cout << component1->Operation();

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
    subcategory1->Add(food_4);
    subcategory2->Add(food_5);

    menu->Add(category1);
    menu->Add(category2);

    category3->Add(subcategory1);
    category3->Add(subcategory2);

    menu->Add(category3);

    cout << "===========================" << endl;
    cout << "Сформированное меню:\n";
    cout << "===========================" << endl;

    GetInfo(menu);


    delete simple;
    delete menu;
    delete category1;
    delete category2;
    delete category3;
    delete subcategory1;
    delete subcategory2;
    delete food_1;
    delete food_2;
    delete food_3;
    delete food_4;
    delete food_5;

    return 0;
}
