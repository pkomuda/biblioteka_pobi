#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

class Element
{
protected:
    unsigned int id;
    unsigned int size;
    std::string publisher;

public:
    Element(unsigned int id,unsigned int size);
    Element(unsigned int id, unsigned int size, std::string publisher);
    virtual ~Element()= default;
    virtual std::string to_string()=0;
    virtual std::string get_title_or_name()=0;
    virtual std::string get_author()=0;
    virtual unsigned int get_year()=0;
    virtual std::string get_genre()=0;
    virtual unsigned int get_number()=0;
    unsigned int get_size();
    unsigned int get_id();
    std::string get_publisher();
    virtual void set_year(unsigned int year)=0;
    virtual void set_genre(std::string genre)=0;
    void set_publisher(std::string publisher);
};

#endif //ELEMENT_H