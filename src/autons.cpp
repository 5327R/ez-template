#include "main.h"
#define swing_l(x)                                         \
  do                                                       \
  {                                                        \
    chassis.set_swing_pid(ez::LEFT_SWING, x, SWING_SPEED); \
  } while (0)
#define swingl_s(x, y)                           \
  do                                             \
  {                                              \
    chassis.set_swing_pid(ez::LEFT_SWING, x, y); \
  } while (0)
#define swing_r(x)                                          \
  do                                                        \
  {                                                         \
    chassis.set_swing_pid(ez::RIGHT_SWING, x, SWING_SPEED); \
  } while (0)
#define swingr_s(x, y)                            \
  do                                              \
  {                                               \
    chassis.set_swing_pid(ez::RIGHT_SWING, x, y); \
  } while (0)

#define turn(x)                          \
  do                                     \
  {                                      \
    chassis.set_turn_pid(x, TURN_SPEED); \
  } while (0)
#define turn_s(x, y)            \
  do                            \
  {                             \
    chassis.set_turn_pid(x, y); \
  } while (0)
#define drive(x)                                 \
  do                                             \
  {                                              \
    chassis.set_drive_pid(x, DRIVE_SPEED, true); \
  } while (0)
#define drive_s(x, y)                  \
  do                                   \
  {                                    \
    chassis.set_drive_pid(x, y, true); \
  } while (0)
#define complete()        \
  do                      \
  {                       \
    chassis.wait_drive(); \
  } while (0)

/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////

const int DRIVE_SPEED = 100; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants()
{
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 15, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 1, 0, 6.7, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 1, 0, 6.7, 0);
  chassis.set_pid_constants(&chassis.turnPID, 7, 0, 59, 15); // 10 0 75
  chassis.set_pid_constants(&chassis.swingPID, 10, 0, 75, 0);
}

