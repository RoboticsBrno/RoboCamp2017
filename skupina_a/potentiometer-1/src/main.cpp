#include "LearningKit.h"

const int LED_COUNT = 5;
int leds[] = { LED_B, LED_G, LED_Y, LED_R, RGB_B };

void setupAnalogLeds() {
    for ( int i = 0; i != LED_COUNT; i++ ) {
        ledcSetup( i, 5000, 16 );
        ledcAttachPin( leds[ i ], i );
    }
}

void setAnalogLed( int led, int value ) {
    ledcWrite( led, value * value );
}

void setup() {
    Serial.begin( DEFAULT_SERIAL_SPEED );
    setupLeds();
    setupAnalogLeds();
}

void loop() {
    int pot = analogRead( POT_1 );
    int l = ( pot * LED_COUNT ) / 4096;
    int p = ( pot * LED_COUNT ) % 4096 / 16;
    for ( int i = 0; i != l; i++ ) {
        setAnalogLed( i, 255 );
    }
    setAnalogLed( l, p );
    for ( int i = l + 1; i < LED_COUNT; i++ )
        setAnalogLed( i, 0 );
    delay( 50 );
}