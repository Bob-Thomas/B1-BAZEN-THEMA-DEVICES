//
// Created by endargon on 10/25/16.
//

#ifndef B1_BAZEN_THEMA_DEVICES_RECEIVER_H
#define B1_BAZEN_THEMA_DEVICES_RECEIVER_H

#include "../../../libs/rtos/rtos.hpp"
#include "../../../libs/hwlib/hwlib.hpp"
#include "controller.h"

/**
 * \class Receiver
 * \brief Class that handles receiving IR handling
 */
class Receiver : public rtos::task<> {
        /** \brief Pin that receives the ir pulses **/
        hwlib::pin_in &signal;
        /** \brief Reference to a abstract controller class **/
        Controller *controller;
        /** \brief RTOS flag to check if the receiver is enabled **/
        rtos::flag enabled;
        /** \brief Buffer for the last received command **/
        Command last_command;
        /** \brief Buffer to keep track on how many bits we've counted for command **/
        int amount_bits_found = 0;
        /** \brief Maximum size of the command bits **/
        const int max_bits = 16;
        /** \brief a short in which the received bits will be shifted into **/
        short bits;


        /**
         * \brief RTOS main loop that if enabled will listen for signals
         * If a command is received twice successfully it will call the current controller it's Received method with as parameter the received command
         */
        void main();

    public:
        /**
         * \brief Constructor for the Receiver class
         * \param name Task name
         * \param signal Pin that's used to received to signals
         * \param controler Reference to a abstract class controller
         */
        Receiver(const char *name, hwlib::pin_in &signal, Controller *controller)
                : task( (unsigned int) 0, name), signal(signal), controller(controller), enabled(this, "receiver-enabled"){ }

        /**
         * \brief sets the enable flag
         */
        void enable() {
            enabled.set();
        }
        /**
         * \brief swaps out the controller that the receiver talks to
         */
        void set_controller(Controller *c) {
            this->controller = c;
        }

        /**
         * \brief returns the controller that the receiver is talking to
         */
        Controller *get_controller() {
            return controller;
        }

        void idle();

        void signal_found();
};

#endif //B1_BAZEN_THEMA_DEVICES_RECEIVER_H
//1 10000 00100 10100
//1 00010 00110