#ifndef SHELF_H
#define SHELF_H

#include <vector>
#include <string>
#include "Typedef.h"

class Element;

class Shelf
{
    std::vector<ElementPtr> elements;
    unsigned int stand_number;
    unsigned int capacity;

public:
    explicit Shelf(unsigned int number, unsigned int capacity=0);
    ~Shelf()= default;
    std::string to_string();
    unsigned int get_number();
    unsigned int get_capacity();
    unsigned int get_element_amount();
    unsigned int get_taken_space();
    ElementPtr give(ElementPtr &element);
    void take(ElementPtr element);
    ElementPtr& at(unsigned int index);
};

#endif //SHELF_H