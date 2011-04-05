#include "broker.h"

void Broker::send(MessagePtr msg,const Neighbour& n)
{
  std::string ip = n.ip_addr;
  int port = n.port;

  struct sockaddr_in serv_addr;
  int sockfd;

  bzero((char*) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_sddr = inet_addr();
  serv_addr.sin_port = htons();

  if ((sockfd = socket(AF_INET, SOCK_STREAM,0)) < 0) {
    throw new exception("can't open client connection");
  }
  if (connect(sockfd,(struct sockaddr*) & serv_addr, sizeof(serv_addr)) < 0) {
    throw new exception("can't connect to broker neighbour");
  }

  // write bytes to socket...
}
