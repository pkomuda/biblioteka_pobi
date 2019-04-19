#include <sstream>
#include <stdexcept>
#include "EmployeeRepository.h"
#include "Employee.h"
#include "Element.h"
#include "Shelf.h"

using namespace std;

EmployeeRepository::EmployeeRepository(std::vector<Employee> employees)
{
    if(employees.size()==MAX_EMPLOYEES)
    {
        for(auto &i : employees)
        {
            this->employees.push_back(i);
        }
    }
    else if(employees.size()>MAX_EMPLOYEES)
        throw out_of_range("Niestety nie wyszyscy mogą zostać zatrudnieni");
    else if(employees.size()<MAX_EMPLOYEES)
        throw out_of_range("Potrzeba wiecej pracownikow na start");
}

EmployeeRepository::EmployeeRepository()
{
    for (int i=0; i<MAX_EMPLOYEES; i++)
    {
        Employee e;
        employees.push_back(e);
    }
}

string EmployeeRepository::to_string()
{
    ostringstream sout;
    for(auto &i : employees)
    {
        if(i.get_id()!="E0")
        sout<<"Pracownik o id "<<i.get_id()<<" znajduje sie na pozycji "<<i.get_position()<<endl;
    }
    return sout.str();
}

int EmployeeRepository::get_employees_amount()
{
    int amount=0;
    for(auto &i : employees)
    {
        if(i.get_id()!="E0")
        {
            amount++;
        }
    }
    return amount;
}

Employee& EmployeeRepository::get_employee(unsigned int index)
{
    if(index<MAX_EMPLOYEES)
        return employees[index];
    else throw out_of_range("Nie ma takiego pracownika");
}

vector<ShelfPtr> EmployeeRepository::get_shelves()
{
    return shelves;
}

int EmployeeRepository::amount_of_allocated_elements()
{
    int sum=0;
    for(const auto &i : shelves)
    {
        for(int j=0; j<i->get_element_amount(); j++)
            sum++;
    }
    return sum;
}

bool EmployeeRepository::can_take(int index)
{
    return(employees[index].get_element()->get_id()==0);
}

void EmployeeRepository::exchange(Employee removed_employee,Employee new_employee)
{
    int i=remove(removed_employee);
    add(new_employee,i);
}

void EmployeeRepository::put_down(ElementPtr element)
{
    int cashier=0;
    for(auto &a : employees)
    {
        if(a.get_position()==-1)
            cashier++;
    }

    if(get_employees_amount()==2)
    {
        int i;
        for(i=0;i<MAX_EMPLOYEES;i++)
        {
            if (cashier == 0)
                employees[i].move(*this, -1);

            if (employees[i].get_position() == -1)
                break;
        }

        employees[i].take_element(element);

        int j;
        for (j = 0; j < MAX_EMPLOYEES; j++)
        {
            if (j != i && can_take(j))
                break;
        }

        employees[j].move(*this,-1);
        employees[j].take_element(employees[i].give_element());

        int k;
        for (k = 0; k < shelves.size(); ++k)
        {
            employees[j].move(*this,k);
            if (shelves.at(k)->get_taken_space() + element->get_size() <= shelves.at(k)->get_capacity())
            {
                shelves.at(k)->take(employees[j].give_element());
                break;
            }
        }

        if(k==shelves.size())
        {
            throw out_of_range("Nie ma miejsca");
        }
    }
    else throw out_of_range("Nie ma tylu pracownikow");
}

ElementPtr EmployeeRepository::pick_up(ElementPtr &element)
{
    if(get_employees_amount()==2)
    {
        int worker=0;
        for(auto &a : employees)
        {
            if(a.get_position()>=0)
                worker++;
        }

        int k;
        for( k=0;k<MAX_EMPLOYEES;k++)
        {
            if (worker == 0)
                employees[k].move(*this, 0);

            if (employees[k].get_position() >= 0 && can_take(k))
                break;
        }

        for(int a=0;a<shelves.size()&&can_take(k);a++)
        {
            employees[k].move(*this,a);
            for(int i=0;i<shelves.at(employees[k].get_position())->get_element_amount();i++)
            {
                if(element==shelves.at(employees[k].get_position())->at(i))
                {
                    employees[k].take_element(shelves.at(employees[k].get_position())->give(element));
                    break;
                }
                else if (a==shelves.size()-1 && i==shelves.at(employees[k].get_position())->get_element_amount())
                    throw out_of_range("Tej ksiazki nie znaleziono");
            }
        }

        int i;
        for (i = 0; i < MAX_EMPLOYEES; i++)
        {
            if (k != i && can_take(i))
                break;
        }
        employees[k].move(*this,-1);
        employees[i].take_element(employees[k].give_element());
        return employees[i].give_element();

    }
    else throw out_of_range("Nie ma pracownikow");
}

void EmployeeRepository::add_shelf(ShelfPtr shelf)
{
    this->shelves.push_back(shelf);
}

void EmployeeRepository::remove_shelf(ShelfPtr shelf)
{
    for(int i=0;i<shelves.size();i++)
    {
        if(shelf==shelves.at(i))
        {
            this->shelves.erase(shelves.begin()+i);
            break;
        }
        else if(i==shelves.size()-1)
            throw out_of_range("Takiego regalu nie ma w bibliotece");
    }
}

void EmployeeRepository::add(Employee employee, int i)
{
    if(MAX_EMPLOYEES>employees.size())
    {
        employees.insert(employees.begin()+i,employee);
    }
    else throw out_of_range("Nie ma miejsca na kolejnego pracownika");
}

int EmployeeRepository::remove(Employee employee)
{
    int i;
    for(i=0;i<MAX_EMPLOYEES; i++)
    {
        if(employees[i].get_id()==employee.get_id())
        {
            employees.erase(employees.begin()+i);
            break;
        }
        else if(i==MAX_EMPLOYEES-1)
            throw out_of_range("Nie ma takiego pracownika");
    }
    return i;
}