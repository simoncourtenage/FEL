/*
 * File:   message.h
 * Author: Simon Courtenage <courtes at wmin.ac.uk>
 *
 * Created on 29 March 2011, 14:07
 */

#ifndef _MESSAGE_H
#define	_MESSAGE_H

namespace fel {

class Message {
private:
    std::string data;
public:
    Message(std::string d) : data(d) {}
    std::string getcontents() { return data; }
};


}

#endif	/* _MESSAGE_H */

