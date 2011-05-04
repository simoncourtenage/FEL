#include "broker.h"

using namespace fel;

void Broker::send(MessagePtr msg,const BrokerAddressPtr& n)
{
  n->send(msg);
}
