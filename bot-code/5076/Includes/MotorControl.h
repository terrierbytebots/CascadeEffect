/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Module: MotorControl.h
//
// Description:
//        Drive system interface handling all logical drive commands and direct drive system motor control
//
// Usage:
//        1) Start the stall task
//        2) Call IsStalled() to determine if a drive side is stalled
//
// Direct Motor Use:
//        LeftUpperDrive   - left side upper motor  (mtr_S1_C1_1)
//        LeftLowerDrive  - left side lower motor  (mtr_S1_C4_1)
//        RightUpperDrive  - right side upper motor (mtr_S1_C1_2)
//        Right2_Drive - right side lower motor (mtr_S1_C4_2)
//
// Direct Sensor Use:
//        motor encoders for above
//
// Timer Use:
//        none
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#pragma systemFile            // this eliminates warning for "unreferenced" functions

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Includes
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// #defines
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Public Global Variables
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Private Global Variables
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Public Function Declarations
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// These are the only functions that are allowed to directly access the motors themselves
//
#define CurrMotorPwr(nDriveSide)     ( (nDriveSide == LEFT_SIDE) ? motor[LRD] : motor[RRD] )

#define LeftRawDriveEncoderVal   nMotorEncoder[LFD]
#define RightRawDriveEncoderVal  nMotorEncoder[RFD]

//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Private Function Declarations
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Task Definitions
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function Definitions
//

/////////////////////////////////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTION: Auto balance using the accelerometer
//

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DIRECT MOTOR CONTROL ... These functions encapsulate the drive motors.
//                          NO OTHER CODE SHOULD DIRECTLY CHANGE MOTOR SETTING!!!
//

/////////////////////////////////////////////////////////////////////////////////////////
//
// PUBLIC FUNCTION: Set motor power for indicated side (left or right) of the drive system
//
// Called ***ONLY*** by the main task
// ...NO OTHER TASK SHOULD EVER CALL THIS
// ...THIS IS THE ONLY FUNCTION THAT SHOULD EVER DIRECTLY APPLY POWER TO THE DRIVE MOTORS
//
void ApplyMotorPower(tDriveSide nDriveSide, int nMotorPower)
{
	if ( nDriveSide == LEFT_SIDE )
	{
	  //motor[DriveLeft] = nMotorPower;
		motor[LFD] = -nMotorPower;
		motor[LRD] = -nMotorPower;
	}
	else if ( nDriveSide == RIGHT_SIDE )
	{
	  //motor[DriveRight] = nMotorPower;
		motor[RFD] = nMotorPower;
		motor[RRD] = nMotorPower;
	}
}

#endif // MOTOR_CONTROL_H
