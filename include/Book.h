#ifndef BOOK_H
#define BOOK_H

#include "Element.h"

class Book: public Element
{
    std::string title;
    std::string author;
    std::string genre;
    unsigned int publishment_year;
    static unsigned int counter;

public:
    explicit Book(unsigned int id=0,unsigned int size=0);
    Book(unsigned int id, unsigned int size, std::string publisher, std::string title, std::string author, std::string genre, unsigned int year);
    ~Book() override {counter--;}
    std::string to_string() override;
    std::string get_title_or_name() override;
    std::string get_author() override;
    unsigned int get_number() override;
    unsigned int get_year() override;
    std::string get_genre() override;
    static unsigned int get_counter();
    void set_year(unsigned int year) override;
    void set_genre(std::string genre) override;
};

#endif //BOOK_H