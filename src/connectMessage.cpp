#include "connectMessage.h"
#include <sstream>
#include <stdexcept>

#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp> // used to parse message contents
#include <time.h>

using namespace fel;
using namespace boost;

/**
 * reconstruct connect message object from string
 */
ConnectMessage::ConnectMessage(std::string contents)
{
  char_separator<char> sep(":"); // message field separator
  tokenizer<char_separator<char> > tokens(contents,sep);
  tokenizer<char_separator<char> >::iterator tokptr = tokens.begin();
  std::string ip;
  struct tm tm_time;
  time_t msgtime;
  int prt;
  if (tokptr != tokens.end()) {
    if ((*tokptr) != "CONN") {
      throw std::runtime_error("Bad connection message");
    }
    tokptr++;
  }
  if (tokptr != tokens.end()) {
    std::string asciitime = (*tokptr);
    strptime(asciitime.c_str(),"%Y-%m-%d-%H-%M-%S",&tm_time);
    msgtime = mktime(&tm_time);
    tokptr++;
  }
  else {
    throw std::runtime_error("Bad connection message");
  }
  if (tokptr != tokens.end()) {
    ip = (*tokptr);
    tokptr++;
  }
  else {
    throw std::runtime_error("Bad connection message");
  }
  if (tokptr != tokens.end()) {
    std::string portstr = (*tokptr);
    prt = atoi(portstr.c_str());
  }
  else {
    throw std::runtime_error("Bad connection message");
  }
  // set the two object attributes to the values read from the message contents
  ipaddr = ip;
  port = prt;
  timestamp = msgtime;
}

std::string ConnectMessage::getMessage() const
{
  std::stringstream outstr;
  outstr << port;
  std::string sep = Message::getFieldSeparator();
  std::string str("");
  str += Message::getMessageHeader(Message::CONN);
  str += sep;
  // timestamp the message
  time_t thistime;
  time(&thistime);
  struct tm* this_tm_ptr = localtime(&thistime);
  char buffer[80];
  if (!strftime(buffer,21,"%Y-%m-%d-%H-%M-%S",this_tm_ptr)) {
    throw std::runtime_error("Unable to construct timestamp");
  }
  str += buffer;
  str += sep;
  str += ipaddr;
  str += sep;
  str += outstr.str();
  str += Message::getMessageEnd();
  return str;
}

