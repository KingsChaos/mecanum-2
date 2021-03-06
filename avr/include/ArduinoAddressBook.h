#ifndef ARDUINOADDRESSBOOK_H
#define ARDUINOADDRESSBOOK_H

#define FSM_MASTER           0
#define FSM_BATTERYMONITOR   1
#define FSM_BLINK            2
#define FSM_CHRISTMASTREE    3
#define FSM_FADE             4
#define FSM_MIMIC            5
#define FSM_TOGGLE           6
#define FSM_DIGITALPUBLISHER 7
#define FSM_ANALOGPUBLISHER  8
#define FSM_MOTORCONTROLLER  9
#define FSM_SERVOSWEEP       10
#define FSM_SENTRY           11
#define FSM_ENCODER          12

#define MSG_MASTER_CREATE_FSM      0
#define MSG_MASTER_DESTROY_FSM     1
#define MSG_MASTER_LIST_FSM        2
#define MSG_MASTER_ENCODER_SAMPLES 3

// PWM LEDs
#define LED_GREEN     4
#define LED_YELLOW    7
#define LED_RED       8
#define LED_UV        9
#define LED_EMERGENCY 10

// Digital LEDs
#define LED_STATUS_GREEN   44
#define LED_STATUS_YELLOW  46
#define LED_BATTERY_EMPTY  48
#define LED_BATTERY_LOW    42
#define LED_BATTERY_MEDIUM 50
#define LED_BATTERY_HIGH   52
#define LED_BATTERY_FULL   52 // Alias

// BeagleBoard interface
#define BEAGLEBOARD_BRIDGE1 19
#define BEAGLEBOARD_BRIDGE2 17
#define BEAGLEBOARD_BRIDGE3 20
#define BEAGLEBOARD_BRIDGE4 16
#define BEAGLEBOARD_BRIDGE5 14
#define BEAGLEBOARD_BRIDGE6 18
#define BEAGLEBOARD_RESET   15

// Motors
#define MOTOR1_PWM 5
#define MOTOR1_A   26
#define MOTOR1_B   22
#define MOTOR1_CS  14 // Analog
#define MOTOR2_PWM 6
#define MOTOR2_A   28
#define MOTOR2_B   38
#define MOTOR2_CS  15 // Analog
#define MOTOR3_PWM 2
#define MOTOR3_A   30
#define MOTOR3_B   24
#define MOTOR3_CS  13 // Analog
#define MOTOR4_PWM 3
#define MOTOR4_A   32
#define MOTOR4_B   36
#define MOTOR4_CS  12 // Analog

// Encoders (to be determined)
#define SERVO_ENCODER   35
/*
#define MOTOR1_ENCODER1 35-53
#define MOTOR1_ENCODER2 35-53
#define MOTOR2_ENCODER1 35-53
#define MOTOR2_ENCODER2 35-53
#define MOTOR3_ENCODER1 35-53
#define MOTOR3_ENCODER2 35-53
#define MOTOR4_ENCODER1 35-53
#define MOTOR4_ENCODER2 35-53
*/

// Base (to be determined)
#define PROXIMITY_SERVO 53
/*
#define BASE_NC         35-53
#define PROXIMITY1      2 // Analog
#define PROXIMITY2      3 // Analog
#define PROXIMITY3      7 // Analog
#define PROXIMITY4      8 // Analog
*/

// Top
#define TOP1 23 // Not Connected
#define TOP2 31 // Not Connected
#define TOP3 13 // PWM
#define TOP4 29
#define TOP5 12 // PWM
#define TOP6 25
#define TOP7 11 // PWM
#define TOP8 27

// Battery voltage divider: R1 = 16.05k, R2 = 9.87k
#define BATTERY_VOLTAGE 11    // Analog
#define BATTERY_R1      16.05f // kOhm
#define BATTERY_R2      9.87f  // kOhm

// Not Connected
#define REGULATOR_ENABLE 21
#define TEMPERATURE      40
#define THATSNOTYOURS1   34
#define THATSNOTYOURS2   33


#endif // ARDUINOADDRESSBOOK_H
