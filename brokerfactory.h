/*
 * File:   brokerfactory.h
 * Author: Simon Courtenage <courtes at wmin.ac.uk>
 *
 * Created on 29 March 2011, 16:33
 */

#ifndef _BROKERFACTORY_H
#define	_BROKERFACTORY_H

#include "brokerconfig.h"
#include <boost/shared_ptr.hpp>

class BrokerFactory {
public:
  static BrokerFactoryPtr getFactory();
    virtual BrokerPtr getBroker(BrokerConfigPtr& ptr) = 0;
    virtual BrokerConfigPtr getBrokerConfig() = 0;
};

typdef boost::shared_ptr<BrokerFactory> FactoryPtr

class SimpleBrokerFactory : public BrokerFactory {
public:
  BrokerPtr getBroker(BrokerConfigPtr& ptr)
  {
    return BrokerPtr(new SimpleBroker(ptr->getIpAddress(),ptr->getPort(),ptr->getNeighbours()));
  }
};

#endif	/* _BROKERFACTORY_H */

