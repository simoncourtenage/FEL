/*
 * File:   message.h
 * Author: Simon Courtenage <courtes at wmin.ac.uk>
 *
 * Created on 29 March 2011, 14:07
 */

#ifndef _MESSAGE_H
#define	_MESSAGE_H
#include <string>
#include <boost/shared_ptr.hpp>
#include <ctime>

namespace fel {

class Message {
public:
  Message() {}
  virtual std::string getMessage() const  = 0;

  enum MSGTYPE { CONN };

  virtual time_t getTimestamp() const = 0;
  
  static std::string getFieldSeparator()
  { return ":"; }
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

