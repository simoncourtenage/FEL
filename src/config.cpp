#include "config.h"
#include <stdexcept>
#include <fstream>

#ifdef DEBUGCFG
#include <iostream>
#endif

using namespace fel;

Config* Config::instance_ = (Config*)0;


Config::Config(int argc,char** argv)
{
  options.add_options()
    ("ipaddress",po::value<std::string>(),"broker's ip address")
    ("port",po::value<int>(),"broker port")
    ("neighbours",po::value<std::string>(),"neighbour nodes")
    ("brokertype",po::value<std::string>(),"select broker type");

  po::store(po::parse_command_line(argc,argv,options),vars);
  po::notify(vars);
  std::string fopt("cfg");
  // need to supply template argument value on call to get
  std::string configfilename = get<std::string>(fopt);
  if (configfilename.size() < 1) {
    configfilename = "./fel.cfg";
  }
  std::ifstream fs(configfilename.c_str());
  if (!fs) {
    throw std::runtime_error("unable to find config file");
  }
  po::store(po::parse_config_file(fs,options,true),vars);
  po::notify(vars);
}

#ifdef DEBUGCFG
int main(int argc,char** argv)
{
  Config::init(argc,argv);
  std::cerr << "Done init" << std::endl;
  Config* cfg = Config::getInstance();
  if (!cfg) {
    std::cerr << "No config pointer" << std::endl;
  }
  std::cout << cfg->get<std::string>("brokertype") << std::endl;
}
#endif
