/*
  vid.hpp
  
  Author: Paul Hamilton (paul@visualops.com)
  Date: 21-Jun-2024
    
  VIDs for Nodes.
  
  Licensed under [version 3 of the GNU General Public License] contained in LICENSE.
 
  https://github.com/visualopsholdings/nodes
*/

#ifndef H_vid
#define H_vid

#include <string>

using namespace std;

class VID {

public:
  VID(const string &vid);
  
  bool valid();
  string uuid() const { return _uuid; }
  string password() const { return _password; }
  void describe();
 
private:
  string _header;
  string _uuid;
  string _password;
    
};

#endif // H_vid
