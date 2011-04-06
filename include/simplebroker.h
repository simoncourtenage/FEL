/*
 * File:   broker.h
 * Author: Simon Courtenage <courtes at wmin.ac.uk>
 *
 * Created on 29 March 2011, 13:48
 */

#ifndef _SIMPLEBROKER_H
#define	_SIMPLEBROKER_H

#include <vector>
#include <sstream>
#include <map>
#include <string>
#include <ctime>
#include "broker.h"

namespace fel {

class SimpleBroker : public Broker {
private:
    std::string myip;
    int myport;
    std::vector<Neighbour> neighbours;

    std::map<std::string,time_t> lastBrokerMessages;

    std::string neighbour2String(const Neighbour& n)
      {
	std::stringstream sbuf;
	sbuf << n.port;
	std::string nstr = n.ip_addr;
	nstr += ":";
	nstr += sbuf.str();
	return nstr;
      }

    void updateBrokerMessages(const Neighbour& n,const time_t& t)
    {
      std::string n_id = neighbour2String(n);
      lastBrokerMessages[n_id] = t;
    }

    void parseNeighbours(std::vector<Neighbour>& ns,const std::string& nodes);

    SimpleBroker(); /** default constructor - not implemented */
    /** assignment operator - not implemented */
    SimpleBroker& operator=(const SimpleBroker&);
    /**
     * connects to neighbours to exchange address information
     */
    void init();
    void execute(int fd); /** deal with incoming messages */
public:
    /**
     * SimpleBrokers are started with their server port number, as well as
     * the IP address and port of another broker.
     * @nodes - a string containing a comma-separated list of ip addresses
     * and port numbers in the format IPADDRESS:PORT of neighouring nodes
     */
  SimpleBroker(const std::string& ip,int myp, const std::string& nodes)
    : myip(ip), myport(myp)
    {
      parseNeighbours(neighbours,nodes);
      init();
      run();
    }
    /**
     * run: starts a broker as a server process
     */
    void run();
};

}

#endif	/* _BROKER_H */

