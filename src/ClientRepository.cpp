#include <sstream>
#include <stdexcept>
#include "ClientRepository.h"
#include "Client.h"

using namespace std;

string ClientRepository::to_string()
{

    ostringstream sout;
    sout<<"W repozytorium jest "<<get_clients_amount()<<" klientow:\n\n";
    for (const auto &i : clients)
        sout<<i->to_string()<<endl;
    return sout.str();
}

unsigned int ClientRepository::get_clients_amount()
{
    return (unsigned int)clients.size();
}

vector<ClientPtr> ClientRepository::get_clients()
{
    return clients;
}

void ClientRepository::add(ClientPtr client)
{
    clients.push_back(client);
}

bool ClientRepository::remove(ClientPtr client)
{
    bool exists=false;
    unsigned int count=0;
    for (const auto &i : clients)
    {
        if (i==client)
        {
            exists=true;
            break;
        }
        count++;
    }
    if (exists)
    {
        clients.erase(clients.begin()+count);
        return true;
    }
    else
        throw out_of_range("Nie ma takiego klienta");
}