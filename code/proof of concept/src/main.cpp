//
// Created by endargon on 10/25/16.
//

#include "../../libs/hwlib/hwlib.hpp"
#include "tasks/transmitter.h"
#include "tasks/receiver.h"
#include "tasks/initGameController.h"
#include "tasks/registerController.h"
#include "tasks/displayController.h"
#include "entities/gameParameters.h"
#include "tasks/runGameController.h"

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
    RunGameController &run_game_controller;
    void main() {
        for (; ;) {
            receiver.enable();
            switch (current_state) {
                case INIT:

                    if (receiver.get_controller()->get_name() != init_controller.get_name()) {
                        receiver.suspend();
                        receiver.set_controller(&init_controller);
                        receiver.resume();
                        init_controller.resume();
                        register_controller.suspend();
                        run_game_controller.suspend();
                    }
                    init_controller.enable();
                    break;
                case REGISTER:

                    if (receiver.get_controller()->get_name() != register_controller.get_name()) {
                        receiver.suspend();
                        receiver.set_controller(&register_controller);
                        receiver.resume();
                        init_controller.suspend();
                        register_controller.resume();
                        run_game_controller.suspend();
                    }
                    register_controller.enable();

                    break;
                case RUNNING:

                    if (receiver.get_controller()->get_name() != run_game_controller.get_name()) {
                        receiver.suspend();
                        receiver.set_controller(&run_game_controller);
                        receiver.resume();
                        init_controller.suspend();
                        register_controller.suspend();
                        run_game_controller.resume();
                    }

                    run_game_controller.enable();
                    break;
                case GAME_END:
                    break;
            }
            sleep(1);
        }
    }

public:
    Main(Receiver &r, InitGameController &i, RegisterController &reg, RunGameController &run) : task("Main"), receiver(r), init_controller(i),
                                                                        register_controller(reg), run_game_controller(run) { }
};

int main() {


    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    // wait for the PC console to start
    hwlib::wait_ms(1000);
#if GAMEMODE == PLAYER
    hwlib::cout << "Player";
#else
    hwlib::cout << "Leader";
#endif
    hwlib::cout << "timer demo\n";

    namespace target = hwlib::target;
    auto ir = target::d2_36kHz();
//    auto shoot_button = target::pin_in( target::pins::d3 );
    auto tsop_signal = target::pin_in(target::pins::d8);
    auto tsop_gnd = target::pin_out(target::pins::d9);
    auto tsop_vdd = target::pin_out(target::pins::d10);
    tsop_gnd.set(0);
    tsop_vdd.set(1);

    // keypad
    auto out0 = target::pin_oc( target::pins::a0 );
    auto out1 = target::pin_oc( target::pins::a1 );
    auto out2 = target::pin_oc( target::pins::a2 );
    auto out3 = target::pin_oc( target::pins::a3 );
    auto out_port = hwlib::port_oc_from_pins( out0, out1, out2, out3 );
    auto in0 = target::pin_in( target::pins::a4 );
    auto in1 = target::pin_in( target::pins::a5 );
    auto in2 = target::pin_in( target::pins::a6 );
    auto in3 = target::pin_in( target::pins::a7 );
    auto in_port = hwlib::port_in_from_pins( in0, in1, in2, in3 );
    auto matrix = hwlib::matrix_of_switches( out_port, in_port );
    auto keypad = hwlib::keypad< 16 >( matrix, "123A456B789C*0#D" );

    // oled
    namespace target = hwlib::target;
    auto scl = target::pin_oc( target::pins::scl );
    auto sda = target::pin_oc( target::pins::sda );
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( sda, scl );
    auto pin_gnd = target::pin_out( target::pins::d19 );
    pin_gnd.set( 0 );
    auto pin_vcc = target::pin_out( target::pins::d18 );
    pin_vcc.set( 1 );
    auto oled = hwlib::glcd_oled_buffered( i2c_bus, 0x3c );

    // entities
    auto game_parameter = GameParameters();
    auto transmitter = Transmitter("transmitter", ir);
    auto display_controller = DisplayController(oled);
    auto init_game_controller = InitGameController(transmitter, keypad, display_controller);
    auto register_controller = RegisterController(display_controller);
    auto run_game_controller = RunGameController(game_parameter, display_controller);
    auto receiver = Receiver("receiver", tsop_signal, &init_game_controller);

    auto main = Main(receiver, init_game_controller, register_controller, run_game_controller);
    rtos::run();
}