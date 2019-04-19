#include <sstream>
#include "Rent.h"
#include "Client.h"
#include "Element.h"

using namespace std;

Rent::Rent():rent_id(0),rent_date(0),return_date(0) {}

Rent::Rent(ClientPtr client, ElementPtr element, unsigned int rent_id, unsigned int rent_date, unsigned int return_date)
: client(move(client)), element(move(element)), rent_id(rent_id), rent_date(rent_date), return_date(return_date) {}

string Rent::to_string()
{
    ostringstream sout;
    sout<<client->get_first_name()<<" "<<client->get_last_name()<<" wypozyczyl(a) ,,"<<element->get_title_or_name()<<"'' (ID: "<<element->get_id()<<") "<<rent_date<<" dnia miesiaca";
    if (return_date==0)
        sout<<" i jeszcze go nie oddal(a)\n";
    else
        sout<<" i oddal(a) go "<<return_date<<" dnia miesiaca\n";
    return sout.str();
}

unsigned int Rent::get_id()
{
    return rent_id;
}

ClientPtr Rent::get_client()
{
    return client;
}

ElementPtr Rent::get_element()
{
    return element;
}

unsigned int Rent::get_rent_date()
{
    return rent_date;
}

unsigned int Rent::get_return_date()
{
    return return_date;
}

void Rent::set_return_day(unsigned int day)
{
    this->return_date=day;
}