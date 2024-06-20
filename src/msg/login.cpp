/*
  loginmsg.cpp
  
  Author: Paul Hamilton (paul@visualops.com)
  Date: 23-May-2024
  
  Licensed under [version 3 of the GNU General Public License] contained in LICENSE.
 
  https://github.com/visualopsholdings/zmqchat
*/

#include "server.hpp"

#include "storage.hpp"

#include <boost/log/trivial.hpp>

void Server::loginMsg(json &j, shared_ptr<Storage> storage) {

  string session;
  if (!getString(j, "session", &session)) {
    sendErr("no session");
    return;
  }
  string password;
  if (!getString(j, "password", &password)) {
    sendErr("no password");
    return;
  }
  
  auto user = User(*storage).find(json{ { "name", password } }, {"name", "fullname"}).value();
  if (!user) {
    sendErr("DB Error");
    return;
  }
  
  BOOST_LOG_TRIVIAL(trace) << user.value();
  
  string id;
  if (!getString(user, "id", &id)) {
    sendErr("User not found");
    return;
  }

  string name;
  if (!getString(user, "name", &name)) {
    sendErr("No name in user");
    return;
  }
  string fullname;
  if (!getString(user, "fullname", &fullname)) {
    sendErr("No fullname in user");
    return;
  }
  
  send({
    { "type", "user" },
    { "session", session },
    { "id", id },
    { "name", name },
    { "fullname", fullname }
  });

}