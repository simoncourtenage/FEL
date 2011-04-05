#include "config.h"
#include <stdexcept>
#include <fstream>

Config::Config(int argc,char** argv)
{
  po::store(po::parse_command_line(argc,argv,options),vars);
  po::notify(vars);
  std::string fopt("cfg");
  std::string configfilename = instance_->get(fopt);
  if (configfilename.size() < 1) {
    configfilename = "fel.cfg";
  }
  std::ifstream fs(configfilename.c_str());
  if (!fs) {
    throw std::runtime_error("unable to find config file");
  }
  po::store(po::parse_config_file(fs,options,true),vars);
  po::notify(vars);
}
