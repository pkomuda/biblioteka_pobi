#include "Book.h"
#include <sstream>
#include <stdexcept>

using namespace std;

unsigned int Book::counter=0;

Book::Book(unsigned int id,unsigned int size):Element(id,size)
{
    this->title="Tytul";
    this->author="Autor";
    this->genre="Gatunek";
    this->publishment_year=0;
}

Book::Book(unsigned int id, unsigned int size, string publisher, string title, string author, string genre, unsigned int year)
: Element(id,size,move(publisher)), title(move(title)), author(move(author)), genre(move(genre)), publishment_year(year)
{
    counter++;
}

string Book::to_string()
{
    ostringstream sout;
    sout<<"Ksiazka ,,"<<title<<"'' (ID: "<<Element::get_id()<<") autorstwa "<<author<<" wydana przez "<<Element::get_publisher()
        <<" w "<<publishment_year<<" roku jest z gatunku "<<genre<<" i ma rozmiar "<<Element::get_size()<<endl;
    return sout.str();
}

string Book::get_title_or_name()
{
    return title;
}

string Book::get_author()
{
    return author;
}

unsigned int Book::get_number()
{
    throw out_of_range("Nie ma takiego atrybutu!");
}

unsigned int Book:: get_year()
{
    return publishment_year;
}

string Book::get_genre()
{
    return genre;
}

unsigned int Book::get_counter()
{
    return counter;
}
void Book::set_year(unsigned int year)
{
    this->publishment_year=year;
}

void Book::set_genre(string genre)
{
    this->genre=genre;
}