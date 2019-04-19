#include <boost/test/unit_test.hpp>

#include "Rent.h"
#include "Client.h"
#include "Element.h"
#include "Book.h"
#include "Magazine.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(RentTest)

    BOOST_AUTO_TEST_CASE(ConstructorTest)
    {
        ClientPtr c(new Client("1","Jan","Kowalski",123456789,"Retkinska","3a","Lodz"));
        ElementPtr m(new Magazine(22,3,"wyd2","czasopismo",100));
        RentPtr r(new Rent(c,m,10,8,0));
        BOOST_REQUIRE_EQUAL(r->get_id(), 10);
        BOOST_REQUIRE_EQUAL(r->get_rent_date(), 8);
        BOOST_REQUIRE_EQUAL(r->get_return_date(), 0);
        BOOST_REQUIRE_EQUAL(r->get_client()->get_id(), "1");
        BOOST_REQUIRE_EQUAL(r->get_element()->get_id(), 22);
    }

    BOOST_AUTO_TEST_CASE(RentToStringTest)
    {
        ClientPtr c(new Client("1","Jan","Kowalski",123456789,"Retkinska","3a","Lodz"));
        ElementPtr b(new Book(11,4,"wyd1","ksiazka","autor","gatunek",2000));
        ElementPtr m(new Magazine(22,3,"wyd2","czasopismo",100));
        RentPtr r1(new Rent(c,b,9,15,17));
        RentPtr r2(new Rent(c,m,10,8,0));
        BOOST_CHECK_EQUAL(r1->to_string(), "Jan Kowalski wypozyczyl(a) ,,ksiazka'' (ID: 11) 15 dnia miesiaca i oddal(a) go 17 dnia miesiaca\n");
        BOOST_CHECK_EQUAL(r2->to_string(), "Jan Kowalski wypozyczyl(a) ,,czasopismo'' (ID: 22) 8 dnia miesiaca i jeszcze go nie oddal(a)\n");
    }


BOOST_AUTO_TEST_SUITE_END()
