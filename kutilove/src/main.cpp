#include <Arduino.h>
#include <Color.h>
#include <FastLED.h>
#include <hsv2rgb.h>
#include <Servo.h>
#include <DHT.h>

static const uint8_t LED_COUNT = 5;
static const uint8_t leds[] = { 6, 12, 13, 7, 8 };

struct Snake {
    Snake(): _goUp( true ), _index( 0 ) {}
    void advance() {
        if ( _goUp ) {
            _index++;
            if ( _index == LED_COUNT - 1 )
                _goUp = false;
        }
        else {
            _index--;
            if ( _index == 0 )
                _goUp = true;
        }
    }

    void begin() {}

    void run() {
        digitalWrite( 5, 0 );
        digitalWrite( 11, 0 );
        for ( int i = 0; i != LED_COUNT; i++ ) {
            digitalWrite( leds[ i ], i == _index );
        }
        advance();
        delay( 25 + analogRead( A0 ) / 4 );
    }

    bool _goUp;
    int _index;
};

struct RgbLed {
    RgbLed(): _color( 0, 255, 255 ) {}

    void begin() {}

    void run() {
        digitalWrite( 12, LOW );
        digitalWrite( 13, LOW );
        digitalWrite( 7, LOW );
        digitalWrite( 8, LOW );
        _color.h++;
        _color.v = analogRead( A1 ) / 4;
        CRGB r;
        hsv2rgb_rainbow( _color, r );
        analogWrite( 5, r.r );
        analogWrite( 6, r.g );
        analogWrite( 11, r.b );
        delay( 1 + ( 1024 - analogRead( A0 ) ) / 4 );
    }

    CHSV _color;
};

struct Meter {
    Meter() : _dht( A3, DHT11 ) {}

    void begin() {
        _servo.attach( 9 );
        _position = 0;
        _goUp = true;
        _dht.begin();
    }

    void run() {
        digitalWrite( 5, 0 );
        digitalWrite( 6, 0 );
        digitalWrite( 11, 0 );
        int tempGauge = max( 0, _dht.readTemperature() * 90 / 40 );
        int humGauge = _dht.readHumidity() * LED_COUNT / 100;
        _servo.write( tempGauge );
        for ( int i = 0; i != LED_COUNT; i++ )
            digitalWrite( leds[ LED_COUNT - i], i < humGauge );
        Serial.print( tempGauge );
        Serial.print( ", " );
        Serial.println( humGauge );
        delay(200);
    }

    DHT _dht;
    Servo _servo;
    uint8_t _position;
    bool _goUp;
};

Snake snake;
RgbLed rgb;
Meter meter;

void setup() {
    Serial.begin(9600);
    for( int i = 0; i != LED_COUNT; i++ )
        pinMode(leds[ i ], OUTPUT);
    pinMode( 5, OUTPUT );
    pinMode( 6, OUTPUT );
    pinMode( 11, OUTPUT );

    pinMode( 2, INPUT_PULLUP );
    pinMode( 3, INPUT_PULLUP );
    pinMode( 4, INPUT_PULLUP );

    snake.begin();
    rgb.begin();
    meter.begin();
}

int mode;

void loop() {
    if ( !digitalRead( 2 ) )
        mode = 0;
    if ( !digitalRead( 3 ) )
        mode = 1;
    if ( !digitalRead( 4 ) )
        mode = 2;

    if ( mode == 0 )
        snake.run();
    if ( mode == 1 )
        rgb.run();
    if ( mode == 2 )
        meter.run();
}