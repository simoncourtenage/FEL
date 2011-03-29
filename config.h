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

class Config {
private:
    po::variables_map;

    static Config* instance_;
    /** creates a config object, reading from a default config file */
    Config();
public:
        static Config* getInstance()
    {
        if (instance_ == (Config*)0) {
            instance_ = new Config();
        }
        return instance_;

    }
};

Config* Config::instance_ = (Config*)0;

#endif	/* _CONFIG_H */

