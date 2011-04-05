/*
 * File:   broker.h
 * Author: Simon Courtenage <courtes at wmin.ac.uk>
 *
 * Created on 29 March 2011, 13:48
 */

#ifndef _BROKER_H
#define	_BROKER_H

#include <vector>
#include <string>

namespace fel {

class SimpleBroker : public Broker {
private:
    std::string myip;
    int myport;
    std::vector<Neighbour>& neighbours;

    SimpleBroker(); /** default constructor - not implemented */
    /** assignment operator - not implemented */
    SimpleBroker& operator=(const SimpleBroker&);
    void execute(int fd); /** deal with incoming messages */
public:
    /**
     * SimpleBrokers are started with their server port number, as well as
     * the IP address and port of another broker.
     */
  SimpleBroker(std::string ip,int myp, const std::vector<Neighbour>& ns)
    : myip(ip), myport(myp), neighbours(ns)
    {
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

