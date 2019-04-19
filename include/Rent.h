#ifndef RENT_H
#define RENT_H

#include <string>
#include "Typedef.h"

class Client;
class Element;

class Rent
{
    unsigned int rent_id;
    ClientPtr client;
    ElementPtr element;
    unsigned int rent_date;
    unsigned int return_date;

public:
    Rent();
    Rent(ClientPtr client, ElementPtr element, unsigned int rent_id, unsigned int rent_date, unsigned int return_date=0);
    ~Rent()= default;
    std::string to_string();
    unsigned int get_id();
    ClientPtr get_client();
    ElementPtr get_element();
    unsigned int get_rent_date();
    unsigned int get_return_date();
    void set_return_day(unsigned int day);
};

#endif //RENT_H