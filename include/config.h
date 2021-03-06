/*
 * File:   config.h
 * Author: Simon Courtenage <courtes at wmin.ac.uk>
 *
 * Created on 29 March 2011, 16:36
 */

#ifndef _CONFIG_H
#define	_CONFIG_H

#include <boost/program_options.hpp>

namespace po = boost::program_options;

namespace fel {

class Config {
private:
  po::variables_map vars;
  po::options_description options;
  static Config* instance_;
  /** creates a config object, reading from a default config file */
  Config(int,char**);
public:
  static Config* getInstance()
  {
    if (instance_ == (Config*)0) {
      instance_ = new Config(0,0);
    }
    return instance_;
    
  }
  static void init(int argc,char** argv)
  {
    if (instance_ == (Config*)0) {
      instance_ = new Config(argc,argv);
    }
  }

  static int verbose() {
    Config* instance = Config::getInstance();
    int verbosity = instance->get<int>("verbosity");
    return verbosity;
  }
  
    // object member functions
  template <typename T> T get(const std::string& name) const {
    if (vars.count(name) > 0) {
      return vars[name.c_str()].as<T>();
    }
    else {
      return T();
    }
  }
};

}

#endif	/* _CONFIG_H */

