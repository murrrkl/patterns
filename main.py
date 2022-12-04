#include <iostream>
#include "observer.h"

using namespace std;

void ClientCode() {

    Creator *burger_creator = new Creator("Burger");
    Creator *salad_creator = new Creator("Salad");
    Creator *cake_creator = new Creator("Cake");
    Creator *coffee_creator = new Creator("Coffee");
    cout << "*******************************************" << endl;

    Client *client1 = new Client(*burger_creator);
    salad_creator->Attach(client1);
    coffee_creator->Attach(client1);

    cout << "*******************************************" << endl;

    Client *client2 = new Client(*coffee_creator);
    cake_creator->Attach(client2);

    cout << "*******************************************" << endl;

    coffee_creator->CreateMessage();
    cake_creator->CreateMessage();
    salad_creator->CreateMessage();
    burger_creator->CreateMessage();

    cout << "*******************************************" << endl;

    delete client1;
    delete client2;

    delete coffee_creator;
    delete burger_creator;
    delete cake_creator;
    delete salad_creator;
}

int main() {
    ClientCode();
    return 0;
}


