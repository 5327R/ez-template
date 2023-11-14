#include "main.h"
#define swing_l(x) do { chassis.set_swing_pid(ez::LEFT_SWING, x, SWING_SPEED); } while(0)
#define swingl_s(x, y) do { chassis.set_swing_pid(ez::LEFT_SWING, x, y); } while(0)
#define swing_r(x) do { chassis.set_swing_pid(ez::RIGHT_SWING, x, SWING_SPEED); } while(0)
#define swingr_s(x, y) do { chassis.set_swing_pid(ez::RIGHT_SWING, x, y); } while(0)

#define turn(x) do { chassis.set_turn_pid(x, TURN_SPEED); } while(0)
#define turn_s(x, y) do { chassis.set_turn_pid(x, y); } while(0)
#define drive(x) do { chassis.set_drive_pid(x, DRIVE_SPEED, true); } while(0)
#define drive_s(x, y) do { chassis.set_drive_pid(x, y, true); } while(0)
#define complete() do { chassis.wait_drive(); } while(0)

/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 100; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 20, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 1, 0, 6.7, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 1, 0, 6.7, 0);
  chassis.set_pid_constants(&chassis.turnPID, 10, 0, 75, 15);
  chassis.set_pid_constants(&chassis.swingPID, 10, 0, 75, 0);
}


void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 15, 3, 100, 7, 200, 500);
  chassis.set_exit_condition(chassis.swing_exit, 15, 3, 100, 7, 200, 500);
  chassis.set_exit_condition(chassis.drive_exit, 15, 50, 100, 150, 200, 500);
}

