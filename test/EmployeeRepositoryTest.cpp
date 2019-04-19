#include <boost/test/unit_test.hpp>

#include <iostream>
#include <stdexcept>
#include "Employee.h"
#include "Element.h"
#include "Book.h"
#include "Magazine.h"
#include "EmployeeRepository.h"
#include "Shelf.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(EmployeeRepositoryTest)

    BOOST_AUTO_TEST_CASE(ConstructorTest)
    {
        vector<Employee> employees;
        Employee e1("1");
        Employee e2("2");
        employees.push_back(e1);
        employees.push_back(e2);
        EmployeeRepository er(employees);
        BOOST_REQUIRE_EQUAL(er.get_employees_amount(), 2);
        cout<<er.to_string();
    }

    BOOST_AUTO_TEST_CASE(ConstructorTestTooManyEmployees)
    {
        vector<Employee> employees;
        Employee e1("1");
        Employee e2("2");
        Employee e3("3");
        employees.push_back(e1);
        employees.push_back(e2);
        employees.push_back(e3);
        BOOST_CHECK_THROW(EmployeeRepository er(employees), out_of_range);
    }

    BOOST_AUTO_TEST_CASE(ConstructorTestNotEnoughEmployees)
    {
        vector<Employee> employees;
        Employee e1("1");
        employees.push_back(e1);
        BOOST_CHECK_THROW(EmployeeRepository er(employees), out_of_range);
    }

    BOOST_AUTO_TEST_CASE(GetEmployeeTest)
    {
        vector<Employee> employees;
        Employee e1("1");
        Employee e2("2");
        employees.push_back(e1);
        employees.push_back(e2);
        EmployeeRepository er(employees);
        BOOST_REQUIRE_EQUAL(er.get_employee(0).get_id(), "1");
        BOOST_REQUIRE_EQUAL(er.get_employee(1).get_id(), "2");
    }

    BOOST_AUTO_TEST_CASE(AddShelfTest)
    {
        vector<Employee> employees;
        Employee e1("1");
        Employee e2("2");
        employees.push_back(e1);
        employees.push_back(e2);
        EmployeeRepository er(employees);
        ShelfPtr s(new Shelf(3));
        BOOST_REQUIRE_EQUAL(er.get_shelves().size(), 0);
        er.add_shelf(s);
        BOOST_REQUIRE_EQUAL(er.get_shelves().size(), 1);
        BOOST_REQUIRE_EQUAL(er.get_shelves().at(0)->get_number(), 3);
    }

    BOOST_AUTO_TEST_CASE(RemoveShelfTest)
    {
        vector<Employee> employees;
        Employee e1("1");
        Employee e2("2");
        employees.push_back(e1);
        employees.push_back(e2);
        EmployeeRepository er(employees);
        ShelfPtr s(new Shelf(3));
        er.add_shelf(s);
        er.remove_shelf(s);
        BOOST_REQUIRE_EQUAL(er.get_shelves().size(), 0);
    }

    BOOST_AUTO_TEST_CASE(ElementAmountTest)
    {
        vector<Employee> employees;
        Employee e1("1");
        Employee e2("2");
        employees.push_back(e1);
        employees.push_back(e2);
        EmployeeRepository er(employees);
        ShelfPtr s1(new Shelf(1,7));
        ShelfPtr s2(new Shelf(2,1));
        ElementPtr b1(new Book(11,4,"wyd1","ksiazka","autor","gatunek",2000));
        ElementPtr m1(new Magazine(22,3,"wyd2","czasopismo",100));
        ElementPtr m2(new Magazine(33,1,"wyd2","czasopismo",100));
        s1->take(b1);
        s1->take(m1);
        s2->take(m2);
        er.add_shelf(s1);
        er.add_shelf(s2);
        BOOST_REQUIRE_EQUAL(er.amount_of_allocated_elements(), 3);
    }

    BOOST_AUTO_TEST_CASE(CanTakeTest)
    {
        ElementPtr m(new Magazine(33,1,"wyd2","czasopismo",100));
        vector<Employee> employees;
        Employee e1("1");
        Employee e2("2");
        employees.push_back(e1);
        employees.push_back(e2);
        EmployeeRepository er(employees);
        er.get_employee(0).take_element(m);
        BOOST_REQUIRE_EQUAL(er.can_take(0), false);
        BOOST_REQUIRE_EQUAL(er.can_take(1), true);
    }

    BOOST_AUTO_TEST_CASE(ExchangeTest)
    {
        vector<Employee> employees;
        Employee e1("1");
        Employee e2("2");
        Employee n("3");
        employees.push_back(e1);
        employees.push_back(e2);
        EmployeeRepository er(employees);
        er.exchange(e1,n);
        BOOST_REQUIRE_EQUAL(er.get_employees_amount(), 2);
        BOOST_REQUIRE_EQUAL(er.get_employee(0).get_id(), "3");
    }

    BOOST_AUTO_TEST_CASE(PickUpTest)
    {
        vector<Employee> employees;
        Employee e1("1");
        Employee e2("2");
        employees.push_back(e1);
        employees.push_back(e2);
        EmployeeRepository er(employees);
        ShelfPtr s1(new Shelf(1,7));
        ElementPtr b1(new Book(11,4,"wyd1","ksiazka","autor","gatunek",2000));
        ElementPtr m1(new Magazine(22,3,"wyd2","czasopismo",100));
        s1->take(b1);
        s1->take(m1);
        er.add_shelf(s1);
        BOOST_REQUIRE_EQUAL(er.pick_up(m1)->get_id(), 22);
        BOOST_REQUIRE_EQUAL(er.get_shelves().at(0)->get_taken_space(), 4);
        BOOST_REQUIRE_EQUAL(er.get_shelves().at(0)->get_element_amount(), 1);
    }

    BOOST_AUTO_TEST_CASE(PutDownTest)
    {
        vector<Employee> employees;
        Employee e1("1");
        Employee e2("2");
        employees.push_back(e1);
        employees.push_back(e2);
        EmployeeRepository er(employees);
        ShelfPtr s1(new Shelf(1,7));
        ElementPtr b1(new Book(11,4,"wyd1","ksiazka","autor","gatunek",2000));
        ElementPtr m1(new Magazine(22,3,"wyd2","czasopismo",100));
        s1->take(b1);
        er.add_shelf(s1);
        er.put_down(m1);
        BOOST_REQUIRE_EQUAL(er.get_shelves().at(0)->get_taken_space(), 7);
        BOOST_REQUIRE_EQUAL(er.get_shelves().at(0)->get_element_amount(), 2);
    }

BOOST_AUTO_TEST_SUITE_END()