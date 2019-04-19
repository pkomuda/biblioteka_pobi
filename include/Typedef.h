#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <memory>

class Element;
class Client;
class Rent;
class Shelf;

typedef std::shared_ptr<Element> ElementPtr;
typedef std::shared_ptr<Client> ClientPtr;
typedef std::shared_ptr<Rent> RentPtr;
typedef std::shared_ptr<Shelf> ShelfPtr;

#endif //TYPEDEF_H