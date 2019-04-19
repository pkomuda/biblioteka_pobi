#include <boost/test/unit_test.hpp>

#include "Element.h"
#include "Book.h"
#include "Typedef.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(BookTest)

    BOOST_AUTO_TEST_CASE(ConstructorTest)
    {
        ElementPtr b1(new Book(11,4,"wyd1","ksiazka","autor","gatunek",2000));
        BOOST_REQUIRE_EQUAL(b1->get_title_or_name(), "ksiazka");
        BOOST_REQUIRE_EQUAL(b1->get_author(), "autor");
        BOOST_REQUIRE_EQUAL(b1->get_year(), 2000);
        BOOST_REQUIRE_EQUAL(b1->get_genre(), "gatunek");
        BOOST_REQUIRE_EQUAL(b1->get_id(), 11);
        BOOST_REQUIRE_EQUAL(b1->get_size(), 4);
        BOOST_REQUIRE_EQUAL(b1->get_publisher(), "wyd1");
    }

    BOOST_AUTO_TEST_CASE(SetterTest)
    {
        ElementPtr b1(new Book(11,4,"wyd1","ksiazka","autor","gatunek",2000));
        b1->set_genre("gat2");
        b1->set_publisher("wyd2");
        b1->set_year(1999);
        BOOST_REQUIRE_EQUAL(b1->get_genre(), "gat2");
        BOOST_REQUIRE_EQUAL(b1->get_year(), 1999);
        BOOST_REQUIRE_EQUAL(b1->get_publisher(), "wyd2");
    }

    BOOST_AUTO_TEST_CASE(CounterTest)
    {
        ElementPtr b1(new Book(11,4,"wyd1","ksiazka","autor","gatunek",2000));
        ElementPtr b2(new Book(11,4,"wyd1","ksiazka","autor","gatunek",2000));
        ElementPtr b3(new Book(11,4,"wyd1","ksiazka","autor","gatunek",2000));
        ElementPtr b4(new Book(11,4,"wyd1","ksiazka","autor","gatunek",2000));
        BOOST_REQUIRE_EQUAL(Book::get_counter(), 4);
        b4.reset();
        BOOST_REQUIRE_EQUAL(Book::get_counter(), 3);
    }

BOOST_AUTO_TEST_SUITE_END()