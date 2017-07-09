#pragma once

#include "Arduino.h"

static const int DEFAULT_SERIAL_SPEED = 115200;

static const int LED_R = 22;
static const int LED_G = 17;
static const int LED_Y = 23;
static const int LED_B = 5;
static const int RGB_R = 4;
static const int RGB_G = 16;
static const int RGB_B = 21;

static const int BUTTON_1 = 15;
static const int BUTTON_2 = 2;
static const int BUTTON_3 = 0;


void setupLeds() {
    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);
    pinMode(LED_Y, OUTPUT);
}

void setupRgbLed() {
    pinMode(RGB_R, OUTPUT);
    pinMode(RGB_G, OUTPUT);
    pinMode(RGB_B, OUTPUT);
}

void setupButtons() {
    pinMode( BUTTON_1, INPUT_PULLUP );
    pinMode( BUTTON_2, INPUT_PULLUP );
    pinMode( BUTTON_3, INPUT_PULLUP );
}