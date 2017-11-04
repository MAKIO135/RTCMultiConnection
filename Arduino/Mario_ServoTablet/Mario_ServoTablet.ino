#include <Servo.h>

#define UP 'u'
#define DOWN 'd'

// Tablet data
Servo servo;
const int servoPin = 12;
int desired = 30;

void setup(){
    servo.attach( servoPin );
    Serial.begin( 9600 );
    servo.write( desired );
}

void loop(){
    int position = servo.read();
    // Serial.println( "position: " + String( position ) );
    // Serial.println( "desired: " + String( desired ) );
    if( position < desired ){ // should look up
        position ++;
        servo.write( position );
    }
    else if( position > desired ){ // should look down
        position --;
        servo.write( position );
    }
    delay( 100 );
}

void serialEvent(){
    if ( Serial.available() > 0 ){
        char cmd = Serial.read();
        // Serial.println( cmd );
        if( cmd == DOWN ){
            desired -= 5;
        }
        else if( cmd == UP){
            desired += 5;
        }
        desired = constrain( desired, 0, 60 );
    }
}
