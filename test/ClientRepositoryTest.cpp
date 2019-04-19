#include <boost/test/unit_test.hpp>

#include <iostream>
#include <stdexcept>
#include "ClientRepository.h"
#include "Client.h"
#include "Address.h"
#include "Rent.h"
#include "Book.h"
#include "Magazine.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(ClientRepositoryTest)

    BOOST_AUTO_TEST_CASE(ClientRepositoryAddTest)
    {
        ClientRepository r;
        BOOST_REQUIRE_EQUAL(r.get_clients_amount(), 0);
        ClientPtr c1(new Client("1","Jan","Kowalski",123456789,"Retkinska","3a","Lodz"));
        ClientPtr c2(new Client("2","Adam","Nowak",234567890,"Politechniki","10","Lodz"));
        ClientPtr c3(new Client("3","Michał","Marianski",345678901,"Piotrkowska","5","Lodz"));
        r.add(c1);
        r.add(c2);
        r.add(c3);
        cout<<r.to_string();
        BOOST_REQUIRE_EQUAL(r.get_clients_amount(), 3);
    }

    BOOST_AUTO_TEST_CASE(ClientRepositoryRemoveTest)
    {
        ClientRepository r;
        ClientPtr c1(new Client("1","Jan","Kowalski",123456789,"Retkinska","3a","Lodz"));
        ClientPtr c2(new Client("2","Adam","Nowak",234567890,"Politechniki","10","Lodz"));
        ClientPtr c3(new Client("3","Michał","Marianski",345678901,"Piotrkowska","5","Lodz"));
        ClientPtr c4(new Client("4","Anna","Golonka",456789012,"Maratonska","12","Lodz"));
        r.add(c1);
        r.add(c2);
        r.add(c3);
        BOOST_REQUIRE_EQUAL(r.remove(c2), true);
        BOOST_CHECK_THROW(r.remove(c4), out_of_range);
        cout<<r.to_string();
        BOOST_REQUIRE_EQUAL(r.get_clients_amount(), 2);
    }

    BOOST_AUTO_TEST_CASE(ClientRepositoryGetClientTest)
    {
        ClientRepository r;
        ClientPtr c1(new Client("1","Jan","Kowalski",123456789,"Retkinska","3a","Lodz"));
        r.add(c1);
        BOOST_REQUIRE_EQUAL(r.get_clients().at(0)->get_id(), "1");
    }


BOOST_AUTO_TEST_SUITE_END()