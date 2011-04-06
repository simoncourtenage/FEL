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
  time_t timestamp;
public:
  ConnectMessage(std::string ia,int p) : ipaddr(ia), port(p) {}
  ConnectMessage(std::string contents);

  /** return the timestamp associated with this message - undefined if timestamp not set */
  time_t getTimestamp() const { return timestamp; }
  
  std::string getMessage() const;
  std::string getIPAddress() const { return ipaddr; }
  int getPort() const { return port; }
};

}
