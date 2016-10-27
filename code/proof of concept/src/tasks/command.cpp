//
// Created by endargon on 10/26/16.
//

#include "command.h"

char * Command::encode(int sender, int data) {
    return (char *) "1001010100";
}

void Command::decode(char bits[16]) {
    this->sender = 6;
    this->data = 7;
}


int Command::get_sender() {
    return sender;
}

void Command::set_sender(int sender) {
    this->sender = sender;
}

int Command::get_data() {
    return data;
}

void Command::set_data(int data) {
    this->data = data;
}