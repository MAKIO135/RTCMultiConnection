/*
   Pin 2: (E1 ASM 1) PWM wheel Front Right
   Pin 3: (M1 ASM 1) DIR wheel Front Right
   Pin 5: (E2 ASM 1) PWM wheel Back Right
   Pin 6: (M2 ASM 1) DIR wheel Back Right
   Pin 8: (E1 ASM 2) PWM wheel Back Left
   Pin 9: (M1 ASM 2) DIR wheel Back Left
   Pin 11: (E2 ASM 2) PWM wheel Front Left
   Pin 12: (M2 ASM 2) DIR wheel Front Left
   Pin 14: Serial 3 for Arduino Servo controller
   Pin 16 : (Internal) RX Carte bluetooth (Serial 2)
   Pin 17 : (Internal) TX Carte bluetooth

   M1 Red Wire: ((+)1 ASM 1)
   M1 black Wire: ((-)1 ASM 1)
   M2 Red Wire: ((+)2 ASM 1)
   M2 black Wire: ((-)2 ASM 1)
   M3 Red Wire: ((-)1 ASM 2)
   M3 black Wire: ((+)1 ASM 2)
   M4 Red Wire: ((-)2 ASM 2)
   M4 black Wire: ((+)2 ASM 2)
 */

#include "MotorWheel.h"
#include "Omni4WD.h"
#include "PID.h"
#include "PinChangeInt.h"
#include "PinChangeIntConfig.h"
#include "Definitions.h"

long timer = 0;
char cmd = 0;
int timeout = 500;
int direction = 90;

// Declaration of Motors and encoders (pinouts)
irqISR( irq1, isr1 );
MotorWheel wheel1( MOTOR1_ENABLE_PIN, MOTOR1_DIRECTION_PIN, MOTOR1_IRQ_PIN, MOTOR1_IRQB_PIN, &irq1 );

irqISR( irq2, isr2 );
MotorWheel wheel2( MOTOR2_ENABLE_PIN, MOTOR2_DIRECTION_PIN, MOTOR2_IRQ_PIN, MOTOR2_IRQB_PIN, &irq2 );

irqISR( irq3, isr3 );
MotorWheel wheel3( MOTOR3_ENABLE_PIN, MOTOR3_DIRECTION_PIN, MOTOR3_IRQ_PIN, MOTOR3_IRQB_PIN, &irq3 );

irqISR( irq4, isr4 );
MotorWheel wheel4( MOTOR4_ENABLE_PIN, MOTOR4_DIRECTION_PIN, MOTOR4_IRQ_PIN, MOTOR4_IRQB_PIN, &irq4 );

Omni4WD Ubbo( &wheel1, &wheel3, &wheel2, &wheel4 );

void setup(){
    //Initialize robot PWM
    delay( 2000 );
    TCCR1B = TCCR1B & 0xf8 | 0x01; // Pin12 &11 PWM 31250Hz
    TCCR2B = TCCR2B & 0xf8 | 0x01; // Pin9,Pin10 PWM 31250Hz
    TCCR3B = TCCR3B & 0xf8 | 0x01; // Pin 5,3, 2 PWM 31250Hz
    TCCR4B = TCCR4B & 0xf8 | 0x01; // Pin8,7,6 PWM 31250Hz

    //Init motors and PID
    Ubbo.PIDEnable( 1.0, 0.8, 0.5, 10 );
    Ubbo.setAcceleration( fAcceleration );
    Ubbo.setDeceleration( fDeceleration );

    // initialize serials:
    Serial.begin( 9600 );
    Serial2.begin( 9600 );
    Serial3.begin( 9600 );
    Serial.println( "Waiting for commands ..." );
}

void loop(){
    if( cmd != 0 ){
        timeout = 500;
        timer = millis();

        switch ( cmd ) {
            case GO_FORWARD:
                Ubbo.doMovement( Omni4WD::STAT_MOVE_FORWARD, iSpeed );
                break;

            case GO_BACKWARD:
                Ubbo.doMovement( Omni4WD::STAT_MOVE_BACKWARD, iSpeed );
                break;

            case TURN_LEFT:
                timeout = 100;
                Ubbo.doMovement( Omni4WD::STAT_TURN_LEFT, iSpeedTurn );
                break;

            case TURN_RIGHT:
                timeout = 100;
                Ubbo.doMovement( Omni4WD::STAT_TURN_RIGHT, iSpeedTurn );
                break;

            case TRANSLATE_LEFT:
                Ubbo.doMovement( Omni4WD::STAT_TRANSLATE_LEFT, iSpeedTranslate );
                break;

            case TRANSLATE_RIGHT:
                Ubbo.doMovement( Omni4WD::STAT_TRANSLATE_RIGHT, iSpeedTranslate );
                break;

            case STOP:
                Ubbo.doMovement( Omni4WD::STAT_STOP );
                break;

            case MOVE_TABLET_UP: // Move Tablet Servo
            case MOVE_TABLET_DOWN: // Move Tablet Servo
                Serial3.write( cmd );
                break;

            default: // Other
                Serial.println( "Unknown command" );
                break;
        }
    }
    else{
        if( millis() - timer > timeout ){
            Ubbo.doMovement( Omni4WD::STAT_STOP );
        }
    }

    cmd = 0;
    Ubbo.PIDRegulate();
}
