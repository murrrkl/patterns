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

    Creator(string _order) {
            this->order = _order;
            cout << "Hi, I'm the Creator your order: ' " << _order << " ' " << endl;
    }

    /*
    virtual ~Creator() {
        cout << "Goodbye, I was the Creator." << endl;
    }
     */

/**
* Методы управления заказами.
*/
    void Attach(IClient *client) override {
        list_client_.push_back(client);
    }
    void Detach(IClient *client) override {
        list_client_.remove(client);
    }
    void Notify() override {
        std::list<IClient *>::iterator iterator = list_client_.begin();
        // HowManyClient();
        while (iterator != list_client_.end()) {
            (*iterator)->Update(message_);
            ++iterator;
        }
    }

    void CreateMessage() {
        this->message_ = "Your order: ' " + this->order + " ' is ready";
        Notify();
    }
    void HowManyClient() {
        cout << "There are " << list_client_.size() << " clients in the list." << endl;;
    }


    void SomeBusinessLogic() {
        this->message_ = "change message message";
        Notify();
        cout << "I'm about to do some thing important " << endl;
    }

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
    virtual ~Client() {
        cout << "Client " << this->number_ << " has received his order" << endl;
    }

    void Update(const std::string &message_from_creator) override {
        message_from_creator_ = message_from_creator;
        PrintInfo();
    }
    void RemoveMeFromTheList() {
        creator_.Detach(this);
        cout << "Client " << number_ << " removed from the list." << endl;
    }
    void PrintInfo() {
        cout << "Client " << this->number_ << ": a new message is available  " << this->message_from_creator_ << endl;
    }

private:
    string message_from_creator_;
    Creator &creator_;
    static int static_number_;
    int number_;
};

int Client::static_number_ = 0;

void ClientCode() {

    Creator *order1 = new Creator("Cheesburger, olivier salad, coffee");
    Client *client1 = new Client(*order1);

    cout << "*******************************************" << endl;

    Creator *order2 = new Creator("Vegan burger, Vegetables salad, ice-tea");
    Client *client2 = new Client(*order2);

    cout << "--------------------------------" << endl;

    order1->CreateMessage();
    delete client1;
    delete order1;

    cout << "--------------------------------" << endl;
    order2->CreateMessage();
    delete client2;
    delete order2;
}

int main() {
    ClientCode();
    return 0;
}
