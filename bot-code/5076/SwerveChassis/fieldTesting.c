#pragma config(Hubs,  S3, HTMotor,  HTMotor,  HTServo,  HTServo)
#pragma config(Hubs,  S4, HTMotor,  none,     none,     none)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S3_C1_1,     RRD,           tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S3_C1_2,     motorE,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S3_C2_1,     RFD,           tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S3_C2_2,     SPIN,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S4_C1_1,     LFD,           tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S4_C1_2,     LRD,           tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S3_C3_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S3_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S3_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S3_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S3_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S3_C3_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S3_C4_1,    servo7,               tServoNone)
#pragma config(Servo,  srvo_S3_C4_2,    servo8,               tServoNone)
#pragma config(Servo,  srvo_S3_C4_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S3_C4_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S3_C4_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S3_C4_6,    servo12,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//int GyroSensor = 0;

#define TEAM_NUMBER 3717

#include "JoystickDriver.c"
#include "../Includes/TeamConfig.h"
#include "../../Common/GlobalDefines.h"
//#include "../../Common/Control/SensorTask.h"

float calcJoystickAngle(int xaxis, int yaxis); //function prototypes
int calcJoyPower(int xaxis, int yaxis);
float calcGoalAngle(float joyAngle, float gyroAngle, float wheelAngle);
void turnSwerveSystem(float goalAngle2, float joyPower2);

float joyAngle = 0.0;
int joyPower = 0;
float goalAngle = 0.0;
int driveDirection = 1;

//temporary Gyro.fAngle for actual Swerve chassis testing
float GyrofAngle = 0.0;

task main()
{
	//StartTask(SensorTask);
  eraseDisplay();
	nMotorEncoder[SPIN] = 0;

  int yaxis = 0;
  int xaxis = 0;

  while (true) {
  	disableDiagnosticsDisplay();
  	getJoystickSettings(joystick);
	  yaxis = joystick.joy1_y1;
    xaxis = joystick.joy1_x1;

    joyAngle = calcJoystickAngle(xaxis, yaxis);
    //joyPower = calcJoyPower(xaxis, yaxis);
    joyPower = 0;
    goalAngle = calcGoalAngle((float)joyAngle, GyrofAngle, -(float)nMotorEncoder[SPIN]/4);
    turnSwerveSystem(goalAngle, (float)joyPower);
    nxtDisplayCenteredTextLine(2, "joyAngle: %4.2f", joyAngle);
    nxtDisplayCenteredTextLine(4, "gyroAngle: %4.2f", GyrofAngle);
    nxtDisplayCenteredTextLine(6, "goalAngle: %4.2f", goalAngle);

    wait1Msec(10); //buffer for debugger console
	}
}

float calcJoystickAngle(int xaxis, int yaxis) {
  float angle;
	if(abs(yaxis) > 10 || abs(xaxis) > 10) {
	  angle = atan(((float)yaxis/(float)xaxis));
	  angle = angle * (180.0/PI);
		if(yaxis >= 0 && xaxis >= 0) {
		  angle = 90.0 - abs(angle);
		}
		else if(yaxis <= 0 && xaxis >= 0) {
		  angle = abs(angle) + 90.0;
		}
		else if(yaxis <= 0 && xaxis <= 0) {
		  angle = 90.0 - abs(angle) + 180.0;
		}
		else if(yaxis >= 0 && xaxis <= 0) {
		  angle = abs(angle) + 270.0;
		}
		//convert 0<->360 range to -180<->180
		if (angle > 180) {
		  angle = (360.0-angle) * -1.0;
	  }
	  return angle;
  }
  else {
    return 0;
  }
}

float calcGoalAngle(float joyAngle, float gyroAngle, float wheelAngle) {
	float oldAlgorithm = ((gyroAngle + wheelAngle) * -1) + joyAngle; //returns the number of degrees needed acheive desired goal.
  /*float newAlgorithm = (180 - oldAlgorithm) * -1;
  if (abs(oldAlgorithm) < abs(newAlgorithm)) {
    driveDirection = 1;
    return oldAlgorithm;
  }
  else {
    driveDirection = -1;
    return newAlgorithm;
  }*/
  return oldAlgorithm;
}

int calcJoyPower(int xaxis, int yaxis)
{
	float power = sqrt(pow(abs(xaxis),2) + pow(abs(yaxis),2));
	return (int)(power*0.78125); //translate max joystick value of 128 to max motor value of 100
}

void turnSwerveSystem(float goalAngle2, float joyPower2) {
  /*int goalTick = (int)(goalAngle2 * 4); //translate degrees to ticks

  if (abs(goalTick) < 10) { //threshold of 10 ticks - if it's reached the goal
  	motor[SPIN] = 0;
	}
	else {
	  if (goalTick < 0) {
	  	motor[SPIN] = abs(goalAngle)*5;
	  }
	  else {
	  	motor[SPIN] = -abs(goalAngle)*5;
	  }
	}*/

	if (abs(goalAngle2) < 2) {
		motor[SPIN] = 0;
	}
	else {
		if (goalAngle2 < 0) {
			motor[SPIN] = -90;
		}
		else {
			motor[SPIN] = 90;
		}
	}

	motor[RRD] = joyPower2 * driveDirection;
	motor[RFD] = joyPower2 * driveDirection;
	motor[LRD] = joyPower2 * driveDirection;
	motor[LFD] = joyPower2 * driveDirection;
}