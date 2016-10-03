#include "hwlib-due.hpp"
int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::cout << "test" << "\n";
}