#ifndef EMPLOYEEREPOSITORY_H
#define EMPLOYEEREPOSITORY_H

#include <vector>
#include "Employee.h"
#include "Typedef.h"

class Shelf;
const unsigned int MAX_EMPLOYEES=2;

class EmployeeRepository
{
    std::vector<Employee> employees;
    std::vector<ShelfPtr> shelves;
    void add (Employee employee, int i);
    int remove(Employee employee);

public:
    friend void Employee::move(EmployeeRepository repository,int position);
    explicit EmployeeRepository(std::vector<Employee> employees);
    EmployeeRepository();
    ~EmployeeRepository()= default;
    std::string to_string();
    int get_employees_amount();
    Employee& get_employee(unsigned int index);
    std::vector<ShelfPtr> get_shelves();
    int amount_of_allocated_elements();
    bool can_take(int index);
    void exchange(Employee removed_employee,Employee new_employee);
    void put_down(ElementPtr element);
    ElementPtr pick_up(ElementPtr &element);
    void add_shelf(ShelfPtr shelf);
    void remove_shelf(ShelfPtr shelf);
};

#endif //EMPLOYEEREPOSITORY_H