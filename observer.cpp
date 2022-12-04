//
// Created by Каринэ Матевосян on 04.12.2022.
//

#include "observer.h"

using namespace std;

Creator::Creator(string _order)  {
    this->order = _order;
    cout << "Hi, I'm the Creator of " << _order <<  endl;
}

void Creator::Attach(IClient *client) {
    list_client_.push_back(client);
}

void Creator::Detach(IClient *client)  {
    list_client_.remove(client);
}

void Creator::Notify()  {
    std::list<IClient *>::iterator iterator = list_client_.begin();
    // HowManyClient();
    while (iterator != list_client_.end()) {
        (*iterator)->Update(message_);
        ++iterator;
    }
}

void Creator::CreateMessage()  {
    this->message_ = "Your order: ' " + this->order + " ' is ready";
    Notify();
}

void Creator::HowManyClient()  {
    cout << "There are " << list_client_.size() << " clients in the list." << endl;;
}

Client::~Client() noexcept  {
    cout << "Client " << this->number_ << " has received his order" << endl;
}

void Client::Update(const std::string &message_from_creator)  {
    message_from_creator_ = message_from_creator;
    PrintInfo();
}

void Client::RemoveMeFromTheList()  {
    creator_.Detach(this);
    cout << "Client " << number_ << " removed from the list." << endl;
}

void Client::PrintInfo()  {
    cout << "Client " << this->number_ << ": a new message is available  " << this->message_from_creator_ << endl;
}

int Client::static_number_ = 0;
