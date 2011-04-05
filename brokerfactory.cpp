#include "brokerfactory.h"
#include <stdexcept>

using namespace fel;

static BrokerFactoryPtr BrokerFactory::getFactory()
{
  Config& config = Config::getInstance();
  BrokerType btype = config.getBrokerType();

  switch (btype) {
  case SIMPLE:
    return BrokerFactoryPtr(new SimpleBrokerFactory()); break;
  default:
    throw std::runtime_error("Unknown broker factory type");
  }
}
