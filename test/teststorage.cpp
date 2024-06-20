/*
  teststorage.cpp
  
  Author: Paul Hamilton (paul@visualops.com)
  Date: 23-May-2024
  
  Licensed under [version 3 of the GNU General Public License] contained in LICENSE.
 
  https://github.com/visualopsholdings/zmqchat
*/

#include <iostream>

#include "storage.hpp"

#define BOOST_AUTO_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace std;

// only one can be.
Storage storage;

void dbSetup() {
  User(storage).deleteMany({{}});
  BOOST_CHECK(User(storage).insert({
    { "name", "tracy" },
    { "admin", true },
    { "fullname", "Tracy" }
  }));
  BOOST_CHECK(User(storage).insert({
    { "name", "leanne" },
    { "admin", false },
    { "fullname", "Leanne" }
  }));
}

BOOST_AUTO_TEST_CASE( user )
{
  cout << "=== user ===" << endl;
  
  dbSetup();
  
  auto doc = User(storage).find({{ "name", "tracy" }}, {"id"}).value();
  cout << doc.value() << endl;
  BOOST_CHECK(doc);
  BOOST_CHECK(doc.value().is_object());
  BOOST_CHECK(doc.value().as_object().if_contains("id"));
  BOOST_CHECK(doc.value().at("id").is_string());
  string id = boost::json::value_to<string>(doc.value().at("id"));
  cout << id << endl;
  
}

BOOST_AUTO_TEST_CASE( findAll )
{
  cout << "=== findAll ===" << endl;
  
  dbSetup();

  auto doc = User(storage).find(json{{}}, {"id"}).values();
  BOOST_CHECK(doc);
//  cout << doc.value() << endl;
  BOOST_CHECK(doc.value().is_array());
  BOOST_CHECK_EQUAL(doc.value().as_array().size(), 2);
  BOOST_CHECK(doc.value().as_array()[0].at("id").is_string());
  BOOST_CHECK(doc.value().as_array()[1].at("id").is_string());
  
}