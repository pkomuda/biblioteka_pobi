#include <boost/test/unit_test.hpp>

#include <iostream>
#include <stdexcept>
#include "Client.h"
#include "Address.h"
#include "Element.h"
#include "Book.h"
#include "Magazine.h"
#include "Rent.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(ClientTest)

    BOOST_AUTO_TEST_CASE(ClientConstructorTest)
    {
        ClientPtr c(new Client("1","Jan","Kowalski",123456789,"Retkinska","3a","Lodz"));
        BOOST_REQUIRE_EQUAL(c->get_id(), "1");
        BOOST_REQUIRE_EQUAL(c->get_first_name(), "Jan");
        BOOST_REQUIRE_EQUAL(c->get_last_name(), "Kowalski");
        BOOST_REQUIRE_EQUAL(c->get_phone(), 123456789);
    }

    BOOST_AUTO_TEST_CASE(ClientSetterTest)
    {
        ClientPtr c(new Client("1","Jan","Kowalski",123456789,"Retkinska","3a","Lodz"));
        c->set_phone(999999999);
        BOOST_REQUIRE_EQUAL(c->get_phone(), 999999999);
    }

    BOOST_AUTO_TEST_CASE(ClientGetAddressTest)
    {
        ClientPtr c(new Client("1","Jan","Kowalski",123456789,"Retkinska","3a","Lodz"));
        cout<<c->to_string();
        BOOST_REQUIRE_EQUAL(c->get_address().get_street(), "Retkinska");
        BOOST_REQUIRE_EQUAL(c->get_address().get_house(), "3a");
        BOOST_REQUIRE_EQUAL(c->get_address().get_city(), "Lodz");
    }

    BOOST_AUTO_TEST_CASE(ClientGetRentAmountTest)
    {
        ClientPtr c(new Client("1","Jan","Kowalski",123456789,"Retkinska","3a","Lodz"));
        ElementPtr m(new Magazine(22,3,"wyd2","czasopismo",100));
        RentPtr r(new Rent(c,m,10,8,0));
        c->add_rent(r);
        cout<<c->print_rents();
        BOOST_CHECK_EQUAL(c->get_rent_amount(), 1);
    }

    BOOST_AUTO_TEST_CASE(ClientAddRentTestException)
    {
        ClientPtr c1(new Client("1","Jan","Kowalski",123456789,"Retkinska","3a","Lodz"));
        ClientPtr c2(new Client("2","Jan","Kowalski",123456789,"Retkinska","3a","Lodz"));
        ElementPtr m(new Magazine(22,3,"wyd2","czasopismo",100));
        RentPtr r(new Rent(c1,m,10,8,0));
        BOOST_CHECK_THROW(c2->add_rent(r), out_of_range);
    }

    BOOST_AUTO_TEST_CASE(ClientRemoveRentTest)
    {
        ClientPtr c(new Client("1","Jan","Kowalski",123456789,"Retkinska","3a","Lodz"));
        ElementPtr b(new Book(11,4,"wyd1","ksiazka","autor","gatunek",2000));
        ElementPtr m(new Magazine(22,3,"wyd2","czasopismo",100));
        RentPtr r1(new Rent(c,b,9,15,17));
        RentPtr r2(new Rent(c,m,10,8,0));
        BOOST_CHECK_THROW(c->add_rent(r1), out_of_range);
        c->add_rent(r2);
        BOOST_CHECK_THROW(c->remove_rent(r1), out_of_range);
        BOOST_CHECK_EQUAL(c->remove_rent(r2), true);
        cout<<c->print_rents();
        BOOST_CHECK_EQUAL(c->get_rent_amount(), 0);
    }

BOOST_AUTO_TEST_SUITE_END()