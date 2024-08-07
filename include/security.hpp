/*
  security.hpp
  
  Author: Paul Hamilton (paul@visualops.com)
  Date: 23-Jun-2024
    
  Security code for Nodes.
  
  Licensed under [version 3 of the GNU General Public License] contained in LICENSE.
 
  https://github.com/visualopsholdings/nodes
*/

#ifndef H_security
#define H_security

#include "storage/schema.hpp"

#include <string>
#include <boost/json.hpp>
#include <memory>

using namespace std;
using json = boost::json::value;

class VID;

class Security {

public:

  static shared_ptr<Security> instance() {
    if(!_instance) {
      _instance.reset(new Security());
    }
    return _instance;
  };
    
  bool valid(const VID &vid, const string &salt, const string &hash);
    // return true if the VID is valid. The salt is generated with the user, and the
    // hash is a premade hash of the password (we don't store the actual password)
    
  void getPolicyUsers(const string &id, vector<string> *users);
    // get a list of users that are in this policy.
  
  // execute a query ensuring that the user can view the results.
  template <typename RowType>
  optional<vector<RowType> > withView(Schema<RowType> &schema, const string &userid, const json &query, const vector<string> &fields = {}) {
  
    GroupViewPermissions groupviews;
    UserViewPermissions userviews;
    return schema.find(withQuery(groupviews, userviews, userid, query), fields).values();
    
  }

    // execute a query ensuring that the user can edit the results.
  template <typename RowType>
  optional<vector<RowType> > withEdit(Schema<RowType> &schema, const string &userid, const json &query, const vector<string> &fields = {}) {
  
    GroupEditPermissions groupviews;
    UserEditPermissions userviews;
    return schema.find(withQuery(groupviews, userviews, userid, query), fields).values();
    
  }
    
private:

  // there can be only 1.
  Security() {};
  static shared_ptr<Security> _instance;
  
  void addTo(vector<string> *v, const string &val);
  void queryIndexes(Schema<IndexRow> &schema, const vector<string> &inids, vector<string> *ids);
  boost::json::array createArray(const vector<string> &list);
  json withQuery(Schema<IndexRow> &gperm, Schema<IndexRow> &uperm, const string &userid, const json &query);

};

#endif // H_security
