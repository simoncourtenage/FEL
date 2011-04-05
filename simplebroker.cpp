#include "simplebroker.h"
#include "brokerfactory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <iostream>

#ifdef DEBUG
#include <boost/program_options.hpp>
#endif

using namespace fel;


void error(const char* msg)
{
    perror(msg);
    exit(1);
}

/**
 * send connection messages to neighbouring nodes
 */
void SimpleBroker::init()
{
  MessagePtr msgptr(new ConnectionMessage(myip,myport));
  vector<Neighbour>::iterator vi;
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
    std::cout << buffer << std::endl;

}

#ifdef DEBUG

int main(int argc,char**argv)
{
    BrokerFactory* factory = Config::getBrokerFactory();
    BrokerConfig* brokerconfig = factory->getBrokerConfig(argc,argv);
    Broker* broker = factory->getBroker(brokerconfig)
}

#endif
