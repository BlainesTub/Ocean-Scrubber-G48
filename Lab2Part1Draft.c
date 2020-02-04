#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  button1,        sensorTouch)
#pragma config(Sensor, dgtl2,  button2,        sensorTouch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           motor1,        tmotorVex393_HBridge, openLoop, encoderPort, I2C_1)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// WHEN YOU FINISH EACH EXERCISE, INCREMENT THIS VALUE
#define EXERCISE_NUMBER 	1

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
	enum T_MotorState {
		MotorOn = 1,
		MotorOff = 0
	};
	resetMotorEncoder(motor1);               //Zero the motor encoder
	int MotorPos = getMotorEncoder(motor1); //Motor Position
	T_MotorState MotorState = MotorOff;

  while(true)
  {
    monitorInput();

		  /* INSERT CODE HERE
		  * - Make sure EXERCISE_NUMBER is set to 2
		  */


		  switch(MotorState){
		  	case MotorOff:
		  		motor[motor1] = 0;
		  		if(button1_pushed){
		  			MotorState = MotorOn;
		  			button1_pushed = false;
		  		}
		  		break;


		  	case MotorOn:
		  		//Turn the motor on
		  		while(MotorPos <= 627){    //Run until the encoder reads 627 or greater
		  			motor[motor1] = 50;
		  		}
		  		MotorState = MotorOff;
		  		break;
					default:
				}






    }// end while

} // end exercise_2

void exercise_3()
{
	while(true)
	{
	  monitorInput();


      /* INSERT CODE HERE
      * - make sure EXERCISE_NUMBER is set to 3
		  */


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
