//
// Created by robbie on 8-11-2016.
//

#include "displayController.h"
DisplayController::DisplayController(hwlib::glcd_oled_buffered &o): oled(o), buffer( this, "buffer" ), timer_screen(this, "timer screen"), clearFlag(this, "clear screen flag"), flushFlag(this, "set flush flag") {
}

void DisplayController::main() {

    hwlib::font_default_8x8 font;
    oled.clear();
    for(;;){
        oled.clear();
        wait( flushFlag );
        char presented_text[2048];
        hwlib::window_ostream stream(oled, font);

        for(int i = 0; i < 2028; i++) {
            presented_text[i] = buffer.read();
        }
        hwlib::cout << HERE << " : " << presented_text;

        stream << presented_text;
        oled.flush();
    }
}


void DisplayController::displayText(const char * txt) {
    buffer.clear();
    flushFlag.set();
    for(int i = 0; i < 2048; i++) {
        buffer.write(txt[i]);
    }

}
