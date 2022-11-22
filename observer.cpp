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

/**
* Издатель владеет некоторым важным состоянием и оповещает наблюдателей о его
* изменениях.
*/

class Creator : public ICreator {
public:
    virtual ~Creator() {
        cout << "Goodbye, I was the Creator." << endl;
    }

/**
* Методы управления подпиской.
*/
    void Attach(IClient *client) override {
        list_client_.push_back(client);
    }
    void Detach(IClient *client) override {
        list_client_.remove(client);
    }
    void Notify() override {
        std::list<IClient *>::iterator iterator = list_client_.begin();
        HowManyClient();
        while (iterator != list_client_.end()) {
            (*iterator)->Update(message_);
            ++iterator;
        }
    }

    void CreateMessage(string message = "Empty") {
        this->message_ = message;
        Notify();
    }
    void HowManyClient() {
        cout << "There are " << list_client_.size() << " clients in the list." << endl;;
    }

/**
* Обычно логика подписки – только часть того, что делает Издатель. Издатели
* часто содержат некоторую важную бизнес-логику, которая запускает метод
* уведомления всякий раз, когда должно произойти что-то важное (или после
* этого).
*/
    void SomeBusinessLogic() {
        this->message_ = "change message message";
        Notify();
        cout << "I'm about to do some thing important " << endl;
    }

private:
    std::list<IClient *> list_client_;
    std::string message_;
};

class Client : public IClient {
public:
    Client(Creator &creator) : creator_(creator) {
        this->creator_.Attach(this);
        cout << "Hi, I'm the Client " << ++Client::static_number_ << endl;
        this->number_ = Client::static_number_;
    }
    virtual ~Client() {
        cout << "Goodbye, I was the Client " << this->number_ << endl;
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
    
    Creator * = new Creator;
    Client *client1 = new Client(*creator);
    Client *client2 = new Client(*creator);
    Client *client3 = new Client(*creator);
    Client *client4;
    Client *client5;

    creator->CreateMessage("Hello World! :D");
    client3->RemoveMeFromTheList();

    creator->CreateMessage("The weather is hot today! :p");
    client4 = new Client(*creator);

    client2->RemoveMeFromTheList();
    client5 = new Client(*creator);

    creator->CreateMessage("My new car is great! ;)");
    client5->RemoveMeFromTheList();

    client4->RemoveMeFromTheList();
    client1->RemoveMeFromTheList();

    delete client5;
    delete client4;
    delete client3;
    delete client2;
    delete client1;
    delete creator;
}

int main() {
    ClientCode();
    return 0;
}
