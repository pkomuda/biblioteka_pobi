#ifndef RENTMANAGER_H
#define RENTMANAGER_H

#include "EmployeeRepository.h"
#include "RentRepository.h"
#include "ClientRepository.h"

class Client;
class RentManager;

class Observer
{
public:
    virtual void observe(RentManager *rent_manager) = 0;
    virtual ~Observer()= default;
};

class RentManager
{
    RentRepository current_rents;
    RentRepository past_rents;
    ClientRepository client_repository;
    EmployeeRepository employee_repository;
    unsigned int hour;
    unsigned int day;
    void change_hour();
    void change_day();

public:
    RentManager();
    ~RentManager();
    std::string to_string();
    int get_clients_amount();
    ClientRepository& get_clients_repository();
    EmployeeRepository& get_employees_repository();
    RentRepository& get_current_rents();
    RentRepository& get_past_rents();
    RentPtr make_rent(ClientPtr &client, ElementPtr &element,  unsigned int rent_date, unsigned int return_date);
    void borrow(ClientPtr &client, ElementPtr &element,  unsigned int rent_date, unsigned int return_date=0);
    void take_back(RentPtr rent);
    void move_to_past(RentPtr rent);
    unsigned int is_hour();
    unsigned int is_day();

    void simulate(int steps,Observer *observer);
};

#endif //RENTMANAGER_H
