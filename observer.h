//
// Created by Каринэ Матевосян on 04.12.2022.
//

#ifndef OBSERVER_OBSERVER_H
#define OBSERVER_OBSERVER_H

#include <iostream>
#include <list>
#include <string>

using namespace std;

class IClient {
public:
    virtual ~IClient(){};
    virtual void Update(const std::string &message_from_creator) = 0;
};

class ICreator {
public:
    virtual ~ICreator(){};
    virtual void Attach(IClient *client) = 0;
    virtual void Detach(IClient *client) = 0;
    virtual void Notify() = 0;
};


class Creator : public ICreator {
public:

    Creator(string _order);


    //virtual ~Creator();

    /**
    * Методы управления заказами.
    */
    void Attach(IClient *client) override;

    void Detach(IClient *client) override;

    void Notify() override;

    void CreateMessage();

    void HowManyClient();

private:
    std::list<IClient *> list_client_;
    string message_;
    string order;
};

class Client : public IClient {
public:
    Client(Creator &creator) : creator_(creator) {
        this->creator_.Attach(this);
        cout << "Hi, I'm the Client " << ++Client::static_number_ << " and i am waiting for my order" << endl;
        this->number_ = Client::static_number_;
    }

    virtual ~Client();

    void Update(const std::string &message_from_creator) override;

    void RemoveMeFromTheList();

    void PrintInfo();

private:

    Creator &creator_;
    string message_from_creator_;
    static int static_number_;
    int number_;
};

#endif //OBSERVER_OBSERVER_H
