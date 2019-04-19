#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "Element.h"

class Magazine: public Element
{
    std::string name;
    unsigned int issue_number;
    static unsigned int counter;

public:
    explicit Magazine(unsigned int id=0,unsigned int size=0);
    Magazine(unsigned int id, unsigned int size, std::string publisher, std::string name, unsigned int number);
    ~Magazine() override {counter--;}
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

#endif //MAGAZINE_H