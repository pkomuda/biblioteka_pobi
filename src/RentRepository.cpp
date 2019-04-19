#include <sstream>
#include <stdexcept>
#include "RentRepository.h"
#include "Rent.h"

using namespace std;

RentRepository::~RentRepository() {}

string RentRepository::to_string()
{
    ostringstream sout;
    for (const auto &i : rents)
        sout<<i->to_string();
    return sout.str();
}

unsigned int RentRepository::get_rent_amount()
{
    return (unsigned int)rents.size();
}

vector<RentPtr> RentRepository::get_rent_repository()
{
    return rents;
}

void RentRepository::add(RentPtr rent)
{
    rents.push_back(rent);
}

void RentRepository::remove(RentPtr rent)
{
    bool exists=false;
    unsigned int count=0;
    for (const auto &i : rents)
    {
        if (i==rent)
        {
            exists=true;
            break;
        }
        count++;
    }
    if (exists)
        rents.erase(rents.begin()+count);
    else
        throw out_of_range("Nie ma takiego wypozyczenia");
}

RentPtr RentRepository::at(int index)
{
    return rents.at(index);
}