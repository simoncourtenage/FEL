/*
 * File:   brokerfactory.h
 * Author: Simon Courtenage <courtes at wmin.ac.uk>
 *
 * Created on 29 March 2011, 16:33
 */

#ifndef _BROKERFACTORY_H
#define	_BROKERFACTORY_H

#include "broker.h"
#include "simplebroker.h"
#include "config.h"
#include <boost/shared_ptr.hpp>

namespace fel {

class BrokerFactory {
public:
  static boost::shared_ptr<BrokerFactory> getFactory();
  virtual BrokerPtr getBroker() = 0;
};

typedef boost::shared_ptr<BrokerFactory> BrokerFactoryPtr;

class SimpleBrokerFactory : public BrokerFactory {
public:
  BrokerPtr getBroker()
  {
    Config* config = Config::getInstance();
    std::string ip = config->get<std::string>("ipaddress");
    int port = config->get<int>("port");
    std::string neighbours = config->get<std::string>("neighbours");
    return BrokerPtr(new SimpleBroker(ip,port,neighbours));
  }
};

}

#endif	/* _BROKERFACTORY_H */

