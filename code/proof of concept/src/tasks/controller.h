//
// Created by endargon on 10/26/16.
//

#ifndef CODE_CONTROLLER_H
#define CODE_CONTROLLER_H

#include "command.h"

/**
 * \class Controller class
 * \brief will be implented by each state
 */
class Controller {
public:

    /**
     * Controller Constructor
     */
    Controller(){};
    /**
     * virtual function for received data from the receiver
     */
    virtual void receive(Command c) = 0;
    /**
     * virtual function to enable the class function task
     */
    virtual void enable() = 0;

    /**
    * virtual function to use button_pressed function task
    */
    virtual void button_pressed() = 0;

    /**
     * virtual function for getting class name
     */
    virtual const char * get_name() = 0;
};

#endif //CODE_CONTROLLER_H
