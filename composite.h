//
// Created by Каринэ Матевосян on 03.12.2022.
//

#ifndef PATTERNS_COMPOSITE_H
#define PATTERNS_COMPOSITE_H

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
    virtual string GetName() const = 0;
    virtual int GetPrice() const = 0;
};

class Food : public Component {
    string food_name;
    int food_price;

public:
    Food(string name, int price);

    string GetName() const override;

    int GetPrice() const override;

    string Operation() const override;
};

class Category : public Component {

protected:
    list<Component *> children_;

public:
    string category_name;

    Category(string name);

    void Add(Component *component) override;

    void Remove(Component *component) override;

    string GetName() const override;

    int GetPrice() const override;

    bool IsCategory() const override;

    string Operation() const override;
};



#endif //PATTERNS_COMPOSITE_H
