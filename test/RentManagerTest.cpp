#include <boost/test/unit_test.hpp>

#include <iostream>
#include <stdexcept>
#include <random>
#include <functional>
#include <chrono>
#include "Shelf.h"
#include "Rent.h"
#include "RentManager.h"
#include "Client.h"
#include "Element.h"
#include "Book.h"
#include "Magazine.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(RentManagerTest)

    BOOST_AUTO_TEST_CASE(ConstructorTest)
    {
        auto *rm = new RentManager;
        BOOST_REQUIRE_EQUAL(rm->is_day(), 1);
        BOOST_REQUIRE_EQUAL(rm->is_hour(), 8);
        delete rm;
    }

    BOOST_AUTO_TEST_CASE(GetClientsAmountTest)
    {
        auto *rm = new RentManager;
        ClientPtr c1(new Client("1","Jan","Kowalski",123456789,"Retkinska","3a","Lodz"));
        ClientPtr c2(new Client("2","Adam","Nowak",234567890,"Politechniki","10","Lodz"));
        ClientPtr c3(new Client("3","Michał","Marianski",345678901,"Piotrkowska","5","Lodz"));
        rm->get_clients_repository().add(c1);
        rm->get_clients_repository().add(c2);
        rm->get_clients_repository().add(c3);
        BOOST_REQUIRE_EQUAL(rm->get_clients_amount(), 3);
        delete rm;
    }

    BOOST_AUTO_TEST_CASE(GetClientsRepositoryTest)
    {
        auto *rm = new RentManager;
        ClientPtr c1(new Client("1","Jan","Kowalski",123456789,"Retkinska","3a","Lodz"));
        ClientPtr c2(new Client("2","Adam","Nowak",234567890,"Politechniki","10","Lodz"));
        ClientPtr c3(new Client("3","Michał","Marianski",345678901,"Piotrkowska","5","Lodz"));
        rm->get_clients_repository().add(c1);
        rm->get_clients_repository().add(c2);
        rm->get_clients_repository().add(c3);
        BOOST_REQUIRE_EQUAL(rm->get_clients_repository().get_clients().at(0)->get_id(), "1");
        BOOST_REQUIRE_EQUAL(rm->get_clients_repository().get_clients().at(1)->get_id(), "2");
        BOOST_REQUIRE_EQUAL(rm->get_clients_repository().get_clients().at(2)->get_id(), "3");
        delete rm;
    }

    BOOST_AUTO_TEST_CASE(GetEmployeesRepositoryTest)
    {
        auto *rm = new RentManager;
        EmployeeRepository er;
        Employee e1("1");
        Employee e2("2");
        rm->get_employees_repository().exchange(er.get_employee(0), e1);
        rm->get_employees_repository().exchange(er.get_employee(1), e2);
        BOOST_REQUIRE_EQUAL(rm->get_employees_repository().get_employee(0).get_id(), "1");
        BOOST_REQUIRE_EQUAL(rm->get_employees_repository().get_employee(1).get_id(), "2");
        delete rm;
    }

    BOOST_AUTO_TEST_CASE(MakeRentTest)
    {
        auto *rm = new RentManager;
        ClientPtr c1(new Client("1","Jan","Kowalski",123456789,"Retkinska","3a","Lodz"));
        ElementPtr m1(new Magazine(22,3,"wyd2","czasopismo",100));
        rm->get_clients_repository().add(c1);
        BOOST_REQUIRE_EQUAL(rm->get_clients_repository().get_clients().at(0)->get_rent_amount(), 0);
        rm->make_rent(c1,m1,15,0);
        BOOST_REQUIRE_EQUAL(rm->get_clients_repository().get_clients().at(0)->get_rent_amount(), 1);
        delete rm;
    }

    BOOST_AUTO_TEST_CASE(BorrowTest)
    {
        auto *rm = new RentManager;
        EmployeeRepository er;
        Employee e1("1");
        Employee e2("2");
        rm->get_employees_repository().exchange(er.get_employee(0), e1);
        rm->get_employees_repository().exchange(er.get_employee(1), e2);

        ClientPtr c1(new Client("1","Jan","Kowalski",123456789,"Retkinska","3a","Lodz"));
        ElementPtr m1(new Magazine(22,3,"wyd2","czasopismo",100));
        ShelfPtr s(new Shelf(5,3));
        s->take(m1);
        rm->get_employees_repository().add_shelf(s);

        rm->get_clients_repository().add(c1);
        BOOST_REQUIRE_EQUAL(rm->get_current_rents().get_rent_amount(), 0);
        rm->borrow(c1,m1,15,0);
        BOOST_REQUIRE_EQUAL(rm->get_current_rents().get_rent_amount(), 1);
        delete rm;
    }

    BOOST_AUTO_TEST_CASE(MoveToPastTest)
    {
        auto *rm = new RentManager;
        EmployeeRepository er;
        Employee e1("1");
        Employee e2("2");
        rm->get_employees_repository().exchange(er.get_employee(0), e1);
        rm->get_employees_repository().exchange(er.get_employee(1), e2);

        ClientPtr c1(new Client("1","Jan","Kowalski",123456789,"Retkinska","3a","Lodz"));
        ElementPtr m1(new Magazine(22,3,"wyd2","czasopismo",100));
        ShelfPtr s(new Shelf(5,3));
        s->take(m1);
        rm->get_employees_repository().add_shelf(s);
        rm->get_clients_repository().add(c1);

        BOOST_REQUIRE_EQUAL(rm->get_past_rents().get_rent_amount(), 0);
        BOOST_REQUIRE_EQUAL(rm->get_current_rents().get_rent_amount(), 0);
        BOOST_REQUIRE_EQUAL(rm->get_clients_repository().get_clients().at(0)->get_rent_amount(), 0);
        rm->borrow(c1,m1,15,0);
        BOOST_REQUIRE_EQUAL(rm->get_past_rents().get_rent_amount(), 0);
        BOOST_REQUIRE_EQUAL(rm->get_current_rents().get_rent_amount(), 1);
        BOOST_REQUIRE_EQUAL(rm->get_clients_repository().get_clients().at(0)->get_rent_amount(), 1);

        rm->move_to_past(rm->get_current_rents().at(0));
        BOOST_REQUIRE_EQUAL(rm->get_past_rents().get_rent_amount(), 1);
        BOOST_REQUIRE_EQUAL(rm->get_current_rents().get_rent_amount(), 0);
        BOOST_REQUIRE_EQUAL(rm->get_clients_repository().get_clients().at(0)->get_rent_amount(), 0);
        delete rm;
    }

    BOOST_AUTO_TEST_CASE(TakeBackTest)
    {
        auto *rm = new RentManager;
        EmployeeRepository er;
        Employee e1("1");
        Employee e2("2");
        rm->get_employees_repository().exchange(er.get_employee(0), e1);
        rm->get_employees_repository().exchange(er.get_employee(1), e2);
        ClientPtr c1(new Client("1","Jan","Kowalski",123456789,"Retkinska","3a","Lodz"));
        ElementPtr m1(new Magazine(22,3,"wyd2","czasopismo",100));
        ShelfPtr s(new Shelf(5,3));
        s->take(m1);
        rm->get_employees_repository().add_shelf(s);
        rm->get_clients_repository().add(c1);
        rm->borrow(c1,m1,15,0);
        rm->move_to_past(rm->get_current_rents().at(0));
        BOOST_REQUIRE_EQUAL(rm->get_employees_repository().get_shelves().at(0)->get_taken_space(), 0);
        BOOST_REQUIRE_EQUAL(rm->get_employees_repository().get_shelves().at(0)->get_element_amount(), 0);
        rm->take_back(rm->get_past_rents().at(0));
        BOOST_REQUIRE_EQUAL(rm->get_employees_repository().get_shelves().at(0)->get_taken_space(), 3);
        BOOST_REQUIRE_EQUAL(rm->get_employees_repository().get_shelves().at(0)->get_element_amount(), 1);
        delete rm;
    }

BOOST_AUTO_TEST_SUITE_END()
