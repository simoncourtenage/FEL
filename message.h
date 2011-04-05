/*
 * File:   message.h
 * Author: Simon Courtenage <courtes at wmin.ac.uk>
 *
 * Created on 29 March 2011, 14:07
 */

#ifndef _MESSAGE_H
#define	_MESSAGE_H

#include <boost/shared_ptr.hpp>

namespace fel {

class Message {
public:
  Message() {}
  virtual std::string getMessage() = 0;

  enum MSGTYPE { CONN };

  
  static std::string getFieldSeparator()
  { return string(":"); }
  static std::string getMessageEnd()
  { return ""; }
  static std::string getMessageHeader(MSGTYPE type)
  {
    switch (type) {
    case CONN: return "CONN"; break;
    default: return "";
    }
  }
  
};
 
typedef boost::shared_ptr<Message> MessagePtr;
 
}

#endif	/* _MESSAGE_H */

