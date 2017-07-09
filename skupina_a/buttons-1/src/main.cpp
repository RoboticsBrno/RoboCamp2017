#include "LearningKit.h"


void setup() {
    Serial.begin( DEFAULT_SERIAL_SPEED );
    setupLeds();
    setupButtons();
}

void loop() {
    digitalWrite( LED_R, !digitalRead( BUTTON_1 ) );
    digitalWrite( LED_Y, !digitalRead( BUTTON_2 ) );
    digitalWrite( LED_G, !digitalRead( BUTTON_3 ) );
}