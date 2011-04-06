#include "header.h"
#include "simplebroker.h"
#include "brokerfactory.h"
#include "connectMessage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <iostream>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp> // used to parse neighbour information

#ifdef DEBUG
#include <boost/program_options.hpp>
#endif

using namespace fel;
using namespace boost;

void error(const char* msg)
{
    perror(msg);
    exit(1);
}

/**
 * parse the string containing information about ip addresses and ports of
 * neighbouring nodes
 */
void SimpleBroker::parseNeighbours(std::vector<Neighbour>& ns,const std::string& nodes)
{
  char_separator<char> sep(",");
  tokenizer<char_separator<char> > tokens(nodes,sep);
  BOOST_FOREACH(std::string n,tokens)
    {
      std::string::size_type pos = n.find_first_of(":");
      if (pos == 0 || pos == std::string::npos) {
	throw std::runtime_error("bad neighbour node info");
      }
      std::string ip = n.substr(0,pos);
      int port = atoi(n.substr(pos+1,std::string::npos).c_str());
      Neighbour neighbour;
      neighbour.ip_addr = ip;
      neighbour.port = port;
      ns.push_back(neighbour);
    }
}
/**
 * send connection messages to neighbouring nodes
 */
void SimpleBroker::init()
{
  MessagePtr msgptr(new ConnectMessage(myip,myport));
  std::vector<Neighbour>::iterator vi;
  for (vi = neighbours.begin();vi != neighbours.end(); vi++) {
    send(msgptr,(*vi));
  }
}

/**
 * start listening as server on given port
 */
void SimpleBroker::run()
{
    int sockfd, newsockfd, pid;
    struct sockaddr_in serv_addr,cli_addr;
    socklen_t clilen;

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if (sockfd < 0) {
        error("Can't open socket");
    }
    bzero((char*)&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(myport);
    if (bind(sockfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0) {
        error("Error on bind");
    }
    listen(sockfd,5);
    while (1) {
        newsockfd = accept(sockfd,(struct sockaddr*) & cli_addr,&clilen);
        if (newsockfd < 0) {
            error("error on accept");
        }
        pid = fork();
        if (pid < 0) {
            error("error on fork");
        }
        if (pid == 0) {
            close (sockfd);
            execute(newsockfd);
            exit(0);
        }
        else {
            close(newsockfd);
        }
    }
    close(sockfd);
    return;
}

void SimpleBroker::execute(int fd)
{
    int n;
    char buffer[256];
    bzero(buffer,256);
    n = read(fd,buffer,255);
    std::string msg(buffer);
    std::string::size_type pos = msg.find_first_of(":");
    if (pos == 0 || pos == std::string::npos) {
      throw std::runtime_error("bad message received");
    }
    std::string msgtype = msg.substr(0,pos);
    if (msgtype == "CONN") {
      // connect message received from neighbour, so add to neighbours
      ConnectMessage connmsg(msg);
      time_t msgtime = connmsg.getTimestamp();
      Neighbour neighbour;
      updateBrokerMessages(neighbour,msgtime);
      neighbour.ip_addr = connmsg.getIPAddress();
      neighbour.port = connmsg.getPort();
      std::cerr << "Connect message received from "
		<< neighbour.ip_addr << ":" << neighbour.port
		<< " timestamped " << ctime(&msgtime) << std::endl;
      neighbours.push_back(neighbour);
    }
}



