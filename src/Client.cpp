#include <sstream>
#include <stdexcept>
#include "Client.h"
#include "Address.h"
#include "Rent.h"

using namespace std;

Client::Client(string client_id) : client_id(move(client_id))
{
    this->first_name="Imie";
    this->last_name="Nazwisko";
    this->phone_number=0;
    this->address = new Address("Ulica","nr","Miasto");
}

Client::Client(string client_id, string first_name, string last_name, unsigned int phone, string street, string house_number, string city)
: client_id(move(client_id)), first_name(move(first_name)), last_name(move(last_name)), phone_number(phone)
{
    this->address = new Address(move(street),move(house_number),move(city));
}

Client::~Client()
{
    delete address;
}

string Client::to_string()
{
    ostringstream sout;
    sout<<"ID klienta: "<<client_id;
    sout<<"\nImię: "<<first_name;
    sout<<"\nNazwisko: "<<last_name;
    sout<<"\nNumer telefonu: "<<phone_number;
    sout<<"\nAdres: "<<address->get_street()<<" "<<address->get_house()<<", "<<address->get_city()<<endl;
    return sout.str();
}

string Client::get_id()
{
    return client_id;
}

string Client::get_first_name()
{
    return first_name;
}

string Client::get_last_name()
{
    return last_name;
}

unsigned int Client::get_phone()
{
    return phone_number;
}

Address& Client::get_address()
{
    return *address;
}

unsigned int Client::get_rent_amount()
{
    return (unsigned int)rents.size();
}

vector<shared_ptr<Rent>> Client::get_rents()
{
    return rents;
}

void Client::set_phone(unsigned int number)
{
    this->phone_number=number;
}

void Client::add_rent(RentPtr rent)
{
    if (rent->get_client()==shared_from_this())
    {
        if (rent->get_return_date()==0)
            rents.push_back(rent);
        else
            throw out_of_range("Nie mozna dodac przeszlego wypozyczenia do aktualnych");
    }
    else
        throw out_of_range("Zly klient");
}

bool Client::remove_rent(RentPtr rent)
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
    {
        rents.erase(rents.begin()+count);
        return true;
    }
    else
        throw out_of_range("Nie ma takiego wypozyczenia");
}

string Client::print_rents()
{
    ostringstream sout;
    for (const auto &i : rents)
        sout<<i->to_string();
    return sout.str();
}