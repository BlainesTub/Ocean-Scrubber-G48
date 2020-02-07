#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  button1,        sensorTouch)
#pragma config(Sensor, dgtl2,  button2,        sensorTouch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           motor1,        tmotorVex393_HBridge, openLoop, encoderPort, I2C_1)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// WHEN YOU FINISH EACH EXERCISE, INCREMENT THIS VALUE
#define EXERCISE_NUMBER 	3

bool button1_pushed; //flag to store button1 input
bool button2_pushed; //flag to store button2 input


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
}

void exercise_1()
{
	// Define tag for enumerated type for exercise 1
	enum T_exercise1_state {
		MOTOR_STOP = 0,
		MOTOR_RUNNING
	};

	// Declare variable to hold state, intialize to MOTOR_STOP state.
	T_exercise1_state exercise1_state = MOTOR_STOP;

	while(true)
	{
		// This function updates the button1_pushed and button2_pushed flags.
		monitorInput();

		// Switch the states.
		switch(exercise1_state) {

			// Code for MOTOR_STOP state:
		case MOTOR_STOP:
			// Turn motor off.
			motor[motor1] = 0;
			if ( button1_pushed ) {
				// If button1 pushed, change to the MOTOR_RUNNING state.
				exercise1_state = MOTOR_RUNNING;
				// Clear flag to indicate button 1 processed.
				button1_pushed = false;
			}
			break;
		case MOTOR_RUNNING:
			// Turn motor on.
			motor[motor1] = 50;
			if (button2_pushed) {
				// If button 2 pushed, transition to MOTOR_STOP state.
				exercise1_state = MOTOR_STOP;
				// Clear flag to indicate that button 2 processed.
				button2_pushed = false;
			}
			break;
		default:
		}

	}//end while
}

void exercise_2()
{
	enum T_test_state {
		state1 = 0,
		state2,
		state3
	};

	T_test_state test_state = state1;

	while(true)
	{
		monitorInput();

		/* INSERT CODE HERE
		* - Make sure EXERCISE_NUMBER is set to 2
		*/
		switch(test_state){

		case state1:

			resetMotorEncoder(motor1);
			motor[motor1] = 0;
			if(button1_pushed == true){
				test_state = state2
				button1_pushed = false;
			}
			break;

		case state2:

			motor[motor1] = 50;
			if(getMotorEncoder(motor1) >= 627){

				test_state = state1;

			}
			if(button1_pushed == true){
				button1_pushed = false;
			}
			break;


		}


	}// end while

} // end exercise_2

void exercise_3()
{
	enum T_test_state{
		stopped = 0,
		forward,
		backward,
	};
	T_test_state exer3_state = stopped;
	while(true)
	{
		monitorInput();


		/* INSERT CODE HERE
		* - make sure EXERCISE_NUMBER is set to 3
		*/

		switch(exer3_state){

		case stopped:

			motor[motor1] = 0;
			resetMotorEncoder(motor1);
			if(button1_pushed == true){
				exer3_state = forward;
				button1_pushed = false;
			}
			if(button2_pushed == true){
				exer3_state = backward;
				button2_pushed = false;
			}

			break;

		case forward:
			//resetMotorEncoder(motor1);
			motor[motor1] = 50;

			if(button1_pushed == true){
				button1_pushed = false;
			}

		/*	if(button2_pushed == true){
				//check this out
				exer3_state = backward;
			}*/

			if(getMotorEncoder(motor1) >= 3000){

				if(button2_pushed == true){
					exer3_state = backward;
					button2_pushed = false;
					}else{
						exer3_state = stopped;

						button1_pushed = false;
				}

				ResetMotorEncoder(motor1);
			}
			button1_pushed = false;
			break;

			case backward:

			motor[motor1] = -50;
			if(button2_pushed == true){
				button2_pushed = false;
			}

			if(getMotorEncoder(motor1) <= -3000){
				if(button1_pushed == true){
					exer3_state = forward;
					button1_pushed = false;
				}else{
					exer3_state = stopped;
				}
				resetMotorEncoder(motor1);
			}
			button2_pushed = false;
			break;

		}

	}//end while

}//end exercse_3


task main()
{
	button1_pushed = button2_pushed = false;

	switch (EXERCISE_NUMBER)
	{
	case 1:
		exercise_1();
		break;
	case 2:
		exercise_2();
		break;
	case 3:
		exercise_3();
		break;
	default: //should never get here.
	} // end switch

}// end main
