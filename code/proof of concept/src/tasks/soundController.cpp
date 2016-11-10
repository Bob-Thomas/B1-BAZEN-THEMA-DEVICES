//
// Created by endargon on 11/10/16.
//

#include "soundController.h"

SoundController::SoundController(hwlib::pin_out &lsp, rtos::mutex & mutex)
        : task("sound controller"), lsp(lsp), play_sound(this, "play-sound"), sounds(this), sound_mutex(mutex) {}

void SoundController::main() {
    for(;;) {
        wait(play_sound);
        sound_mutex.wait();
        for(int i = 0; i < 20; i++) {
            play(sounds.read());
        }
        sounds.clear();
        sound_mutex.signal();
        ;        }
}

void SoundController::play(Sound s ) {
    if( s.frequency == 0 ){
        hwlib::wait_us( s.duration );
    } else {
        auto end = hwlib::now_us() + s.duration;
        auto half_period = 1'000'000 / ( 2 * s.frequency );
        while( end > hwlib::now_us() ){
            lsp.set( 1 );
            hwlib::wait_us( half_period );
            lsp.set( 0 );
            hwlib::wait_us( half_period );
        }
    }
}

void SoundController::play_shoot() {
    sound_mutex.wait();
    for(int i = 0; i < 20; i++) {
        sounds.write({2000-(100*i), 10000});
    }
    sound_mutex.signal();
    play_sound.set();
}