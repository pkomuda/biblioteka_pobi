#include <boost/test/unit_test.hpp>

#include <stdexcept>
#include "Employee.h"
#include "Element.h"
#include "Magazine.h"
#include "EmployeeRepository.h"
#include "Shelf.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(EmployeeTest)

    BOOST_AUTO_TEST_CASE(ConstructorTest)
    {
        Employee e("1");
        BOOST_REQUIRE_EQUAL(e.get_id(), "1");
        BOOST_REQUIRE_EQUAL(e.get_position(), -1);
    }

    BOOST_AUTO_TEST_CASE(TakeElementTest)
    {
        Employee e("1");
        ElementPtr m1(new Magazine(22,3,"wyd2","czasopismo",100));
        e.take_element(m1);
        BOOST_REQUIRE_EQUAL(e.get_element()->get_id(), 22);
    }

    BOOST_AUTO_TEST_CASE(GiveElementTest)
    {
        vector<Employee> employees;
        employees.emplace_back(Employee("1"));
        BOOST_REQUIRE_THROW(EmployeeRepository r(employees),out_of_range);
        employees.emplace_back(Employee("2"));
        EmployeeRepository r(employees);
        ElementPtr m1(new Magazine(22,3,"wyd2","czasopismo",100));
        employees.at(0).take_element(m1);
        BOOST_REQUIRE_EQUAL(employees.at(0).give_element()->get_id(), 22);
        BOOST_REQUIRE_EQUAL(employees.at(0).get_element()->get_id(), 0);
    }

    BOOST_AUTO_TEST_CASE(MoveTest)
    {
        vector<Employee> employees;
        employees.emplace_back(Employee("1"));
        employees.emplace_back(Employee("2"));
        EmployeeRepository r(employees);
        ShelfPtr s(new Shelf(5));
        r.add_shelf(s);
        BOOST_REQUIRE_EQUAL(employees[0].get_position(), -1);
        employees[0].move(r,0);
        BOOST_REQUIRE_EQUAL(employees[0].get_position(), 0);
    }

    BOOST_AUTO_TEST_CASE(MoveTestException)
    {
        vector<Employee> employees;
        employees.emplace_back(Employee("1"));
        employees.emplace_back(Employee("2"));
        EmployeeRepository r(employees);
        ShelfPtr s(new Shelf(5));
        r.add_shelf(s);
        BOOST_CHECK_THROW(employees[0].move(r,1), out_of_range);
    }

BOOST_AUTO_TEST_SUITE_END()