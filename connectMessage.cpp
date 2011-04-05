#include "connectMessage.h"

using namespace fel;

std::string getMessage()
{
  std::string sep = Message::getFieldSeparator();
  std::string str("");
  str += Message::getMessageHeader(Message::CONN);
  str += sep;
  str += ipaddr;
  str += sep;
  str += itoa(port);
  str += Message::getMessageEnd();
}
