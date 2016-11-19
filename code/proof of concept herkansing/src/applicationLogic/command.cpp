//
// Created by endargon on 10/26/16.
//

#include "command.h"

Command::Command(int sender, int data) : sender(sender), data(data) {
    if (sender >= 31) {
        hwlib::cout << "Player range exceeded\n";
    } else if (sender < 0) {
        hwlib::cout << "Player not in range\n";
    }
    if (data >= 31) {
        hwlib::cout << "Data range exceeded\n";
    } else if (data < 0) {
        hwlib::cout << "Data not in range\n";
    }
}

Command::Command() : sender(-1), data(-1) { }

bool Command::valid_checksum(short bits) {
    for (int i = 1; i <= 5; i++) {
        bool current_bit = bits & (1 << i);
        bool check_bit = bits & (1 << (i+5));
        bool control_bit = bits & (1 << (i+10));
        bool xor_bit = current_bit ^ check_bit;
        hwlib::cout << "\n" << ((current_bit) ? "1" : "0") << ((check_bit) ? "1" : "0") << " ^ " << ((xor_bit) ? "1" : "0") << " = " << ((control_bit) ? "1" : "0") << "\n";
        if (control_bit != xor_bit) {
            return false;
        }
    }
    return true;
}

short Command::encode() {
    short bits = 0;
    bits |= 1 << 15;//add startbit

    //Convert id to  short and place it on position 1-5
    short id_bits = sender << 10;
    bits = bits | id_bits;

    //Convert data to  short and place it on position 5-10
    short data_bits = data << 5;
    bits = bits | data_bits;
    for (int i = 1; i <= 5; i++) {
        short checksum = ((bits >> (15 - i)) & 1) ^((bits >> (15 - (i + 5))) & 1);
        checksum = checksum << (5 - i);
        bits = bits | checksum;
    }
    //add new bits
#if RTOS_STATISTICS_ENABLED

    hwlib::cout << "checksumed data " << bits << "\n";
#endif

    return bits;
}

void Command::decode(short bits) {
    bool start_bit = bits & (1 << 0);
    if (!start_bit) {
#if RTOS_STATISTICS_ENABLED

        hwlib::cout << HERE << " Starbit not correct\n";
#endif

        error = true;
    }
    if (!valid_checksum(bits)) {
        error = true;
#if RTOS_STATISTICS_ENABLED
        hwlib::cout << HERE << " Checksum not correct\n";
#endif
    }
    if (!error) {
        //retrieve id
        int i = 0;
        sender = 0;
        data = 0;
        for (i = 1; i <= 5; i++) {
            sender = sender | ((bits >> (16 - i)) & 1);
            if (i < 5) {
                sender = sender << 1;
            }
        }
        for (i = 6; i <= 10; i++) {
            data = data | ((bits >> (16 - i)) & 1);
            if (i < 10) {
                data = data << 1;
            }
        }

    }
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

bool Command::get_error() {
    return error;
}

void Command::print_command() {
    short encoded = encode();
    hwlib::cout << HERE << "\n \t--" << "decoded " << sender << " | " << data << " Encoded: ";
    for (int i = 0; i < 16; i++) {
        hwlib::cout << ((encoded >> (15 - i)) & 1);

    }
    hwlib::cout << "\n";
}