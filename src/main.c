#include <Arduino.h>

#include "scheduler.h"

void timer_init(){
    noInterrupts(); // disable all interrupts
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;

    OCR1A = 31250; // compare match register 16MHz/256 = 62500 <- value for 1Hz blink
                   // since we use 31250 then its 2Hz blink
                   // OCR1A = 31;    // compare match register 16MHz/256/2kHz
    TCCR1B |= (1 << WGM12); // CTC mode -> clear timer on compare match
    TCCR1B |= (1 << CS12); // 256 prescaler -> set prescaler as 256
    TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
    interrupts(); // enable all interrupts
}

ISR(TIMER1_COMPA_vect){
    Sched_Schedule();
}

#define LED1 10
#define LED2 11
#define LED3 12
#define LED4 13

void setup(){
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);

    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
}

void blink_led(int led) {digitalWrite(led, !digitalRead(led));}

void blink1(void){
    blink_led(LED1);
}

void blink2(void){
    blink_led(LED2);
}

void blink3(void){
    blink_led(LED3);
}

void blink4(void){
    blink_led(LED4);
}

void loop(){
    timer_init();
    Sched_Init();

    Sched_AddT(blink1, 10, 1);
    Sched_AddT(blink2, 5, 2);
    Sched_AddT(blink3, 1, 4);
    Sched_AddT(blink4, 3, 3);

    while(1){
        Sched_Dispatch();
    }
}
