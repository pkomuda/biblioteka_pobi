#include <iostream>
#include <sstream>
#include <stdexcept>
#include <random>
#include <functional>
#include <chrono>
#include "RentManager.h"
#include "Rent.h"
#include "Magazine.h"
#include "Book.h"
#include "Client.h"
#include "Shelf.h"

using namespace std;

RentManager::RentManager():day(1),hour(8)
{
    ClientRepository clients;
    RentRepository current;
    RentRepository past;
    this->current_rents=current;
    this->past_rents=past;
    this->client_repository=clients;
}

RentManager::~RentManager() {}

string RentManager::to_string()
{
    ostringstream sout;
    sout<<"W bibliotece znajduje sie obecnie "<<Book::get_counter()+Magazine::get_counter()
    <<" elementow. W tym "<<Book::get_counter()<<" ksiazek i "<<Magazine::get_counter()<< " magazynow.\n"
    <<employee_repository.amount_of_allocated_elements()<<" z nich znajduje sie na polkach";
    return sout.str();
}

int RentManager::get_clients_amount()
{
    return client_repository.get_clients_amount();
}

ClientRepository& RentManager::get_clients_repository()
{
    return client_repository;
}

EmployeeRepository& RentManager::get_employees_repository()
{
    return employee_repository;
}

RentRepository& RentManager::get_current_rents()
{
    return current_rents;
}

RentRepository& RentManager::get_past_rents()
{
    return past_rents;
}

RentPtr RentManager::make_rent(ClientPtr &client, ElementPtr &element,  unsigned int rent_date, unsigned int return_date)
{
    unsigned int rent_id;
    unsigned int i=current_rents.get_rent_amount()+past_rents.get_rent_amount()+1;
    rent_id=i;

    RentPtr r(new Rent(client,element,rent_id,rent_date,return_date));
    client->add_rent(r);
    return r;
}

void RentManager::borrow(ClientPtr &client, ElementPtr &element,  unsigned int rent_date, unsigned int return_date)
{
    ElementPtr e=employee_repository.pick_up(element);
    current_rents.add(make_rent(client,e,rent_date,return_date));
}

void RentManager:: take_back(RentPtr rent)
{
    move_to_past(rent);
    employee_repository.put_down(rent->get_element());
}

void RentManager::move_to_past(RentPtr rent)
{
    change_day();
    for(int i=0;i<current_rents.get_rent_amount();i++)
    {
        if(current_rents.at(i)==rent)
        {
            current_rents.remove(rent);
            past_rents.add(rent);
            for(int j=0;j<get_clients_amount();j++)
            {
                if(rent->get_client()==client_repository.get_clients().at(j))
                {
                    client_repository.get_clients().at(j)->remove_rent(rent);
                    past_rents.at(past_rents.get_rent_amount()-1)->set_return_day(day);
                    break;
                }
                else if (i==get_clients_amount()-1)
                {
                    throw out_of_range("Takiego klienta nie ma w systemie");
                }
            }
            break;
        }
        else if (i==current_rents.get_rent_amount()-1)
            throw out_of_range("Takiego wypozyczenia nie ma w systemie");
    }
}

void RentManager::change_hour()
{
    auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    auto rand = bind(uniform_int_distribution<unsigned int>(8,20),mt19937((unsigned int)seed));
    unsigned int hour = rand();
    this->hour=hour;
}

void RentManager::change_day()
{
    auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    auto rand = bind(uniform_int_distribution<unsigned int>(1,30),mt19937((unsigned int)seed));
    unsigned int day = rand();
    this->day=day;
}

unsigned int RentManager::is_hour()
{
    return hour;
}

unsigned int RentManager::is_day()
{
    return day;
}

