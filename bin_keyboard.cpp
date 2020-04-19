#include "mbed.h"
#include "USBKeyboard.h"
#include "PinDetect.h"

USBKeyboard keyboard;
 
PinDetect sw0(P0_0);
PinDetect sw1(P0_1);

DigitalOut led1(LED1);
DigitalOut led2(LED2);

int state = 0;
char code = 0x00;
unsigned int pressed_count_0 = 0;
unsigned int pressed_count_1 = 0;
 
void pressed_0()
{
    led1 = 0;
    code = code << 1;
    state++;
}
 
void pressed_1()
{
    led2 = 0;
    code = code << 1;
    code++;
    state++;
}
 
int main(void)
{
    led1 = 1;
    led2 = 1;
 
    sw0.mode(PullUp);
    sw1.mode(PullUp);
 
    sw0.attach_deasserted(&pressed_0);
    sw1.attach_deasserted(&pressed_1);

    sw0.setSampleFrequency();
    sw1.setSampleFrequency();
 
    while(1) {
        if(state == 8){
           keyboard.keyCode(code);
           state = 0;
        }
    }
}