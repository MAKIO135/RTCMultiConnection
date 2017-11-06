//Speed / accel parameters
const int iSpeed = 400; // Initially 300
const int iSpeedTranslate = 300; // Initially 300
const int iSpeedTurn = 200; //
const int iSpeedMediumTurn = 300; //
const float fAcceleration = 1.0f; // can be 0 to disable
const float fDeceleration = 1.0f; // can be 0 to disable

int int_deceleration_time = 300; // initially 300

//Motor power pins
const int MOTOR1_ENABLE_PIN = 2;
const int MOTOR1_DIRECTION_PIN = 3;
const int MOTOR2_ENABLE_PIN = 5;
const int MOTOR2_DIRECTION_PIN = 6;
const int MOTOR3_ENABLE_PIN = 8;
const int MOTOR3_DIRECTION_PIN = 9;
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
const char TRANSLATE_LEFT = 'a';
const char TRANSLATE_RIGHT = 'z';
const char MOVE_TABLET_UP = 'u';
const char MOVE_TABLET_DOWN = 'd';
const char TURN_LEFT = 'l';
const char TURN_RIGHT = 'r';
