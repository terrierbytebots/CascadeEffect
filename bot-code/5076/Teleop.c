#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S4, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S2,     GyroSensor,     sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     IRsensor1,      sensorI2CCustom)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     LeftDrive,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     LeftLift,      tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     Collector,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_1,     RightDrive,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S4_C1_2,     RightLift,     tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S4_C2_1,    LeftGrab,             tServoStandard)
#pragma config(Servo,  srvo_S4_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S4_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S4_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S4_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S4_C2_6,    RightGrab,            tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define TEAM_NUMBER 5076

#include "Includes/TeamConfig.h"
#include "../Common/Teleop.h"