#include "connectMessage.h"

std::string getMessage()
{
  str sep = Message::getFieldSeparator();
  string str("");
  str += Message::getMessageHeader(Message::CONN);
  str += sep;
  str += ipaddr;
  str += sep;
  str += itoa(port);
  str += Message::getMessageEnd();
}
