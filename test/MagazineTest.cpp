#include <boost/test/unit_test.hpp>

#include <iostream>
#include <stdexcept>
#include "Element.h"
#include "Magazine.h"
#include "Typedef.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(MagazineTest)

    BOOST_AUTO_TEST_CASE(ConstructorTest)
    {
        ElementPtr m1(new Magazine(22,3,"wyd2","czasopismo",100));
        BOOST_REQUIRE_EQUAL(m1->get_title_or_name(), "czasopismo");
        BOOST_REQUIRE_EQUAL(m1->get_number(), 100);
        BOOST_REQUIRE_EQUAL(m1->get_id(), 22);
        BOOST_REQUIRE_EQUAL(m1->get_size(), 3);
        BOOST_REQUIRE_EQUAL(m1->get_publisher(), "wyd2");
        BOOST_CHECK_THROW(m1->get_year(), out_of_range);
        BOOST_CHECK_THROW(m1->get_genre(), out_of_range);
    }

    BOOST_AUTO_TEST_CASE(SetterTest)
    {
        ElementPtr m1(new Magazine(22,3,"wyd2","czasopismo",100));
        BOOST_CHECK_THROW(m1->set_year(2018), out_of_range);
        BOOST_CHECK_THROW(m1->set_genre("gat3"), out_of_range);
        m1.reset();
    }

    BOOST_AUTO_TEST_CASE(CounterTest)
    {
        ElementPtr m1(new Magazine(22,3,"wyd2","czasopismo",100));
        BOOST_REQUIRE_EQUAL(Magazine::get_counter(), 1);
        m1.reset();
        BOOST_REQUIRE_EQUAL(Magazine::get_counter(), 0);
    }

BOOST_AUTO_TEST_SUITE_END()