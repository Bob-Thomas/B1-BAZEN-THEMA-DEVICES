//
// Created by robbie on 9-11-2016.
//

#ifndef CODE_RUNEGAMECONTROLLER_H
#define CODE_RUNEGAMECONTROLLER_H

#include "../../../libs/rtos/rtos.hpp"
#include "../entities/gameParameters.h"
#include "controller.h"
#include "../../../libs/hwlib/hwlib-ostream.hpp"
#include "displayController.h"
#include "soundController.h"
#include "transmitter.h"
/**
 * \class RunGameController
 * \brief can be interpretted as playing state and will handle each event during his state.
 */
class RunGameController : public Controller, public rtos::task<> {
private:
    /**
     * \brief fflag to enable the task
     */
    rtos::flag enabled;
    /**
     * \brief rtos flag will be used for detecting button press
     */
    rtos::flag pressed;

    /**
    * \brief rtos flag will be used for detecting hits
    */
    rtos::flag hit;

    /**
    * \brief rtos clock that will count down the minutes
    */
     rtos::clock game_timer;
    /**
     * \brief gameParameters will be an entity object for storring the personal player data.
     */
    GameParameters &gameParameters;

    /**
     * \brief DisplayController reference handles text display on oled screen.
     */
    DisplayController &displayCtrl;

    /**
     * \brief Transmitter reference handles sending data over IR
     */
    Transmitter &transmitter;
    /**
     * \brief SoundController reference handles sound.
     */
    SoundController &soundCtrl;

    /**
     * \briefRTOS task function.
     */
    void main();

public:
    /**
     * \brief interface function for activating task.A
     */
    void enable();

    /**
     * \brief interface function for receiving a command
     * \param Command c for encode en decode data.
     */
    void receive(Command c);

    /**
     * \brief interface function for getting controller name.
     */
    const char *get_name() {
        return this->name();
    }

    /**
    * \brief button_pressed interface function.
    */
    void button_pressed();

    /**
     * \brief Update the oled display with game timer and current health points
     * \param alive a simple boolean to show a alive display layout or dead layout q
     */
    void update_screen_game_parameters(bool alive);

    /**
     * RunGameController constructor.
     * \param &gameParam to set or get player game settings.
     * \param &disCtrl to write text on screen.
     */
    RunGameController(GameParameters &gameParam, DisplayController &disCtrl, Transmitter &t, SoundController &sCtrl);
};

#endif //CODE_RUNEGAMECONTROLLER_H
