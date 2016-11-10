//
// Created by endargon on 11/10/16.
//

#ifndef CODE_SOUNDCONTROLLER_H
#define CODE_SOUNDCONTROLLER_H

#include "../../../libs/rtos/rtos.hpp"
#include "../../../libs/hwlib/hwlib-pin.hpp"

struct Sound {
    int frequency;
    int duration;
};

/**
 * \class SoundController
 * \brief Simple task that can play a predefined sound
 *
 * This class has the ability of playing a so called shoot sound
 */
class SoundController : public rtos::task<> {
    /** Pin used for outputting sound to the speaker **/
    hwlib::pin_out &lsp;
    /** Flag to be set if sound can be playe **/
    rtos::flag play_sound;
    /** Simple channel which will hold a wave of sounds **/
    rtos::channel<Sound, 20> sounds;

    /**
     * \brief function to translate frequency and duration into pulses
     * \param s A sound struct with frequency and duration defined
     */
    void play(Sound s);

    /**
     * Rtos main loop
     * Will wait on the flag play_sound to be set.
     * If the flag is set it will read from the channel and play the sounds stored in the channel;
     */
    void main();

public:
    /**
     * \brief Constructor of the SoundController
     * \param lsp Pin that will be turn on and off to send pulses to the speaker
     */
    SoundController(hwlib::pin_out &lsp);

    /**
     * \brief Simple function which will fill the sound channel with specific sounds. and set the play_sound flag so a sound will be played
     */
    void play_shoot();
};


#endif //CODE_SOUNDCONTROLLER_H
