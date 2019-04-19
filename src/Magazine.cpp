#include <sstream>
#include <stdexcept>
#include "Magazine.h"

using namespace std;

unsigned int Magazine::counter=0;

Magazine::Magazine(unsigned int id,unsigned int size):Element(id,size)
{
    this->name="Nazwa";
    this->issue_number=0;
}

Magazine::Magazine(unsigned int id, unsigned int size, string publisher, string name, unsigned int number)
: Element(id,size,move(publisher)), name(move(name)), issue_number(number)
{
    counter++;
}

string Magazine::to_string()
{
    ostringstream sout;
    sout<<"Czasopismo ,,"<<name<<"'' (ID: "<<Element::get_id()<<", wydanie "<<issue_number<<") wydane przez "<<Element::get_publisher()<<" ma rozmiar "<<Element::get_size()<<endl;
    return sout.str();
}

string Magazine::get_title_or_name()
{
    return name;
}

string Magazine::get_author()
{
    throw out_of_range("Nie ma takiego atrybutu!");
}

unsigned int Magazine::get_number()
{
    return issue_number;
}

unsigned int Magazine::get_year()
{
    throw out_of_range("Nie ma takiego atrybutu!");
}

std::string Magazine::get_genre()
{
    throw out_of_range("Nie ma takiego atrybutu!");
}

unsigned int Magazine::get_counter()
{
    return counter;
}

void Magazine::set_year(unsigned int year)
{
    throw out_of_range("Nie ma takiego atrybutu!");
}

void Magazine::set_genre(std::string genre)
{
    throw out_of_range("Nie ma takiego atrybutu!");
}