void RentManager::simulate(int steps, Observer *observer)
{
    //rekrutujemy pracownikow//
    vector<Employee> employees;

    for(int i=0;i<MAX_EMPLOYEES;i++)
    {
        ostringstream eout;
        eout << "Pracownik " << (i + 1);
        employees.emplace_back(Employee(eout.str()));
    }
    //zatrudniamy pracownikow//
    EmployeeRepository employeeRepo(employees);
    this->employee_repository=employeeRepo;
    cout<<"\nIlosc zatrudnionych pracownikow: "<<employee_repository.get_employees_amount()<<endl;
    cout<<employee_repository.to_string();

    //Tworzymy regal//
    cout<<"\nTworzymy regał\n";
    ShelfPtr s1(new Shelf(1));
    cout<<"Tworzymy regał\n";
    ShelfPtr s2(new Shelf(2,20));

    employee_repository.add_shelf(s1);
    employee_repository.add_shelf(s2);
    cout<<"Ilosc regalow: "<< employee_repository.get_shelves().size()<<endl<<endl;

    //tworzymy ksiazki i czasopisma oraz odkladamy je na regal//
    vector<ElementPtr> elements;//by mozna bylo je wypozyczyc
    cout<<"\nTworzymy "<<steps<<" elementow i kladziemy je na polkach\n\n";
    for (int i = 0; i < steps*2; ++i)
    {
        if (i < steps)
        {
            ElementPtr b(new Book((unsigned int)i,0));
            elements.push_back(b);
            employee_repository.put_down(b);
            cout<<employee_repository.to_string();
            cout<<"i kladzie ksiazke na polce.\n";
        }
        else {
            ElementPtr m(new Magazine((unsigned int)i+2*steps,1));
            elements.push_back(m);
            employee_repository.put_down(m);
            cout<<employee_repository.to_string();
            cout<<"i kladzie magazyn na polce.\n";
        }
    }
    cout<<"\n\n";
    for(const auto &i: employee_repository.get_shelves())
    {
        cout<<endl<<i->to_string()<<endl<<endl;
    }

    //wpisujemy klientow do repozytorium//
    cout<<"\nWpisujemy klientow do repozytorum\n";
    int j;
    for (j = 0; j < steps; j++)
    {
        ostringstream sout;
        sout << "Klient " << (j + 1);
        ClientPtr c(new Client(sout.str()));
        client_repository.add(c);
    }
    cout<<client_repository.to_string()<<endl;
    cout<<"Ilosc klientow w repozytorium: "<<client_repository.get_clients_amount();


    cout<<"\n\n\nRozpoczynamy symulacje wypozyczen\n\n";
    for (j=0;j < client_repository.get_clients().size(); j++)
    {
        change_day();change_hour();
        borrow((client_repository.get_clients().at(j)),elements[j],day);
        if(hour<=10 || hour>=18)
        {
            cout<<endl<<client_repository.get_clients().at(j)->get_id()<<" posiada "<<client_repository.get_clients().at(j)->get_rent_amount()<<" wypozyczen:\n";
            cout<<client_repository.get_clients().at(j)->print_rents();
            cout<<"-------------------------------\n";
            cout<<"Teraz jest czas na wypozyczenia\n";
            cout<<"-------------------------------\n";
            change_day();change_hour();
            borrow((client_repository.get_clients().at(j)),elements[j],day);
            cout<<client_repository.get_clients().at(j)->get_id()<<" posiada "<<client_repository.get_clients().at(j)->get_rent_amount()<<" wypozyczen:\n";
            cout<<client_repository.get_clients().at(j)->print_rents()<<"\n\n";
        }
        else
        {
            if ((client_repository.get_clients().at(j))->get_rent_amount() != 0)
            {
                cout<<endl<<client_repository.get_clients().at(j)->get_id()<<" posiada "<<client_repository.get_clients().at(j)->get_rent_amount()<<" wypozyczen:\n";
                cout<<client_repository.get_clients().at(j)->print_rents();
                cout<<"------------------------\n";
                cout<<"Teraz jest czas na zwrot\n";
                cout<<"------------------------\n";
                auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
                auto rand = bind(uniform_int_distribution<unsigned int>(0,client_repository.get_clients().at(j)->get_rent_amount()-1),mt19937((unsigned int)seed));
                int one_of_rents = rand();

                take_back(client_repository.get_clients().at(j)->get_rents().at(one_of_rents));
                cout<<client_repository.get_clients().at(j)->get_id()<<" posiada "<<client_repository.get_clients().at(j)->get_rent_amount()<<" wypozyczen\n\n\n";
            }
            else
            {
                cout<<"Najpierw wypozycz ksiazke!\n";
                borrow(client_repository.get_clients().at(j),elements[j],is_day());
            }
        }
    }
}