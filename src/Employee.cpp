#include <stdexcept>
#include "Employee.h"
#include "EmployeeRepository.h"
#include "Book.h"

using namespace std;

Employee::Employee():employee_id("E0") {}

Employee::Employee(std::string employee_id):employee_id(std::move(employee_id)),position(-1)
{
    ElementPtr temp(new Book);
    this->element=temp;
}

string Employee::get_id()
{
    return employee_id;
}

int Employee::get_position()
{
    return position;
}

ElementPtr& Employee::get_element()
{
    return element;
}

ElementPtr Employee::give_element()
{
    ElementPtr temp1(new Book);
    ElementPtr temp2(new Book);
    temp1=this->element;
    this->element=temp2;
    return temp1;
}

void Employee::take_element(ElementPtr element)
{
    if(this->element->get_id()==0)
        this->element=std::move(element);
    else
        throw out_of_range("Nie ma takiego elementu");
}

void Employee::move(EmployeeRepository repository,int position)
{
    if( position>=-1 && position<(int)repository.shelves.size() )
        this->position=position;
    else
        throw out_of_range("Nie ma takiej pozycji");
}