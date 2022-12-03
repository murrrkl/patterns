//
// Created by Каринэ Матевосян on 03.12.2022.
//

#include "composite.h"

Food::Food(string name, int price) {
    food_name = name;
    food_price = price;
}

int Food::GetPrice() const {
    return food_price;
}

string Food::GetName() const {
    return food_name;
}

string Food::Operation() const {
    return "\n        '" + food_name + "'\n" + "        Цена: " + to_string(food_price) + "р \n";
}


Category::Category(string name) {
        category_name = name;
}

void Category::Add(Component *component) {
        this->children_.push_back(component);
        component->SetParent(this);
}

void Category::Remove(Component *component) {
        children_.remove(component);
        component->SetParent(nullptr);
}

bool Category::IsCategory() const {
        return true;
}

string Category::Operation() const {
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

string Category::GetName() const {
    return category_name;
}

int Category::GetPrice() const {
    int result;
    for (const Component *c : children_) {
        if (c == children_.back()) {
            result += c->GetPrice();
        } else {
            result += c->GetPrice();
        }
    }
    return result;
}

