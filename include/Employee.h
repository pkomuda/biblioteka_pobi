#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include "Typedef.h"

class Element;
class Rent;
class EmployeeRepository;

class Employee
{
    ElementPtr element;
    RentPtr rent;
    std::string employee_id;
    int position;

public:
    Employee();
    explicit Employee(std::string employee_id);
    ~Employee()= default;
    std::string get_id();
    int get_position();
    ElementPtr& get_element();
    ElementPtr give_element();
    void take_element(ElementPtr element);
    void move(EmployeeRepository repository,int position);
};

#endif //EMPLOYEE_H