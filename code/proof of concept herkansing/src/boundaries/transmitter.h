//
// Created by smart on 11/19/2016.
//

#ifndef CODE_TRANSMITTER_H
#define CODE_TRANSMITTER_H

#include "../../../libs/hwlib/hwlib-due.hpp"
#include "../../../libs/rtos/rtos.hpp"

class Transmitter  : public rtos::task<> {
        /** Reference to a instance of a hwlib::target::d2_36kHz class **/
        hwlib::target::d2_36kHz &ir;
        /** An RTOS flag used to check if a command is received **/
        rtos::flag command_received;
        /** short to save the command in **/
        short command_bits;
        /** Rtos main loop that sends a short in binary form over IR using the d2_36khz pin **/
        void main();
    public:
        /**
         * \brief Constructor for the Transmitter
         * \param priority priority of the task
         * \param ir Reference to already instantiated d2_36khz class
         */
        Transmitter(
                int priority,
                hwlib::target::d2_36kHz &ir) : task(priority, "Transmitter task"), ir(ir), command_received(this, "transmit-flag") {

        }

        /**
         * \brief Send given short in binary msb over IR
         *
         * Uses the defined protocol of the project
         * It sends a 0 by sending for 800us and silent for 1600us
         *
         * It sends a 1 by sending for 1600us and silent for 800us
         *
         * The command is sent twice in a delay of 3ms
         *
         * The starbit is a simple 1
         *
         * \param bits The short that will be send by binary MSB over ir
         */
        void send(short bits);

};
#endif //CODE_TRANSMITTER_H
