//
// Created by smart on 11/19/2016.
//

#include "sound.h"

Sound::Sound(int priority, hwlib::pin_out &lsp)
        : task(priority, "sound controller"), lsp(lsp), play_sound(this, "play-sound"), sounds(this) { }

void Sound::main() {
    for (; ;) {
        wait(play_sound);
        for (int i = 0; i < 20; i++) {
            play(sounds.read());
        }
        sounds.clear();
    }
}

void Sound::play(sound_effect s) {
    if (s.frequency == 0) {
        hwlib::wait_us(s.duration);
    } else {
        auto end = hwlib::now_us() + s.duration;
        auto half_period = 1'000'000 / (2 * s.frequency);
        while (end > hwlib::now_us()) {
            lsp.set(1);
            hwlib::wait_us(half_period);
            lsp.set(0);
            hwlib::wait_us(half_period);
        }
    }
}

void Sound::play_shoot() {
    for (int i = 0; i < 20; i++) {
        sounds.write({2000 - 100 * i, 10000});
    }
    play_sound.set();
}