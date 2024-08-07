/*
  json.hpp
  
  Author: Paul Hamilton (paul@visualops.com)
  Date: 2-Jul-2024
    
  JSON code for Nodes
  
  Licensed under [version 3 of the GNU General Public License] contained in LICENSE.
 
  https://github.com/visualopsholdings/nodes
*/

#ifndef H_json
#define H_json

#include <string>
#include <boost/json.hpp>

using namespace std;
using json = boost::json::value;

class Json {

public:

  static string toISODate(json &date);
  static optional<string> getString(json &j, const string &name);
  static optional<boost::json::array> getArray(json &reply, const string &name);
  static optional<json> getObject(json &j, const string &name);
  static optional<bool> getBool(json &j, const string &name);

};

#endif // H_json
