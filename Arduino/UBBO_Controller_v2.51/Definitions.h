// For tablet serial prot
const char STX = '<';
const char ETX = '>';

//Speed / accel parameters
const int iSpeed = 400; // Initially 300
const int iSpeedTranslate = 300; // Initially 300
const int iSpeedTurn = 200; //
const int iSpeedMediumTurn = 300; //
const float fAcceleration = 1.0f; // can be 0 to disable
const float fDeceleration = 1.0f; // can be 0 to disable

int int_deceleration_time = 300; //initially 300

//Motor power pins
const int MOTOR1_ENABLE_PIN = 2;
const int MOTOR1_DIRECTION_PIN = 3;

const int MOTOR2_ENABLE_PIN=5;
const int MOTOR2_DIRECTION_PIN=6;

const int MOTOR3_ENABLE_PIN =8;
const int MOTOR3_DIRECTION_PIN =9;

const int MOTOR4_ENABLE_PIN = 11;
const int MOTOR4_DIRECTION_PIN = 12;

//Motors sensors
const int MOTOR1_IRQ_PIN = 18;
const int MOTOR1_IRQB_PIN = 31;

const int MOTOR2_IRQ_PIN = 19;
const int MOTOR2_IRQB_PIN = 32;

const int MOTOR3_IRQ_PIN = 20;
const int MOTOR3_IRQB_PIN = 33;

const int MOTOR4_IRQ_PIN = 21;
const int MOTOR4_IRQB_PIN = 34;

//Command Values
const char GO_FORWARD = 'f';
const char GO_BACKWARD = 'b';
const char STOP = 's';
const char GO_BACK_DOCKSTATION = 0x4;
const char TRANSLATE_LEFT = 0x08;
const char TRANSLATE_RIGHT = 0x09;
const char MOVE_TABLET = 0x10;
const char MOVE_TABLET_UP = 'u';
const char MOVE_TABLET_DOWN = 'd';
const char HEART_BEAT = 0x11;
const char TURN_LEFT = 'l';
const char TURN_RIGHT = 'r';

//Nb max of variable in the message
const int MAX_VAR= 10;

const byte END_OF_FRAME_1 = 0x7F;
const byte END_OF_FRAME_2 = 0x00;
const byte END_OF_FRAME_3 = 0x7F;

#ifdef DEBUG
    #define dbg_print(x)    Serial.print (x)
    #define dbg_print_hex(x)    Serial.print (x,HEX)
    #define dbg_println(x)  Serial.println (x)
    #define dbg_println_hex(x,y)  Serial.println (x,HEX)
    #define dbg2_print(x)    Serial2.print (x)
    #define dbg2_println(x)  Serial2.println (x)
    #define dbg_line() Serial.print("line : ");Serial.print(__LINE__)
    #define dbg_lineln() Serial.print("line : ");Serial.println(__LINE__)
#else
    #define dbg_print(x)
    #define dbg_print_hex(x)
    #define dbg_println(x)
    #define dbg_println_hex(x)
    #define dbg2_print(x)
    #define dbg2_println(x)
    #define dbg_line()
    #define dbg_lineln()
#endif