void oppsteal() {
  chassis.set_swing_pid(ez::RIGHT_SWING, -45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(17, DRIVE_SPEED, true);
  chassis.wait_drive();
  
  chassis.set_swing_pid(ez::LEFT_SWING, 0, 127);
  pros::delay(200);
  intake_motor.move(127);
  chassis.wait_drive();

  chassis.set_drive_pid(-3, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_drive_pid(11, 127, true);
  chassis.wait_drive();

  intake_motor.move(0);

  chassis.set_swing_pid(ez::LEFT_SWING, -50, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(-20, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, 0, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(20, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(40, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  intake_motor.move(-127);
  chassis.set_drive_pid(10, DRIVE_SPEED, true);
  chassis.wait_drive();
  pros::delay(500);

  chassis.set_drive_pid(-4, DRIVE_SPEED, true);
  chassis.wait_drive();
  intake_motor.move(0);

  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();

  flaps.set_value(true);
  chassis.set_drive_pid(-20, 127, false);
  chassis.wait_drive();

  flaps.set_value(false);

}

void friendlyton() {
  chassis.set_swing_pid(ez::LEFT_SWING, 45, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(17, DRIVE_SPEED, true);
  chassis.wait_drive();
  
  chassis.set_swing_pid(ez::RIGHT_SWING, 0, 127);
  pros::delay(200);
  intake_motor.move(127);
  chassis.wait_drive();

  chassis.set_drive_pid(-3, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_drive_pid(8, 127, true);
  chassis.wait_drive();

  intake_motor.move(0);

  chassis.set_drive_pid(-7, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(-69, TURN_SPEED);
  chassis.wait_drive();
  //47
  chassis.set_drive_pid(47, DRIVE_SPEED, true);
  intake_motor.move(-127);
  chassis.wait_drive();
  //0
  chassis.set_turn_pid(17, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(17, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::LEFT_SWING, 90, 60);
  chassis.wait_drive();

  chassis.set_drive_pid(16, 127, true);
  intake_motor.move(127);
  chassis.wait_drive();

  chassis.set_drive_pid(-10, 127, true);
  chassis.wait_drive();

  chassis.set_drive_pid(10, 127, true);
  chassis.wait_drive();

  intake_motor.move(0);

  chassis.set_drive_pid(-5, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(25, DRIVE_SPEED, true);
  intake_motor.move(-127);
  chassis.wait_drive();

  chassis.set_turn_pid(100, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(27, DRIVE_SPEED, true);
  intake_motor.move(127);
  chassis.wait_drive();

  chassis.set_drive_pid(-10, 127, true);
  chassis.wait_drive();

  chassis.set_drive_pid(10, 127, true);
  chassis.wait_drive();

  intake_motor.move(0);

  // chassis.set_swing_pid(ez::LEFT_SWING, 90, SWING_SPEED);
  // chassis.wait_drive();

  // intake_motor.move(127);
  // chassis.wait_drive();


}

void oppton() {
  chassis.set_swing_pid(ez::RIGHT_SWING, -45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(17, DRIVE_SPEED, true);
  chassis.wait_drive();
  
  chassis.set_swing_pid(ez::LEFT_SWING, 0, 127);
  pros::delay(200);
  intake_motor.move(127);
  chassis.wait_drive();

  chassis.set_drive_pid(-3, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_drive_pid(10, 127, true);
  chassis.wait_drive();

  intake_motor.move(0);

  chassis.set_swing_pid(ez::LEFT_SWING, -45, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(-23, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::LEFT_SWING, -90, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(-36, DRIVE_SPEED, true);
  chassis.wait_drive();


  
}

void skillsProg() {
  
  
  // // open blocker
  // blocker.set_value(true);
  // pros::delay(1000);
  // // turn on slapper for 5 sec
  // slapper_motor.move(127);
  // pros::delay(3000);

  // slapper_motor.move(0);
  // blocker.set_value(false);

  // re-calibrate imu
  drive_s(-7, 50);
  complete();
  pros::delay(500); 
  chassis.set_angle(-42);

  // run intake for 0.5 seconds as warning
  intake_motor.move(127);
  pros::delay(500); 
  intake_motor.move(0);


  // start movement
  swing_l(0);
  complete();
  

  slapper_motor.set_brake_mode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_HOLD);
  slapper_motor.move(127);
  pros::delay(650);
  slapper_motor.move(0);

  drive(72);
  complete();
  slapper_motor.set_brake_mode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_COAST);
}

///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches
  default_constants();

  // Drive forward and back
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  pros::delay(500);

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  // chassis.set_drive_pid(-24, 127);
  // chassis.wait_drive();

  // chassis.set_drive_pid(-24, 127);
  // chassis.wait_drive();


  // // Turn
  // chassis.set_turn_pid(90, TURN_SPEED);
  // chassis.wait_drive();

  // chassis.set_turn_pid(45, TURN_SPEED);
  // chassis.wait_drive();

  // chassis.set_turn_pid(0, TURN_SPEED);
  // chassis.wait_drive();

  // // Swing
  // chassis.set_swing_pid(ez::LEFT_SWING, 90, 127);
  // chassis.wait_drive();

  // chassis.set_drive_pid(24, DRIVE_SPEED, true);
  // chassis.wait_until(12);

  // chassis.set_swing_pid(ez::LEFT_SWING, 0, 127);
  // chassis.wait_drive();
}



///
// Turn Example
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at


  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
}



///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // wait_until will wait until the robot gets to a desired position


  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_until(-6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();
}




///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive

  //chassis.set_swing_pid(ez::RIGHT_SWING, -90, SWING_SPEED);
  //chassis.wait_drive();

  // chassis.set_drive_pid(24, DRIVE_SPEED, true);
  // chassis.wait_until(12);

  // chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  // chassis.wait_drive();
}



///
// Auto that tests everything
///
void combining_movements() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Interference example
///
void tug (int attempts) {
  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees. 
// If interfered, robot will drive forward and then attempt to drive backwards. 
void interfered_example() {
 chassis.set_drive_pid(24, DRIVE_SPEED, true);
 chassis.wait_drive();

 if (chassis.interfered) {
   tug(3);
   return;
 }

 chassis.set_turn_pid(90, TURN_SPEED);
 chassis.wait_drive();
}



// . . .
// Make your own autonomous functions here!
// . . .