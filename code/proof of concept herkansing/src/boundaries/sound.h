//
// Created by smart on 11/19/2016.
//

#ifndef CODE_SOUND_H
#define CODE_SOUND_H

#include "../../../libs/rtos/rtos.hpp"
#include "../../../libs/hwlib/hwlib.hpp"

/**
 * \struct Sound
 * \brief simple struct to maintain frequency and duration data
 */
struct sound_effect {
    int frequency;
    int duration;
};

/**
 * \class SoundController
 * \brief Simple task that can play a predefined sound
 *
 * This class has the ability of playing a so called shoot sound
 */
class Sound : public rtos::task<> {
        /** Pin used for outputting sound to the speaker **/
        hwlib::pin_out &lsp;
        /** Flag to be set if sound can be playe **/
        rtos::flag play_sound;
        /** Simple channel which will hold a wave of sounds **/
        rtos::channel<sound_effect, 20> sounds;

        /**
         * \brief function to translate frequency and duration into pulses
         * \param s A sound struct with frequency and duration defined
         */
        void play(sound_effect s);

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
        Sound(int priority, hwlib::pin_out &lsp);

        /**
         * \brief Simple function which will fill the sound channel with specific sounds. and set the play_sound flag so a sound will be played
         */
        void play_shoot();

        /**
        * \brief Simple function which will fill the sound channel with specific sounds. and set the play_sound flag so a sound will be played
        */
        void play_hit();
};
#endif //CODE_SOUND_H
