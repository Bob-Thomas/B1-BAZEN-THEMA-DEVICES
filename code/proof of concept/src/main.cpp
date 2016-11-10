//
// Created by endargon on 10/25/16.
//


/*! \mainpage Laser tag
 * This is doxygen documentation for our school project named THEMA DEVICES.
 *
 * THEMA DEVICES is a group project about building a laser tag game with RTOS.
 * This is the proof of concept documentation.
 */

#include "../../libs/hwlib/hwlib.hpp"
#include "tasks/transmitter.h"
#include "tasks/receiver.h"
#include "tasks/initGameController.h"
#include "tasks/registerController.h"
#include "tasks/displayController.h"
#include "entities/gameParameters.h"
#include "tasks/runGameController.h"
#include "tasks/buttonController.h"
#include "tasks/soundController.h"

enum States {
    INIT, REGISTER, RUNNING, GAME_END
};

#if GAMEMODE == PLAYER
States current_state = REGISTER;
#else
States current_state = INIT;
#endif

/**
 * \class Main
 * \brief This class will resume and suspend running tasks based on it's current state
 */
class Main : public rtos::task<> {
    /**
     * Reference to a Receiver task
     */
    Receiver &receiver;
    /**
    * Reference to a ButtonController task
    */
    ButtonController &button_controller;
    /**
     * Reference to a InitController task
     */
    InitGameController &init_controller;
    /**
     * Reference to a RegisterController task
     */
    RegisterController &register_controller;
    /**
    * Reference to a RunGameController task
    */
    RunGameController &run_game_controller;

    /**
     * Reference to a SoundController task;
     */
    SoundController &sound_controller;

    /**
     * Main loop that the rtos tasks runs and suspends
     * It enables and disables running tasks based on the current state.
     * It will also swap the listeners for the receiver based on the current state.
     */
    void main() {

        for (; ;) {
           // receiver.enable();
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
                        button_controller.set_listener(&register_controller);

                        receiver.resume();
                        init_controller.suspend();
                        register_controller.resume();
                        run_game_controller.suspend();
                    }
                    register_controller.enable();

                    if(register_controller.state() == 1) {
                        sound_controller.play_shoot();
                        current_state = RUNNING;
                    }
                    break;
                case RUNNING:

                    if (receiver.get_controller()->get_name() != run_game_controller.get_name()) {
                        receiver.suspend();
                        receiver.set_controller(&run_game_controller);
                        button_controller.set_listener(&run_game_controller);
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
    /**
     * \brief Constructor for the Main class
     * \param r a Reference to a existing instance of a Receiver task
     * \param i a Reference to a existing instance of a InitGameController task
     * \param reg a Reference to a existing instance of a RegisterController task
     * \param run a Reference to a existing instance of a RunGameFController task
     */
    Main(Receiver &r, ButtonController &b, InitGameController &i, RegisterController &reg, RunGameController &run, SoundController &sound) : task("Main"), receiver(r), button_controller(b), init_controller(i),
                                                                        register_controller(reg), run_game_controller(run), sound_controller(sound) { }
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

    auto lsp = target::pin_out(target::pins::d13);
    // entities
    auto game_parameter = GameParameters();
    auto transmitter = Transmitter("transmitter", ir);
    auto sound_controller = SoundController(lsp);
    auto display_controller = DisplayController(oled);
    auto init_game_controller = InitGameController(transmitter, keypad, display_controller);
    auto register_controller = RegisterController(game_parameter, display_controller);
    auto run_game_controller = RunGameController(game_parameter, display_controller, sound_controller);
    auto receiver = Receiver("receiver", tsop_signal, &init_game_controller);
    auto gnd = target::pin_out( target::pins::d49);
    auto vlt = target::pin_out( target::pins::d51);
    auto but = target::pin_in( target::pins::d53);
    auto button_controller = ButtonController(&register_controller, gnd, vlt, but);
    auto main = Main(receiver, button_controller, init_game_controller, register_controller, run_game_controller, sound_controller);
    rtos::run();
}