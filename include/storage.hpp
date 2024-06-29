/*
  storage.hpp
  
  Author: Paul Hamilton (paul@visualops.com)
  Date: 23-May-2024
    
  Storage for ZMQChat
  
  Use like:
  
    auto doc = User(storage).find({{"name", "tracy"}}).value();
    auto alldocs = User(storage).find().values();

  Licensed under [version 3 of the GNU General Public License] contained in LICENSE.
 
  https://github.com/visualopsholdings/zmqchat
*/

#ifndef H_storage
#define H_storage

#include "storage/cursor.hpp"
#include "storage/schema.hpp"

using namespace std;

class StorageImpl;

class Storage {

public:
  static shared_ptr<Storage> instance() {
    if(!_instance) {
      _instance.reset(new Storage());
    }
    return _instance;
  };
    
  void init(const string &dbConn, const string &dbName);
  
private:
  friend class Schema;

  // there can be only 1.
  Storage() {};
  static shared_ptr<Storage> _instance;
  
  shared_ptr<StorageImpl> _impl;
    
};

#endif // H_storage
