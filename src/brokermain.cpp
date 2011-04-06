#include "simplebroker.h"
#include "brokerfactory.h"
#include "config.h"

int main(int argc,char**argv)
{
  fel::Config::init(argc,argv);
  fel::BrokerFactoryPtr factory = fel::BrokerFactory::getFactory();
  fel::BrokerPtr broker = factory->getBroker();
  broker->run();
}
