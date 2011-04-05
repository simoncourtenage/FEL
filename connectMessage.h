/**
 * Connect message
 * Author: Simon Courtenage, April 2011
 */

#include "message.h"
#include <string>

namespace fel {

/**
 * ConnectMessage is sent by a broker node to its direct neighbours
 * to announce its existence.  It contains the sending node's IP
 * address and port number.     
 */
class ConnectMessage : public Message {
private:
  std::string ipaddr;
  int port;
public:
  ConnectMessage(string ia,int p) : ipaddr(ia), port(p) {}
  std::string getMessage();
};

}