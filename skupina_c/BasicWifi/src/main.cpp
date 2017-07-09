#include <Arduino.h>
#include <WiFi.h>

#include "credentials.h"

//  WL_IDLE_STATUS
// WL_NO_SSID_AVAIL
// WL_SCAN_COMPLETED
// WL_CONNECTED
// WL_CONNECT_FAILED
// WL_CONNECTION_LOST
// WL_DISCONNECTED


void setup() {
    Serial.begin(115200);

    WiFi.mode( WIFI_STA );
    WiFi.begin( ssid, password );
    while( WiFi.status() != WL_CONNECTED ) {
        delay( 500 );
        Serial.print( "." );
    }

    Serial.println( "" );
    Serial.print( "Pripojil jsem se k ");
    Serial.print( ssid );
    Serial.print( " s IP adresou ");
    Serial.println( WiFi.localIP() );
}

void loop() {}