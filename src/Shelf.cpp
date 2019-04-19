#include <sstream>
#include <stdexcept>
#include "Shelf.h"
#include "Book.h"
#include "Magazine.h"

using namespace std;

Shelf::Shelf(unsigned int number, unsigned int capacity):stand_number(number), capacity(capacity) {}

std::string Shelf::to_string()
{
    ostringstream sout;
    sout<<"Regal nr. "<<stand_number<<endl
    <<"pojemnosc: "<<capacity<<endl
    <<"zajete miejsce: "<<get_taken_space()<<endl
    <<"ilosc elementow: "<<elements.size()<<endl;

    sout<<endl<<endl;

    for(const auto &i:elements)
    {
        sout<<i->to_string();
    }
    return sout.str();
}

unsigned int Shelf::get_number()
{
    return stand_number;
}

unsigned int Shelf::get_capacity()
{
    return capacity;
}

unsigned int Shelf::get_element_amount()
{
    return (unsigned int)elements.size();
}

unsigned int Shelf::get_taken_space()
{
    unsigned int sum=0;
    for(const auto &i :elements)
    {
        sum+=i->get_size();
    }
    return sum;
}

ElementPtr Shelf::give(ElementPtr &element)
{
    ElementPtr temp;
    for(int i=0;i<elements.size();i++)
    {
        if(elements.at(i)->get_id()==element->get_id())
        {
            temp=element;
            elements.erase(elements.begin()+i);
            return temp;
        }
    }
    throw out_of_range("Na regale nie ma takiego elementu");
}

void Shelf::take(ElementPtr element)
{
    if (element->get_size()+get_taken_space()<=get_capacity())
        elements.push_back(element);
    else
        throw out_of_range("Na polce nie ma miejsca");
}

ElementPtr& Shelf::at(unsigned int index)
{
    return elements.at(index);
}