void exit_condition_defaults()
{
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition()
{
  chassis.set_exit_condition(chassis.turn_exit, 15, 3, 100, 7, 200, 500);
  chassis.set_exit_condition(chassis.swing_exit, 15, 3, 100, 7, 200, 500);
  chassis.set_exit_condition(chassis.drive_exit, 15, 50, 100, 150, 200, 500);
}

// Custom Autons
// ---------------------------------------------------------------------------------------------------------------------
void testAuton()
{
  drive(24);
  complete();

  turn(90);
  complete();

  drive(24);
  complete();

  turn(270);
  complete();

  drive(24);
  complete();

  turn(180);
  complete();

  drive(24);
  complete();

  turn(0);
  complete();
}

void oppsteal()
{
  chassis.set_swing_pid(ez::RIGHT_SWING, -45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(17, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::LEFT_SWING, 0, 127);
  pros::delay(200);
  intake.move(127);
  chassis.wait_drive();

  chassis.set_drive_pid(-3, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_drive_pid(11, 127, true);
  chassis.wait_drive();

  intake.move(0);

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

  intake.move(-127);
  chassis.set_drive_pid(10, DRIVE_SPEED, true);
  chassis.wait_drive();
  pros::delay(500);

  chassis.set_drive_pid(-4, DRIVE_SPEED, true);
  chassis.wait_drive();
  intake.move(0);

  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();

  horizontalFlaps.set_value(true);
  chassis.set_drive_pid(-20, 127, false);
  chassis.wait_drive();

  horizontalFlaps.set_value(false);
}

void descore()
{
  verticalFlap.set_value(true);
  pros::delay(500);
  intake.move(127);
  chassis.set_turn_pid(60, 127); // swings out of start position
  chassis.wait_drive();

  chassis.set_drive_pid(16, DRIVE_SPEED, true); // drives 18 inches toward goal
  chassis.wait_drive();

  intake.move(-127);
  pros::delay(700);
  intake.move(0);

  chassis.set_turn_pid(30, 127); // lines up with goal to score
  chassis.wait_drive();

  verticalFlap.set_value(false);

  chassis.set_drive_pid(30, 127, false); // second push
  chassis.wait_drive();

  chassis.set_swing_pid(ez::LEFT_SWING, 0, 127); // swings out of start position
  chassis.wait_drive();

  chassis.set_drive_pid(-7, 127, false); // second push
  chassis.wait_drive();

  chassis.set_drive_pid(14, 127, false); // second push
  chassis.wait_drive();

  chassis.set_drive_pid(-10, 127, false); // second push
  chassis.wait_drive();

  chassis.set_turn_pid(-75, 127); // lines up with goal to score
  chassis.wait_drive();

  intake.move(127);
  chassis.set_drive_pid(46, 127, true); // second push
  chassis.wait_drive();

  chassis.set_swing_pid(ez::LEFT_SWING, 90, 110); // swings out of start position
  chassis.wait_drive();

  intake.move(-127);
  chassis.set_drive_pid(36, 127, true); // second push
  chassis.wait_drive();
  intake.move(0);

  chassis.set_drive_pid(-20, 127, true); // second push
  chassis.wait_drive();
}

void friendlyton()
{
  verticalFlap.set_value(true);
  pros::delay(500);
  verticalFlap.set_value(false);
  intake.move(127);
  chassis.set_swing_pid(ez::LEFT_SWING, 45, 127); // swings out of start position
  chassis.wait_drive();

  chassis.set_drive_pid(18, DRIVE_SPEED, true); // drives 18 inches toward goal
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, 20, 127); // lines up with goal to score
  chassis.wait_drive();

  intake.move(-127); // starts outaking the tribal with intake.
  chassis.wait_drive();

  chassis.set_drive_pid(-5, DRIVE_SPEED, false); // pulls back 5 in
  chassis.wait_drive();

  chassis.set_drive_pid(10, 127, false); // rushes forward
  chassis.wait_drive();

  intake.move(0); // stops intake

  chassis.set_drive_pid(-10, DRIVE_SPEED, false);
  chassis.wait_drive();

  chassis.set_turn_pid(-69, TURN_SPEED); // lines up to center field
  chassis.wait_drive();
  // 47
  chassis.set_drive_pid(47, DRIVE_SPEED, true); // grabs midfield triball
  intake.move(127);
  chassis.wait_drive();
  // 0
  chassis.set_turn_pid(17, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(15, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::LEFT_SWING, 90, 60);
  chassis.wait_drive();
  horizontalFlaps.set_value(true);

  chassis.set_drive_pid(16, 127, true);
  intake.move(-127);
  chassis.wait_drive();

  chassis.set_drive_pid(-10, 127, false);
  chassis.wait_drive();

  chassis.set_drive_pid(10, 127, false);
  chassis.wait_drive();

  intake.move(0);
  horizontalFlaps.set_value(false);

  chassis.set_drive_pid(-5, DRIVE_SPEED, false);
  chassis.wait_drive();

  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(25, DRIVE_SPEED, true);
  intake.move(127);
  chassis.wait_drive();

  chassis.set_turn_pid(100, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(27, DRIVE_SPEED, true);
  intake.move(-127);
  chassis.wait_drive();

  chassis.set_drive_pid(-10, 127, false);
  chassis.wait_drive();

  chassis.set_drive_pid(10, 127, false);
  chassis.wait_drive();

  intake.move(0);

  // chassis.set_swing_pid(ez::LEFT_SWING, 90, SWING_SPEED);
  // chassis.wait_drive();

  // intake.move(127);
  // chassis.wait_drive();
}

void oppton()
{
  chassis.set_swing_pid(ez::RIGHT_SWING, -45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(17, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::LEFT_SWING, 0, 127);
  pros::delay(200);
  intake.move(127);
  chassis.wait_drive();

  chassis.set_drive_pid(-3, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_drive_pid(10, 127, true);
  chassis.wait_drive();

  intake.move(0);

  chassis.set_swing_pid(ez::LEFT_SWING, -45, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(-23, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::LEFT_SWING, -90, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(-36, DRIVE_SPEED, true);
  chassis.wait_drive();
}

// void skillsProg()
// {
//   // open blocker
//   blocker.set_value(true);
//   pros::delay(1000); // wait for blocker to open
//   // turn on slapper for 30 sec
//   slapper.move(127);
//   pros::delay(35000);

//   // run intake for 0.5 seconds as warning
//   intake.move(127);
//   pros::delay(500);
//   intake.move(0);
//   // stop slapper
//   slapper.move(0);
//   blocker.set_value(false);

//   // -------------------- AFTER MATCH-LOADING -------------------- //
//   // re-calibrate imu after lineup with
//   swing_l(-45);
//   complete();
//   chassis.set_angle(-42);
//   // intake.move(127);

//   // start movement
//   swing_l(10);
//   complete();
//   drive(10);
//   pros::delay(250);
//   swing_r(0);

//   slapper.set_brake_mode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_HOLD);
//   slapper.move(127);
//   pros::delay(650);
//   slapper.move(0);

//   drive_s(65, 75);
//   complete();
//   slapper.set_brake_mode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_COAST);

//   swing_r(-45);
//   complete();

//   drive(24);
//   pros::delay(500);
//   swing_r(-90);
//   complete();

//   intake.move(127);
//   drive(12);
//   pros::delay(500);
//   drive(-6);
//   pros::delay(500);
//   swing_r(30);
//   complete();
//   intake.move(0);

//   drive(-38);
//   complete();

//   swing_r(90);
//   complete();

//   drive(-20);
//   complete();

//   turn(180);
//   complete();

//   // -------------------- FINAL PUSHES INTO GOAL -------------------- //
//   intake.move(0);
//   horizontalFlaps.set_value(true);

//   drive(-30);
//   complete();
//   horizontalFlaps.set_value(false);
//   drive(25);
//   complete();
//   turn(270);
//   complete();
//   drive(20);
//   complete();
//   turn(215);
//   complete();
//   horizontalFlaps.set_value(true);
//   drive_s(-22, 127);
//   pros::delay(400);
//   swingl_s(180, 127);
//   pros::delay(400);
//   drive_s(-10, 127);
//   complete();
//   drive_s(10, 127);
//   complete();
//   drive_s(-10, 127);
//   complete();
//   drive_s(10, 127);
// }

// Simple Examples
// ---------------------------------------------------------------------------------------------------------------------

///
// Drive Example
///
void drive_example()
{
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches
  default_constants();

  // Drive forward and back
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

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
void turn_example()
{
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
void drive_and_turn()
{
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
void wait_until_change_speed()
{
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
void swing_example()
{
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive

  // chassis.set_swing_pid(ez::RIGHT_SWING, -90, SWING_SPEED);
  // chassis.wait_drive();

  // chassis.set_drive_pid(24, DRIVE_SPEED, true);
  // chassis.wait_until(12);

  // chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  // chassis.wait_drive();
}

///
// Auto that tests everything
///
void combining_movements()
{
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
void tug(int attempts)
{
  for (int i = 0; i < attempts - 1; i++)
  {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered)
    {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else
    {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees.
// If interfered, robot will drive forward and then attempt to drive backwards.
void interfered_example()
{
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  if (chassis.interfered)
  {
    tug(3);
    return;
  }

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
}

// . . .
// Make your own autonomous functions here!
// . . .