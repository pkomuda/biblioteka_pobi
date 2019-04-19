#include <boost/test/unit_test.hpp>

#include <iostream>
#include <stdexcept>
#include "Element.h"
#include "Magazine.h"
#include "Book.h"
#include "Shelf.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(ShelfTest)

    BOOST_AUTO_TEST_CASE(ConstructorTest)
    {
        ShelfPtr s(new Shelf(1,10));
        BOOST_REQUIRE_EQUAL(s->get_number(), 1);
        BOOST_REQUIRE_EQUAL(s->get_capacity(), 10);
    }

    BOOST_AUTO_TEST_CASE(TakeTest)
    {
        ShelfPtr s(new Shelf(1,10));
        ElementPtr b(new Book(11,4,"wyd1","ksiazka","autor","gatunek",2000));
        ElementPtr m(new Magazine(22,3,"wyd2","czasopismo",100));
        s->take(b);
        s->take(m);
        cout<<s->to_string();
        BOOST_REQUIRE_EQUAL(s->get_element_amount(), 2);
        BOOST_REQUIRE_EQUAL(s->get_taken_space(), 7);

    }

    BOOST_AUTO_TEST_CASE(TakeTestException)
    {
        ShelfPtr s(new Shelf(1,5));
        ElementPtr b(new Book(11,4,"wyd1","ksiazka","autor","gatunek",2000));
        ElementPtr m(new Magazine(22,3,"wyd2","czasopismo",100));
        s->take(b);
        BOOST_CHECK_THROW(s->take(m), out_of_range);
        cout<<s->to_string();
        BOOST_REQUIRE_EQUAL(s->get_element_amount(), 1);
        BOOST_REQUIRE_EQUAL(s->get_taken_space(), 4);
    }

    BOOST_AUTO_TEST_CASE(GiveTest)
    {
        ShelfPtr s(new Shelf(1,10));
        ElementPtr b(new Book(11,4,"wyd1","ksiazka","autor","gatunek",2000));
        ElementPtr m(new Magazine(22,3,"wyd2","czasopismo",100));
        s->take(b);
        s->take(m);
        BOOST_REQUIRE_EQUAL(s->give(m), m);
        BOOST_REQUIRE_EQUAL(s->get_element_amount(), 1);
        BOOST_REQUIRE_EQUAL(s->get_taken_space(), 4);
    }

    BOOST_AUTO_TEST_CASE(AtTest)
    {
        ShelfPtr s(new Shelf(1,10));
        ElementPtr b(new Book(11,4,"wyd1","ksiazka","autor","gatunek",2000));
        ElementPtr m(new Magazine(22,3,"wyd2","czasopismo",100));
        s->take(b);
        s->take(m);
        BOOST_REQUIRE_EQUAL(s->at(1)->get_id(), 22);
    }

BOOST_AUTO_TEST_SUITE_END()