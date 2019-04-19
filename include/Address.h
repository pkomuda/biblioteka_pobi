#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

class Address
{
    std::string street;
    std::string house_number;
    std::string city;

public:
    Address(std::string street, std::string house_number, std::string city);
    ~Address()= default;
    std::string get_street();
    std::string get_house();
    std::string get_city();
};

#endif //ADDRESS_H