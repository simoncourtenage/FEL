/*
 * File:   broker.h
 * Author: Simon Courtenage <courtes at wmin.ac.uk>
 *
 * Created on 29 March 2011, 16:29
 */

#ifndef _BROKER_H
#define	_BROKER_H

#include <string>
#include "message.h"
#include <boost/shared_ptr.hpp>

namespace fel {

class Broker {
public:
    virtual void run() = 0;

    typedef struct {
      std::string ip_addr;
      int port;
    } Neighbour;

    void send(MessagePtr msgptr,const Neighbour& neighbour);
};

 typedef boost::shared_ptr<Broker> BrokerPtr;

}

#endif	/* _BROKER_H */

