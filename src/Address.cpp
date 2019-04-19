#include "Address.h"

using namespace std;

Address::Address(string street, string house_number, string city)
: street(std::move(street)), house_number(std::move(house_number)), city(std::move(city))
{}

string Address::get_street()
{
    return street;
}

string Address::get_house()
{
    return house_number;
}

string Address::get_city()
{
    return city;
}