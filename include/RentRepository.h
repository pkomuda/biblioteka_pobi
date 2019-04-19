#ifndef RENTREPOSITORY_H
#define RENTREPOSITORY_H

#include <vector>
#include <string>
#include "Typedef.h"

class Rent;

class RentRepository
{
    std::vector<RentPtr> rents;

public:
    RentRepository()= default;
    ~RentRepository();
    std::string to_string();
    unsigned int get_rent_amount();
    std::vector<RentPtr> get_rent_repository();
    void add(RentPtr rent);
    void remove(RentPtr rent);
    RentPtr at(int index);
};

#endif //RENTREPOSITORY_H
