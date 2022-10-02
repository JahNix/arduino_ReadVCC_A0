
/*  Basic Script for the Arduino to read voltage and initiate
 *  a Shutdown to the RPi based on voltage found.
 *  
 *  While we could do this on the base RPi, we can use the
 *  Low-Power arduino for other LowLevel functions like
 *  charging management if we require.
 *  
 *  We are reading the state of a single 3.7V Lipo/18650
 *  5 Volts Max so we can use an Analog Input on the Arduino.
 */
 
const int vcc_pin = A0;
int lvc_pin = A5;


void setup(){
    Serial.begin( 9600 );
}

void loop(){
 
    int vcc_value;
    float vcc_volt;

    vcc_value = analogRead( vcc_pin );
    vcc_volt = (vcc_value + 0.5) * 5 / 1024.0;

    Serial.print( "Value: " );
    Serial.print( vcc_value );
    Serial.print( "  Volt: " );
    Serial.println( vcc_volt );

    if (vcc_volt < 3.4) {
      analogWrite( lvc_pin, 170 );
      Serial.println( "LVC Kicking In" );
    }
    else if ((vcc_volt >= 3.4) && (vcc_volt < 3.7)) {
      analogWrite( lvc_pin, 0 );
      Serial.println( "Recharge Needed Soon" );
    }
    else if ((vcc_volt >= 3.7) && (vcc_volt < 3.8)) {
      analogWrite( lvc_pin, 0 );
      Serial.println( "Still Healthy" );
    }
    else if (vcc_volt >= 3.8) {
      analogWrite( lvc_pin, 0 );
      Serial.println( "Full Battery - AOK!" );
    }
 
    delay( 5000 );
 
}
