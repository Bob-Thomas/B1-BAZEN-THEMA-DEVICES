//
// Created by endargon on 10/25/16.
//

#include "../../libs/hwlib/hwlib.hpp"
#include "tasks/transmitter.h"
#include "tasks/receiver.h"
#include "tasks/initGameController.h"
#include "tasks/registerController.h"

enum States {
    INIT, REGISTER, RUNNING, GAME_END
};

#if GAMEMODE == PLAYER
States current_state = REGISTER;
#else
States current_state = INIT;
#endif

class Main : public rtos::task<> {
    Receiver &receiver;
    InitGameController &init_controller;
    RegisterController &register_controller;

    void main() {
        for (; ;) {
            receiver.enable();
            switch (current_state) {
                case INIT:
                    if (receiver.get_controller()->get_name() != init_controller.get_name()) {
                        receiver.set_controller(&init_controller);
                    }
                    init_controller.enable();
                    break;
                case REGISTER:
                    if (receiver.get_controller()->get_name() != register_controller.get_name()) {
                        receiver.set_controller(&register_controller);
                    }
                    register_controller.enable();
                    break;
                case RUNNING:
                    break;
                case GAME_END:
                    break;
            }
            sleep(1);
        }
    }

public:
    Main(Receiver &r, InitGameController &i, RegisterController &reg) : task("Main"), receiver(r), init_controller(i),
                                                                        register_controller(reg) { }
};

int main() {
#if GAMEMODE == PLAYER
    hwlib::cout << "Player";
#else
    hwlib::cout << "Leader";
#endif

    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    // wait for the PC console to start
    hwlib::wait_ms(1000);

    hwlib::cout << "timer demo\n";

    namespace target = hwlib::target;
    auto ir = target::d2_36kHz();
//    auto shoot_button = target::pin_in( target::pins::d3 );
    auto tsop_signal = target::pin_in(target::pins::d8);
    auto tsop_gnd = target::pin_out(target::pins::d9);
    auto tsop_vdd = target::pin_out(target::pins::d10);
    tsop_gnd.set(0);
    tsop_vdd.set(1);

    auto transmitter = Transmitter("transmitter", ir);
    auto init_game_controller = InitGameController();
    auto register_controller = RegisterController();
    auto receiver = Receiver("receiver", tsop_signal, &init_game_controller);
    auto main = Main(receiver, init_game_controller, register_controller);
    rtos::run();
}