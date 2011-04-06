#include "connectMessage.h"
#include <sstream>

using namespace fel;

std::string ConnectMessage::getMessage()
{
  std::stringstream outstr;
  outstr << port;
  std::string sep = Message::getFieldSeparator();
  std::string str("");
  str += Message::getMessageHeader(Message::CONN);
  str += sep;
  str += ipaddr;
  str += sep;
  str += outstr.str();
  str += Message::getMessageEnd();
  return str;
}
