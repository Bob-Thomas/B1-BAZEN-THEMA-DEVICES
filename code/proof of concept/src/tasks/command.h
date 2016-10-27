//
// Created by endargon on 10/26/16.
//

#ifndef CODE_COMMAND_H
#define CODE_COMMAND_H
#include "../../../libs/hwlib/hwlib.hpp"
#include "../../../libs/rtos/rtos.hpp"

class Command {
    int sender;
    int data;
    bool error = false;

    void decode(short bits);

    short generate_checksum(short bits);

    bool valid_checksum(short bits);;

public:
    void print_command() {
        char bits[16];
        short encoded = encode();
        for(int i = 0; i < 16; i++) {
            bool bit = ((encoded >> (15-i))&1);
            (bit) ? bits[i] = '1' : bits[i] = '0';
        }
        hwlib::cout << HERE << "\n \t--" << "decoded " << sender << " | " << data << " Encoded: " << bits;
    }
    short encode();

    bool get_error();

    int get_sender();

    void set_sender(int sender);

    int get_data();

    void set_data(int data);

    Command();

    Command(unsigned int bits) {
        decode(bits);
    }

    Command(int sender, int data);
};

#endif //CODE_COMMAND_H
