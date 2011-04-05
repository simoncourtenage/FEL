#include "broker.h"
#include <stdexcept>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>

using namespace fel;

void Broker::send(MessagePtr msg,const Neighbour& n)
{
  std::string ip = n.ip_addr;
  int port = n.port;

  struct sockaddr_in serv_addr;
  int sockfd;

  bzero((char*) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(n.ip_addr.c_str());
  serv_addr.sin_port = htons(n.port);

  if ((sockfd = socket(AF_INET, SOCK_STREAM,0)) < 0) {
    throw std::runtime_error("can't open client connection");
  }
  if (connect(sockfd,(struct sockaddr*) & serv_addr, sizeof(serv_addr)) < 0) {
    throw std::runtime_error("can't connect to broker neighbour");
  }

  // write bytes to socket...
  int nleft,nwritten,nbytes;
  std::string msgstr = msg->getMessage();
  const char* cptr = msgstr.c_str();
  nbytes = strlen(cptr);
  nleft = nbytes;

  while (nleft > 0) {
    nwritten = write(sockfd,cptr,nleft);
    if (nwritten < 0) {
      throw std::runtime_error("Message send failed");
    }
    nleft -= nwritten;
    cptr += nwritten;
  }
}
