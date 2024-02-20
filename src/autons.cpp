#include "main.h"
#define swing_l(x)                                                             \
  do {                                                                         \
    chassis.pid_swing_set(ez::LEFT_SWING, x, SWING_SPEED);                     \
  } while (0)
#define swingl_s(x, y)                                                         \
  do {                                                                         \
    chassis.pid_swing_set(ez::LEFT_SWING, x, y);                               \
  } while (0)
#define swing_r(x)                                                             \
  do {                                                                         \
    chassis.pid_swing_set(ez::RIGHT_SWING, x, SWING_SPEED);                    \
  } while (0)
#define swingr_s(x, y)                                                         \
  do {                                                                         \
    chassis.pid_swing_set(ez::RIGHT_SWING, x, y);                              \
  } while (0)

#define turn(x)                                                                \
  do {                                                                         \
    chassis.pid_turn_set(x, TURN_SPEED);                                       \
  } while (0)
#define turn_s(x, y)                                                           \
  do {                                                                         \
    chassis.pid_turn_set(x, y);                                                \
  } while (0)
#define drive(x)                                                               \
  do {                                                                         \
    chassis.pid_drive_set(x, DRIVE_SPEED, true);                               \
  } while (0)
#define drive_s(x, y)                                                          \
  do {                                                                         \
    chassis.pid_drive_set(x, y, true);                                         \
  } while (0)
#define complete()                                                             \
  do {                                                                         \
    chassis.pid_wait();                                                        \
  } while (0)
#define TILE 24

/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////

const int DRIVE_SPEED =
    100; // This is 110/127 (around 87% of max speed).  We don't suggest making
         // this 127. If this is 127 and the robot tries to heading correct,
         // it's only correcting by making one side slower.  When this is 87%,
         // it's correcting by making one side faster and one side slower,
         // giving better heading correction.
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier
// game objects, or with lifts up vs down. If the objects are light or the cog
// doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.pid_heading_constants_set(5, 0, 30, 0);
  chassis.pid_drive_constants_forward_set(1, 0, 6.7, 0);
  chassis.pid_drive_constants_backward_set(1, 0, 6.7, 0);
  chassis.pid_turn_constants_set(5, 0, 48, 15); // 10 0 75
  chassis.pid_swing_constants_set(10, 0, 120, 0);

  chassis.slew_drive_constants_set(7_in, 80);
}

