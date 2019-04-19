#ifndef CLIENTREPOSITORY_H
#define CLIENTREPOSITORY_H

#include <vector>
#include <string>
#include "Typedef.h"

class Client;

class ClientRepository
{
    std::vector<ClientPtr> clients;

public:
    ClientRepository() = default;
    ~ClientRepository() = default;
    std::string to_string();
    unsigned int get_clients_amount();
    std::vector<ClientPtr> get_clients();
    void add(ClientPtr client);
    bool remove(ClientPtr client);
};

#endif //CLIENTREPOSITORY_H