#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  button1,        sensorTouch)
#pragma config(Sensor, dgtl2,  button2,        sensorTouch)
#pragma config(Sensor, dgtl3,  winchswitch,    sensorTouch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           imeLeft,       tmotorVex393_HBridge, openLoop, driveRight, encoderPort, I2C_1)
#pragma config(Motor,  port2,           motorLeft,     tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port3,           winch,         tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port9,           motorRight,    tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port10,          imeRight,      tmotorVex393_HBridge, openLoop, reversed, driveRight, encoderPort, I2C_2)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// WHEN YOU FINISH EACH EXERCISE, INCREMENT THIS VALUE
#define EXERCISE_NUMBER 	1
int distconst = 0.5;
bool button1_pushed; //flag to store button1 input
bool button2_pushed; //flag to store button2 input
bool winchswitch_pushed;


/* monitorInput()
*
*  Used to flag button inputs
*       - this avoids errors caused by program recognizing input, taking action, and
*         reading input again before button is released
*/
void monitorInput()
{
	if(SensorValue(button1) && !button1_pushed)
	{
		button1_pushed = true;
	}

	if(SensorValue(button2) && !button2_pushed)
	{
		button2_pushed = true;
	}
		if(SensorValue(winchswitch) && !winchswitch_pushed)
	{
		winchswitch_pushed = true;
	}
}

void RobotOperation()
{
	enum T_test_state{          //Initialize 3 states
		stopped = 0,
		forward,
		backward,
		winch,

	};
	T_test_state exer3_state = stopped;     //Set initial state to "stopped"
	while(true)
	{
		monitorInput();

		/* INSERT CODE HERE
		* - make sure EXERCISE_NUMBER is set to 3
		*/

		switch(exer3_state){

		case stopped:                            //Stopped Case
			writeDebugStream("Stopped[%d]\n",time1[T1]);
			motor[imeLeft] = 0;										//Set motor speed to 50
			motor[imeRight] = 0;
			motor[motorLeft] = 0;
			motor[motorRight] = 0;
			motor[winch] = 0;
			resetMotorEncoder(imeRight);             //Zero the motor encoder
			if(button1_pushed == true){
				exer3_state = forward;               //Change state to forward when button 1 pushed
				button1_pushed = false;              //debounce button1
			}
			if(button2_pushed == true){
				exer3_state = backward;             //Change state fo backwards when button 2 pushed
				button2_pushed = false;							//debounce button2
			}
			if(winchswitch_pushed == true){
				exer3_state = winch;
			}

			break;

		case forward:
		int motorpos = getMotorEncoder(imeRight);
			writeDebugStream("Forwards, (%d)\n", motorpos);
			int speed = 30;
			int TargetDistance = 1500;
			int TurnArc = 500;
			motor[imeLeft] = speed;										//Set motor speed to 50
			motor[imeRight] = .8*speed;
			motor[motorLeft] = speed;
			motor[motorRight] = 0.8*speed;
			if(button1_pushed == true){
				button1_pushed = false;             //If button 1 is pushed again, disregard
			}

			if(getMotorEncoder(imeRight) <= -TargetDistance){      //When the motor position <= 3000

				if(button2_pushed == true){
					exer3_state = backward;               //When forwards motion is complete, go backwards
					button2_pushed = false;               //Debounce button 2
					}else{
						exer3_state = stopped;              //If no other input, set state to stopped

						button1_pushed = false;             //Debounce button1
				}

				resetMotorEncoder(imeRight);
			}
			button1_pushed = false;
			break;

			case backward:


			motor[imeLeft] = -2*speed;										//Set motor speed to 50
			motor[imeRight] = 2*speed;
		  motor[motorLeft] = -speed;
			motor[motorRight] = speed;                      //Spin motor backwards
			if(button2_pushed == true){
				button2_pushed = false;                 //If button 2 is pushed again, disregard
			}

			if(getMotorEncoder(imeRight) >= TurnArc){     //Spin until motor position is -3000
				if(button1_pushed == true){
					exer3_state = forward;                //When backwards motion complete, go forwards
					button1_pushed = false;               //Debounce button 1
				}else{
					exer3_state = stopped;                //If no other input, set state to stop
				}
				resetMotorEncoder(imeRight);
			}
			button2_pushed = false;                   //Debounce button2
			break;

		case winch:
		writeDebugStream("case winch!");
			motor[winch] = -127;
			wait1Msec(3400); //
			motor[winch] = 127;
			wait1Msec(3200);
			motor[winch] = 0;
			winchswitch_pushed = false;
			exer3_state = stopped;

			break;
		}



	}//end while

}//end exercse_3


task main()
{
	button1_pushed = button2_pushed = false;
//Branchtest
	switch (EXERCISE_NUMBER)
	{
	case 1:
		RobotOperation();
		break;
	default: //should never get here.
	} // end switch

}// end main