void exit_condition_defaults() {
  chassis.pid_turn_exit_condition_set(100, 3, 500, 7, 500, 500);
  chassis.pid_swing_exit_condition_set(100, 3, 500, 7, 500, 500);
  chassis.pid_drive_exit_condition_set(80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  chassis.pid_turn_exit_condition_set(100, 3, 400, 7, 200, 500);
  chassis.pid_swing_exit_condition_set(100, 3, 400, 7, 200, 500);
  chassis.pid_drive_exit_condition_set(100, 50, 200, 150, 200, 500);
}

// Custom Autons
// ---------------------------------------------------------------------------------------------------------------------
void testAuton() {
  drive(20);
  complete();

  turn(90);
  complete();

  drive(20);
  complete();

  turn(270);
  complete();

  drive(20);
  complete();

  turn(180);
  complete();

  drive(20);
  complete();

  turn(0);
  complete();
}

void oppsteal() {
  chassis.pid_swing_set(ez::RIGHT_SWING, -45, SWING_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(17, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0, 127);
  pros::delay(200);
  intake.move(127);
  chassis.pid_wait();

  chassis.pid_drive_set(-3, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(11, 127, true);
  chassis.pid_wait();

  intake.move(0);

  chassis.pid_swing_set(ez::LEFT_SWING, -50, 127);
  chassis.pid_wait();

  chassis.pid_drive_set(-20, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0, 127);
  chassis.pid_wait();

  chassis.pid_turn_set(20, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(40, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(0, TURN_SPEED);
  chassis.pid_wait();

  intake.move(-127);
  chassis.pid_drive_set(10, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(500);

  chassis.pid_drive_set(-4, DRIVE_SPEED, true);
  chassis.pid_wait();
  intake.move(0);

  chassis.pid_turn_set(-90, TURN_SPEED);
  chassis.pid_wait();

  horizontalFlaps.set_value(true);
  chassis.pid_drive_set(-20, 127, false);
  chassis.pid_wait();

  horizontalFlaps.set_value(false);
}

void descore() {
  verticalFlap.set_value(true);
  pros::delay(500);
  intake.move(127);
  chassis.pid_turn_set(60, 127); // swings out of start position
  chassis.pid_wait();

  chassis.pid_drive_set(16, DRIVE_SPEED, true); // drives 18 inches toward goal
  chassis.pid_wait();

  chassis.pid_turn_set(-10, 100); // lines up with goal to score
  chassis.pid_wait();

  verticalFlap.set_value(false);

  chassis.pid_turn_set(30, 127); // lines up with goal to score
  chassis.pid_wait();

  intake.move(-127);
  pros::delay(700);

  chassis.pid_drive_set(30, 127, false); // second push
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0, 127); // swings out of start position
  chassis.pid_wait();

  chassis.pid_drive_set(-7, 127, false); // second push
  chassis.pid_wait();

  chassis.pid_drive_set(14, 127, false); // second push
  chassis.pid_wait();

  chassis.pid_drive_set(-10, 127, false); // second push
  chassis.pid_wait();

  chassis.pid_turn_set(-75, 127); // lines up with goal to score
  chassis.pid_wait();

  intake.move(0);
  intake.move(127);

  chassis.pid_drive_set(46, 127, true); // second push
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 90,
                        100); // swings out of start position
  chassis.pid_wait();

  intake.move(-127);
  chassis.pid_drive_set(36, 127, true); // second push
  chassis.pid_wait();
  intake.move(0);

  chassis.pid_drive_set(-20, 127, true); // second push
  chassis.pid_wait();
}
void nakulton() {
  // modified_exit_condition();
  chassis.drive_angle_set(-90);
  // intake first triball
  intake.move(127);
  verticalFlap.set_value(true);
  pros::delay(200);
  verticalFlap.set_value(false);

  // push matchload to goal
  drive_s(-28, 80);
  pros::delay(700);
  swingl_s(-120, 110);
  pros::delay(300);
  drive_s(-26, 100);
  pros::delay(700);
  swingl_s(-180, 110);
  complete();

  drive_s(5, 127);
  pros::delay(300);

  turn_s(-340, 127);
  complete();

  intake.move(-127);
  pros::delay(700);
  intake.move(0);

  turn_s(-170, 127);
  complete();
  drive_s(-18, 127);
  complete();

  // drive_s(10, 127); //second push
  // complete();

  // drive_s(-14, 127);
  // complete();

  swingl_s(-75, 100); // grab md
  complete();

  intake.move(127);
  drive_s(46, 127);
  complete();
  intake.move(0);

  turn(50);
  complete();

  intake.move(-127);
  pros::delay(500);
  drive(5);
  complete();
  intake.move(0);

  turn(-20);
  complete();

  intake.move(127);
  drive(20);
  complete();
  swingr_s(-90, 110);
  complete();

  horizontalFlaps.set_value(true);

  drive_s(-48, 127);
}
void friendlyton() {
  // modified_exit_condition();
  chassis.drive_angle_set(-90);
  // intake first triball
  intake.move(127);
  verticalFlap.set_value(true);
  pros::delay(200);
  verticalFlap.set_value(false);

  // push matchload to goal
  drive_s(-28, 80);
  complete();
  swingl_s(-120, 110);
  complete();
  drive_s(-26, 100);
  complete();
  swingl_s(-180, 110);
  complete();

  drive_s(5, 127);
  complete();

  turn_s(-340, 127);
  complete();

  intake.move(-127);
  pros::delay(700);
  intake.move(0);

  turn_s(-170, 127);
  complete();
  drive_s(-18, 127);
  complete();

  // drive_s(10, 127); //second push
  // complete();

  // drive_s(-14, 127);
  // complete();

  swingl_s(-45, 100); // grab md
  complete();

  intake.move(127);
  drive_s(52, 127);
  complete();

  swingr_s(-90, 127);
  complete();

  drive_s(-12, 127);
  complete();

  drive_s(5, 127);
  complete();

  turn_s(90, 127);
  complete();

  intake.move(-127);
  pros::delay(300);
  drive_s(24, 127);
  complete();
  intake.move(0);

  drive(-10);

  // swingl_s(-100, 127);
  // complete();

  // intake.move(127);
  // drive_s(10, 127);
  // complete();

  // turn(45);
  // pros::delay(500);
  // drive_s(10, 127);
  // pros::delay(100);
  // intake.move(-127);
  // swingl_s(90, 127);
  // pros::delay(200);
  // drive_s(24, 127);
}

void oppton() {
  // intake deployment
  verticalFlap.set_value(true);
  pros::delay(500);
  verticalFlap.set_value(false);
  intake.move(127);

  // 3 tiles forward
  drive(2 * TILE);
  complete();

  // turn to opp goal
  turn(-50);
  complete();

  // deposit triball in front of opp goal
  intake.move(-127);
  pros::delay(700);
  intake.move(0);

  // grab mid triball
  complete();
  intake.move(127);
  turn(90);
  complete();
  swing_r(0);
  complete();
  pros::delay(100);

  // flaps over barrier
  turn(-90);
  complete();
  horizontalFlaps.set_value(true);
  drive_s(-0.6 * TILE, 127);
  complete();
  // chassis.drive_angle_set(-90);
  drive(0.6 * TILE);
  horizontalFlaps.set_value(false);
  complete();
  turn(0);
  complete();

  // descore
  drive(-0.7 * TILE);
  complete();
  swing_r(90);
  complete();
  drive(-1.3 * TILE);
  complete();
  turn(180);
  complete();
  drive(0.5 * TILE);
  complete();
  verticalFlap.set_value(true);
  swingr_s(90, 100);
  complete();
  turn(100);
  complete();
  intake.move(-127);
  drive(1.55 * TILE);
  complete();
}

void oppton_noflaps() {
  // intake deployment
  verticalFlap.set_value(true);
  pros::delay(500);
  verticalFlap.set_value(false);
  intake.move(127);

  // 3 tiles forward
  drive(2 * TILE);
  complete();

  // turn to opp goal
  turn(-50);
  complete();

  // deposit triball in front of opp goal
  intake.move(-100);
  pros::delay(700);
  intake.move(0);

  // grab mid triball
  intake.move(127);
  turn_s(90, 80);
  complete();
  swing_r(0);
  complete();
  pros::delay(100);

  // descore
  drive(-0.7 * TILE);
  complete();
  swing_r(90);
  complete();
  drive(-1.3 * TILE);
  complete();
  turn(180);
  complete();
  drive(0.5 * TILE);
  complete();
  verticalFlap.set_value(true);
  swingr_s(90, 100);
  complete();
  turn(100);
  complete();
  intake.move(-127);
  drive(37.2);
  complete();
}

void skillsProg() {

  // turn on slapper for 30 sec
  slapper.move(127);
  pros::delay(1000);

  // run intake for 0.5 seconds as warning
  intake.move(127);
  pros::delay(500);
  intake.move(0);
  // stop slapper
  slapper.move(0);

  // -------------------- AFTER MATCH-LOADING -------------------- //
  // re-calibrate imu after lineup with
  swing_l(-45);
  complete();
  // chassis.drive_angle_set(-42);
  // intake.move(127);

  // start movement
  swing_l(10);
  complete();
  drive(10);
  pros::delay(250);
  swing_r(0);

  slapper.set_brake_modes(pros::motor_brake_mode_e::E_MOTOR_BRAKE_HOLD);
  slapper.move(127);
  pros::delay(650);
  slapper.move(0);

  drive_s(65, 75);
  complete();
  slapper.set_brake_modes(pros::motor_brake_mode_e::E_MOTOR_BRAKE_COAST);

  swing_r(-45);
  complete();

  drive(24);
  pros::delay(500);
  swing_r(-90);
  complete();

  intake.move(127);
  drive(12);
  pros::delay(500);
  drive(-6);
  pros::delay(500);
  swing_r(30);
  complete();
  intake.move(0);

  drive(-38);
  complete();

  swing_r(90);
  complete();

  drive(-20);
  complete();

  turn(180);
  complete();

  // -------------------- FINAL PUSHES INTO GOAL -------------------- //
  intake.move(0);
  horizontalFlaps.set_value(true);

  drive(-30);
  complete();
  horizontalFlaps.set_value(false);
  drive(25);
  complete();
  turn(270);
  complete();
  drive(20);
  complete();
  turn(215);
  complete();
  horizontalFlaps.set_value(true);
  drive_s(-22, 127);
  pros::delay(400);
  swingl_s(180, 127);
  pros::delay(400);
  drive_s(-10, 127);
  complete();
  drive_s(10, 127);
  complete();
  drive_s(-10, 127);
  complete();
  drive_s(10, 127);
}

// Simple Examples
// ---------------------------------------------------------------------------------------------------------------------

///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a
  // slew at the start of drive motions for slew, only enable it when the drive
  // distance is greater then the slew distance + a few inches
  default_constants();

  // Drive forward and back
  chassis.pid_drive_set(24, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(90, TURN_SPEED);
  chassis.pid_wait();

  // chassis.pid_drive_set(-24, 127);
  // chassis.pid_wait();

  // chassis.pid_drive_set(-24, 127);
  // chassis.pid_wait();

  // // Turn
  // chassis.pid_turn_set(90, TURN_SPEED);
  // chassis.pid_wait();

  // chassis.pid_turn_set(45, TURN_SPEED);
  // chassis.pid_wait();

  // chassis.pid_turn_set(0, TURN_SPEED);
  // chassis.pid_wait();

  // // Swing
  // chassis.pid_swing_set(ez::LEFT_SWING, 90, 127);
  // chassis.pid_wait();

  // chassis.pid_drive_set(24, DRIVE_SPEED, true);
  // chassis.pid_wait_until(12);

  // chassis.pid_swing_set(ez::LEFT_SWING, 0, 127);
  // chassis.pid_wait();
}

///
// Turn Example
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at

  chassis.pid_turn_set(90, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(45, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0, TURN_SPEED);
  chassis.pid_wait();
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.pid_drive_set(24, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void pid_wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches, the robot will travel the remaining
  // distance at a max speed of 40
  chassis.pid_drive_set(24, DRIVE_SPEED, true);
  chassis.pid_wait_until(6);
  chassis.pid_speed_max_set(
      40); // After driving 6 inches at DRIVE_SPEED, the robot
           // will go the remaining distance at 40 speed
  chassis.pid_wait();

  chassis.pid_turn_set(45, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches, the robot will travel the remaining
  // distance at a max speed of 40
  chassis.pid_drive_set(-24, DRIVE_SPEED, true);
  chassis.pid_wait_until(-6);
  chassis.pid_speed_max_set(
      40); // After driving 6 inches at DRIVE_SPEED, the robot
           // will go the remaining distance at 40 speed
  chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive

  // chassis.pid_swing_set(ez::RIGHT_SWING, -90, SWING_SPEED);
  // chassis.pid_wait();

  // chassis.pid_drive_set(24, DRIVE_SPEED, true);
  // chassis.pid_wait_until(12);

  // chassis.pid_swing_set(ez::RIGHT_SWING, 0, SWING_SPEED);
  // chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.pid_drive_set(-12, 127, false);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2, 20, false);
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
  chassis.pid_drive_set(24, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90, TURN_SPEED);
  chassis.pid_wait();
}

// . . .
// Make your own autonomous functions here!
// . . .
