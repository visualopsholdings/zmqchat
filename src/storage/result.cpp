/*
  result.cpp
  
  Author: Paul Hamilton (paul@visualops.com)
  Date: 5-June-2024
  
  Licensed under [version 3 of the GNU General Public License] contained in LICENSE.
 
  https://github.com/visualopsholdings/nodes
*/

#include "storage/result.hpp"

#include "storage/resulti.hpp"
#include "storage/schemai.hpp"
#include "json.hpp"

#include <boost/log/trivial.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/options/find.hpp>
#include <sstream>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;

mongocxx::cursor ResultImpl::find() {

  mongocxx::options::find opts{};
  if (_f.size() > 0) {
    boost::json::object j;
    for (auto i: _f) {
      j[i] = 1;
    }
    stringstream ss;
    ss << j;
    opts.projection(bsoncxx::from_json(ss.str()));
  }
  
  return _c.find(_q, opts);

}

json ResultImpl::fixObjects(const json &j) {

  boost::json::object o;
  for (auto i: j.as_object()) {
    if (i.value().is_object()) {
      if (i.key() == "_id" && i.value().is_object() && i.value().as_object().if_contains("$oid")) {
        o["id"] = i.value().at("$oid");
        continue;
      }
      if (i.value().is_object() && i.value().as_object().if_contains("$date")) {
        o[i.key()] = Json::toISODate(i.value());
        continue;
      }
    }
    o[i.key()] = i.value();
  }
  return o;

}

optional<json> ResultImpl::value() {
  
  if (!_c) {
    return {};
  }
  
  mongocxx::cursor cursor = find();
  if (cursor.begin() == cursor.end()) {
    BOOST_LOG_TRIVIAL(trace) << "empty";
    return {};
  }
  auto first = cursor.begin();
  if (first == cursor.end()) {
    return {}; 
  }
  return fixObjects(boost::json::parse(bsoncxx::to_json(*first)));
  
}

optional<boost::json::array> ResultImpl::values() {
  
  if (!_c) {
    return {};
  }
  
  mongocxx::cursor cursor = find();
  if (cursor.begin() == cursor.end()) {
    BOOST_LOG_TRIVIAL(trace) << "empty";
    return {};
  }
  boost::json::array val;
  for (auto i: cursor) {
    val.push_back(fixObjects(boost::json::parse(bsoncxx::to_json(i))));
  }
  return val;
  
}

