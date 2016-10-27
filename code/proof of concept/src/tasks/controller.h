//
// Created by endargon on 10/26/16.
//

#ifndef CODE_CONTROLLER_H
#define CODE_CONTROLLER_H

#include "command.h"

class Controller {
public:
    Controller(){};
    virtual void receive(Command c) = 0;
    virtual void enable() = 0;
    virtual const char * get_name() = 0;
};

#endif //CODE_CONTROLLER_H
