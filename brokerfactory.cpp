#include "brokerfactory.h"
#include <stdexcept>
#include <string>

using namespace fel;

BrokerFactoryPtr BrokerFactory::getFactory()
{
  Config* config = Config::getInstance();
  std::string btype = config->get<std::string>("brokertype");

  if (btype == "simple") {
    return BrokerFactoryPtr(new SimpleBrokerFactory());
  }
  else {
    throw std::runtime_error("Unknown broker factory type");
  }
}
