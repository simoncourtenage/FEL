/*
 * File:   broker.h
 * Author: Simon Courtenage <courtes at wmin.ac.uk>
 *
 * Created on 29 March 2011, 13:48
 */

#ifndef _BROKER_H
#define	_BROKER_H

#include <string>

namespace fel {

class Broker {
private:
    int myport;
    std::string neighbour_ipaddr;
    int neighbour_port;

    Broker(); /** default constructor - not implemented */
public:
    /**
     * Brokers are started with their server port number, as well as
     * the IP address and port of another broker.
     */
    Broker(int myp, std::string ipaddr,int port)
            : myport(myp), neighbour_ipaddr(ipaddr), neighbour_port(port)
            { run(); }
    /**
     * run: starts a broker as a server process
     */
    void run();
};

}

#endif	/* _BROKER_H */

