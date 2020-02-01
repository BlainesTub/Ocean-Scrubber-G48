// Basic simulate imprecise measurement code in RobotC

// Upper and lower of range of values to estimate.
const int min_value = 0;
const int max_value = 100;

// Experiment parameters
int total_trials = 1000;

// Storage of number of guesses.
int total_meas = 0;
int correct_guess = 0;

/**********************************************************
** int resolve_measurement( int meas_point )
** Resolve Measurement at set point.
** Inputs:
**   meas_point	Set point of measurment
**              If meas_point is a non-negative number, the
**              function returns the value below.  If meas_point
**              is negative, the function generates a new random
**              value and returns this value.  This value should
**              only be used for debugging purposes.
** Outputs: (if input is non-negative)
**   0						If value is equal to meas_point
**   -1          If value is greater than meas_point
**   1           If true value is less than meas_pont
** Global Interaction:
**   Keeps track of number of measurements in total_meas
**
**********************************************************/
int resolve_measurement( int meas_point ) {

	// Storage of random number.
	//   static means value is maintained between function calls.
	static int true_value;

	// Check if new value is desired...
	if ( meas_point < 0 ) {
		// Random number parameter
		int temp_number = rand();

		int range = max_value - min_value;

		// Kludge to handle fact that RobotC does not have unsigned ints.
		temp_number = ( temp_number < 0 ) ? -1 * temp_number : temp_number;

		// Limit value to range.
		true_value = temp_number % range + min_value;

		return(true_value);
	}

	// Increment total number of guesses.
	total_meas++;

	if ( true_value > meas_point ) {

		// Return -1 if true value bigger than set point.
		return(-1);

		} else if ( true_value < meas_point ) {

		// Return 1 if true value less than set point
		return(1);

		} else {

		// Return 0 if measurement point matches
		correct_guess++;
		return(0);

	}
}

task main()
{
	// Run multiple trials and keep track of number of trials.
	int current_trial;

	// Storage of true value. USE ONLY FOR DEBUGGING.
	int true_value;

	// For each trial
	for ( current_trial = 1; current_trial <= total_trials ; current_trial++ ) {

		// Generate new value to measure
		true_value = resolve_measurement(-1);

		// Storage of guessed value
		int value;

		// Storage of result of last measurement
		int result;

		// Range to search for true value
		int min_v = min_value;
		int max_v = max_value;

		// Modify the code starting here.

		// Initialization here.
		// Current measurement point set to lowest value.
		int current_meas_point = min_v;

		// Estimation code here.

		// Start a loop
		do {

		  // Take a measurement at the current measurement point
			result = resolve_measurement( current_meas_point );

			// Check if current measurmeent point is too low.
			if ( result == - 1 ) {

			  // Our measurement point is too low,
			  //  add 1 to current measurment point
			  current_meas_point = current_meas_point + 1;
		  } else {

		    // Measurement is not too low,
		    //  set estimated value to to current measurement point.
		    value = current_meas_point;
		  }

		  // Loop until result == 0, indicating current measurement point is
		  //   the true value.
		} while( result != 0 );


		writeDebugStream("%d. Guess = %d\tTrue value = %d.\n",current_trial,value,true_value);
		// All modified code should be above this line.

		// Write output to debug stream.
		// Keep this line for evaluation of performance.
		writeDebugStream("%d trials and %d guesses with %d correct\n",current_trial,total_meas,correct_guess);

	}

	// Wait for an infinite amount of time.
	// Keeps the Debug stream open so we can read the output of the program.
	while(1);
}
