#include <iostream>
#include <stdexcept>
#include "Client.h"
#include "Address.h"
#include "Rent.h"
#include "ClientRepository.h"
#include "Element.h"
#include "Book.h"
#include "Magazine.h"
#include "RentManager.h"

using namespace std;

void printClient(ClientPtr c)
{
    cout << c->to_string() << endl;
}

class CLIObserver: public Observer
{
public:
    void observe(RentManager *r)
    {
        for (int i = 0; i < r->get_clients_amount(); i++)
        {
            ClientPtr c = r->get_clients_repository().get_clients().at(i);
            printClient (c);
        }
        cout << endl;
    }
};

int main()
{
    auto *r=new RentManager;
    CLIObserver observer;
    r->simulate(10, &observer);
    delete r;
    return 0;
}
