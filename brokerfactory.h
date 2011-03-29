/*
 * File:   brokerfactory.h
 * Author: Simon Courtenage <courtes at wmin.ac.uk>
 *
 * Created on 29 March 2011, 16:33
 */

#ifndef _BROKERFACTORY_H
#define	_BROKERFACTORY_H

#include "config.h"

class BrokerFactory {
public:
    static BrokerFactory* getFactory(Config& c) = 0;
    virtual Broker* getBroker(const BrokerConfig*) = 0;
    virtual BrokerConfig* getBrokerConfig(int,char**);
};


#endif	/* _BROKERFACTORY_H */

