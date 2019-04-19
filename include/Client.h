#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include "Typedef.h"

class Rent;
class Address;

class Client : public std::enable_shared_from_this<Client>
{
    std::string client_id;
    std::string first_name;
    std::string last_name;
    unsigned int phone_number;
    Address *address;
    std::vector<RentPtr> rents;

public:
    explicit Client(std::string client_id="0");
    Client(std::string client_id, std::string first_name, std::string last_name, unsigned int phone, std::string street, std::string house_number, std::string city);
    ~Client();
    std::string to_string();
    std::string get_id();
    std::string get_first_name();
    std::string get_last_name();
    unsigned int get_phone();
    Address& get_address();
    unsigned int get_rent_amount();
    std::vector<RentPtr> get_rents();
    void set_phone(unsigned int number);
    void add_rent(RentPtr rent);
    bool remove_rent(RentPtr rent);
    std::string print_rents();
};

#endif //CLIENT_H