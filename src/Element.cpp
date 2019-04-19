#include "Element.h"

using namespace std;

Element::Element(unsigned id,unsigned int size) : id(id), size(size), publisher("Wydawnictwo") {}

Element::Element(unsigned int id, unsigned int size, string publisher) : id(id), size(size), publisher(move(publisher)) {}

unsigned int Element::get_size()
{
    return size;
}

unsigned int Element::get_id()
{
    return id;
}

string Element::get_publisher()
{
    return publisher;
}

void Element::set_publisher(std::string publisher)
{
    this->publisher=move(publisher);
}