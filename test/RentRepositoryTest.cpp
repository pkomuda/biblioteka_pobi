#include <boost/test/unit_test.hpp>

#include <iostream>
#include <stdexcept>
#include "Rent.h"
#include "RentRepository.h"
#include "Client.h"
#include "Element.h"
#include "Book.h"
#include "Magazine.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(RentRepositoryTest)

    BOOST_AUTO_TEST_CASE(AddTest)
    {
        ClientPtr c(new Client("1","Jan","Kowalski",123456789,"Retkinska","3a","Lodz"));
        ElementPtr b(new Book(11,4,"wyd1","ksiazka","autor","gatunek",2000));
        ElementPtr m(new Magazine(22,3,"wyd2","czasopismo",100));
        RentRepository rr;
        BOOST_REQUIRE_EQUAL(rr.get_rent_amount(), 0);
        RentPtr r1(new Rent(c,b,9,15,17));
        RentPtr r2(new Rent(c,m,10,8,0));
        rr.add(r1);
        rr.add(r2);
        cout<<rr.to_string();
        BOOST_REQUIRE_EQUAL(rr.get_rent_amount(), 2);
    }

    BOOST_AUTO_TEST_CASE(GetRentsTest)
    {
        ClientPtr c(new Client("1","Jan","Kowalski",123456789,"Retkinska","3a","Lodz"));
        ElementPtr b(new Book(11,4,"wyd1","ksiazka","autor","gatunek",2000));
        ElementPtr m(new Magazine(22,3,"wyd2","czasopismo",100));
        RentPtr r1(new Rent(c,b,9,15,17));
        RentPtr r2(new Rent(c,m,10,8,0));
        RentRepository rr;
        rr.add(r1);
        rr.add(r2);
        BOOST_REQUIRE_EQUAL(rr.get_rent_repository()[0]->get_id(), 9);
        BOOST_REQUIRE_EQUAL(rr.get_rent_repository()[1]->get_id(), 10);
    }

    BOOST_AUTO_TEST_CASE(RemoveTest)
    {
        ClientPtr c(new Client("1","Jan","Kowalski",123456789,"Retkinska","3a","Lodz"));
        ElementPtr b(new Book(11,4,"wyd1","ksiazka","autor","gatunek",2000));
        ElementPtr m(new Magazine(22,3,"wyd2","czasopismo",100));
        RentRepository rr;
        RentPtr r1(new Rent(c,b,9,15,17));
        RentPtr r2(new Rent(c,m,10,8,0));
        rr.add(r1);
        rr.add(r2);
        BOOST_REQUIRE_EQUAL(rr.get_rent_amount(), 2);
        rr.remove(r1);
        BOOST_REQUIRE_EQUAL(rr.get_rent_amount(), 1);
    }

    BOOST_AUTO_TEST_CASE(RemoveTestException)
    {
        ClientPtr c(new Client("1","Jan","Kowalski",123456789,"Retkinska","3a","Lodz"));
        ElementPtr b1(new Book(11,4,"wyd1","ksiazka","autor","gatunek",2000));
        ElementPtr m1(new Magazine(22,3,"wyd2","czasopismo",100));
        ElementPtr m2(new Magazine(33,3,"wyd2","czasopismo",100));
        RentRepository rr;
        RentPtr r1(new Rent(c,b1,9,15,17));
        RentPtr r2(new Rent(c,m1,10,8,0));
        RentPtr r3(new Rent(c,m2,10,8,0));
        rr.add(r1);
        rr.add(r2);
        BOOST_CHECK_THROW(rr.remove(r3), out_of_range);
    }

    BOOST_AUTO_TEST_CASE(AtTest)
    {
        ClientPtr c(new Client("1","Jan","Kowalski",123456789,"Retkinska","3a","Lodz"));
        ElementPtr b(new Book(11,4,"wyd1","ksiazka","autor","gatunek",2000));
        ElementPtr m(new Magazine(22,3,"wyd2","czasopismo",100));
        RentRepository rr;
        RentPtr r1(new Rent(c,b,9,15,17));
        RentPtr r2(new Rent(c,m,10,8,0));
        rr.add(r1);
        rr.add(r2);
        BOOST_REQUIRE_EQUAL(rr.at(0), r1);
        BOOST_REQUIRE_EQUAL(rr.at(1), r2);
    }

BOOST_AUTO_TEST_SUITE_END()
