//
// Created by endargon on 10/26/16.
//

#include "initGameController.h"

InitGameController::InitGameController(Transmitter &transmitter, hwlib::keypad<16> &keypad, DisplayController &displayCtrl)
        : task("Init_Controller"), transmitter(transmitter), keypad(keypad), displayCtrl(displayCtrl), enabled(this, "init-enabled"), command_available(this, "command-available"), command_full(0) { }

void InitGameController::main() {

    for(;;) {

        wait(enabled);
        char txt[] = "Press A to \n insert player. \n \n \n \nPress C to \n insert command. \n";

        // default screen
        displayCtrl.displayText(txt);

        auto c = keypad.getc();

        if(c == 'A') {
            char txt_1[15] = "Type id: \n\n\n";
            displayCtrl.displayText(txt_1);

            // getting first character
            auto first = keypad.getc();
            txt_1[12] = first;
            txt_1[13] = '\0';
            displayCtrl.displayText(txt_1);

            // getting second character
            auto second = keypad.getc();
            txt_1[13] = second;
            txt_1[14] = '\0';
            displayCtrl.displayText(txt_1);

            // check if the id is valid
            auto valid = valid_id(first, second);

            // when valid is alright
            if(valid != 0) {

                // assign to player id
                player_id = valid;

                // asking for weapon
                displayCtrl.displayText("Press B to \n Select weapon.");

                auto c = keypad.getc();

                // weapon select
                if(c == 'B') {

                    displayCtrl.displayText("Weapons: \n 1.Power Beam \n 2.Sonic Beam \n 3.Laser Beam \n");
                    auto c = keypad.getc();

                    // player selected weapon
                    while(c != '1' && c!= '2' && c!= '3' && c!='A') {

                        // listen again for keypad input
                        c = keypad.getc();
                    }

                    if(c != 'A') {

                        weapon_id = atoi(&c);

                        hwlib::cout << "TEST CASE PLAYER ID:" << player_id << "\n TEST CASE WEAPON ID " << weapon_id << "\n";
                        displayCtrl.displayText("Press * to \n send data.");
                        c = keypad.getc();

                        if(c =='*') {
                            displayCtrl.displayText("Sending data..");
                            Command c(player_id, weapon_id);
                            c.print_command();
                            transmitter.send(c.encode());
                            keypad.getc();
                        }
                    }


                }

                // player can select id again...

            } else {
                displayCtrl.displayText("incorrect id.");
            }

        }

        if(c == 'C') {
            hwlib::cout << "im here";
            int counter = 1;
            custom_command = 0;
            custom_command |= 1 << 15;
            char first_screen_command[] = "1.........xxxxx";
            displayCtrl.displayText(first_screen_command);

            while(counter < 16){

                char c = keypad.getc();
                if(c == '1' || c == '0' ) {
                    first_screen_command[counter] = c;
                    if(c == '1') {
                        custom_command |= (1 << (15-counter));
                    }
                    displayCtrl.displayText(first_screen_command);
                    counter++;
                } else{
                    command_full = 0;
                    break;
                }

            }

            if(counter == 16) {
                displayCtrl.displayText("Press # \nany time \nto send  \ncommand. \nPress any \nkey to \ncontinue.");
                command_full = '1';
            }

        }
        if(c == '#') {

            if(command_full == '1') {
                displayCtrl.displayText("send last \ninserted command");
                transmitter.send(custom_command);
            } else {
                displayCtrl.displayText("Incorrect  \nCommand");
            }
        }


        hwlib::cout << c;
    }

    /*
    rtos::timer timer(this);
    Command test(2, 6);
    test.print_command();
    timer.set(1000);
    for (; ;) {
        wait(enabled);
        wait(timer);
        transmitter.send(test.encode());
        timer.set(1000);
    }
    */
}

// id validator
int InitGameController::valid_id(char first, char second) {

    // check if the chars are numbers
    if(first >= '0'&& first <= '9' && second >= '0' && second <= '9') {
        char txt_id[2];
        txt_id[0] = first;
        txt_id[1] = second;
        int id = atoi(txt_id);

        if(id > 0 && id < 32) {
            return id;
        }

        return 0;
    }

    return 0;
}

void InitGameController::receive(Command c) {
    command = c;
    command_available.set();
    hwlib::cout << HERE << " RECEIVED << " << c.get_sender() << "\n";
}

void InitGameController::enable() {
    enabled.set();
}