#include "autons.hpp"
#include "EZ-Template/util.hpp"
#include "main.h"
#include "pros/motors.h"

#define delay(x) pros::delay(x);
#define dr_s(x, y)                                                             \
  do {                                                                         \
    chassis.pid_drive_set(x, y, false);                                        \
    chassis.pid_wait();                                                        \
  } while (0)

#define dr(x)                                                                  \
  do {                                                                         \
    chassis.pid_drive_set(x, 127, false);                                      \
    chassis.pid_wait();                                                        \
  } while (0)

#define turn(x)                                                                \
  do {                                                                         \
    chassis.pid_turn_set(x, 127, false);                                       \
    chassis.pid_wait();                                                        \
  } while (0)

#define turn_s(x, y)                                                           \
  do {                                                                         \
    chassis.pid_turn_set(x, y, false);                                         \
    chassis.pid_wait();                                                        \
  } while (0)
#define swing_r(x, y, z)                                                       \
  do {                                                                         \
    chassis.pid_swing_set(ez::RIGHT_SWING, x, y, z);                           \
    chassis.pid_wait();                                                        \
  } while (0)
#define swing_l(x, y, z)                                                       \
  do {                                                                         \
    chassis.pid_swing_set(ez::LEFT_SWING, x, y, z);                            \
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
  chassis.pid_heading_constants_set(7, 0, 45);
  chassis.pid_drive_constants_set(12, 0, 60);
  chassis.pid_turn_constants_set(5, 0, 40);
  chassis.pid_swing_constants_set(5, 0, 45);

  chassis.pid_turn_exit_condition_set(100_ms, 2_deg, 250_ms, 5_deg, 750_ms,
                                      750_ms);
  chassis.pid_swing_exit_condition_set(100_ms, 3_deg, 250_ms, 5_deg, 750_ms,
                                       750_ms);
  chassis.pid_drive_exit_condition_set(80_ms, 1_in, 300_ms, 2_in, 500_ms,
                                       500_ms);

  chassis.slew_drive_constants_set(7_in, 80);
}

// Custom Autons
// ---------------------------------------------------------------------------------------------------------------------
void testAuton() { swing_l(90, 100, 0); }

void descore() {
  verticalFlap.set(true);
  delay(500);
  intake.move(127);
  chassis.pid_swing_set(ez::LEFT_SWING, 60, SWING_SPEED);

  chassis.pid_wait();
}

void descore_old() {
  verticalFlap.set(true);
  delay(500);
  intake.move(127);
  chassis.pid_turn_set(60, 127); // swings out of start position
  chassis.pid_wait();

  chassis.pid_drive_set(16, DRIVE_SPEED, true); // drives 18 inches toward goal
  chassis.pid_wait();

  chassis.pid_turn_set(-10, 100); // lines up with goal to score
  chassis.pid_wait();

  verticalFlap.set(false);

  chassis.pid_turn_set(30, 127); // lines up with goal to score
  chassis.pid_wait();

  intake.move(-127);
  delay(700);

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

void oppton() {
  // intake deployment
  verticalFlap.set(true);
  delay(500);
  verticalFlap.set(false);
  intake.move(127);

  // 3 tiles forward
  dr(2 * TILE);

  // turn to opp goal
  turn(-50);

  // deposit triball in front of opp goal
  intake.move(-100);
  delay(700);
  intake.move(0);

  // grab mid triball
  intake.move(127);
  turn_s(90, 80);

  chassis.pid_swing_set(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.pid_wait();
  delay(100);

  // flaps
  turn(-90);
  horizontalFlaps.set(true);
  dr_s(-0.6 * TILE, 127);
  // chassis.drive_angle_set(-90);
  horizontalFlaps.set(false);
  dr(0.6 * TILE);
  turn(0);

  // descore
  dr(-0.7 * TILE);

  chassis.pid_swing_set(ez::RIGHT_SWING, 90, SWING_SPEED, 10);
  chassis.pid_wait();
  dr(-1.3 * TILE);
  turn(180);

  dr(0.5 * TILE);

  verticalFlap.set(true);
  chassis.pid_swing_set(ez::RIGHT_SWING, 90, 100);
  chassis.pid_wait();

  turn(100);

  verticalFlap.set(false);

  intake.move(-127);
  dr(39);
}

void oppton_noflaps() {
  // intake deployment
  verticalFlap.set(true);
  delay(500);
  verticalFlap.set(false);
  intake.move(127);

  // 3 tiles forward
  dr(2 * TILE);

  // turn to opp goal
  turn(-50);

  // deposit triball in front of opp goal
  intake.move(-100);
  delay(700);
  intake.move(0);

  // grab mid triball
  intake.move(127);
  turn_s(90, 80);

  chassis.pid_swing_set(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.pid_wait();
  delay(100);

  // descore
  dr(-0.7 * TILE);

  chassis.pid_swing_set(ez::RIGHT_SWING, 90, SWING_SPEED, 10);
  chassis.pid_wait();
  dr(-1.3 * TILE);
  turn(180);

  dr(0.5 * TILE);

  verticalFlap.set(true);
  chassis.pid_swing_set(ez::RIGHT_SWING, 90, 100);
  chassis.pid_wait();

  turn(100);

  verticalFlap.set(false);

  intake.move(-127);
  dr(37.8);
}

void skills() {
  // STEP 1
  // ------------------------------
  chassis.drive_brake_set(pros::E_MOTOR_BRAKE_HOLD);
  chassis.drive_angle_set(-180);

  chassis.pid_swing_set(e_swing::RIGHT_SWING, -135, 90, 0);
  chassis.pid_wait();
  chassis.pid_swing_set(e_swing::LEFT_SWING, -180, 127,
                        78); // rams both alliance into enemy goal
  chassis.pid_wait();

  turn(-170);
  dr(10);    // drive back after push
  turn(-65); // get matchload angle
  dr(-6);    // backup and touch bar

  slapper.move(90); // run slapper
  delay(25001);
  slapper.move(0);

  turn(-80);

  // STEP 2
  // ------------------------------

  dr(41); // 45
  turn(-180);

  horizontalFlaps.set(true);
  delay(500);
  turn(-180);
  dr_s(-72, 80); // ram mid balls

  horizontalFlaps.set(false);

  // CHECKPOINT 1 and STEP 3
  // ------------------------------
  // chassis.drive_angle_set(-180);

  chassis.drive_brake_set(pros::E_MOTOR_BRAKE_HOLD);
  turn(-180);

  chassis.pid_swing_set(e_swing::LEFT_SWING, -120, 127, 0);
  chassis.pid_wait();

  dr(-10);

  chassis.pid_swing_set(e_swing::LEFT_SWING, -270, 100, 20);
  chassis.pid_wait();

  dr_s(-72, 90); // push lane triballs

  turn(-290);

  chassis.pid_swing_set(e_swing::LEFT_SWING, -360, 127,
                        65); // side push after going through lane
  chassis.pid_wait();

  dr(-10);

  turn(-260);

  // chassis.pid_swing_set(e_swing::LEFT_SWING, -260, 80,
  //                       0); // swing to turn to middle
  // chassis.pid_wait();

  dr(44);

  // STEP 4
  // ------------------------------
  turn(-325);
  horizontalFlaps.set(true);
  delay(500);

  chassis.pid_swing_set(e_swing::RIGHT_SWING, -270, 127, 85); // mid push
  chassis.pid_wait();

  turn(-270);
  dr(20); // second push
  dr(-26);

  horizontalFlaps.set(false);

  dr(28);

  turn(-360);
  dr(-34);

  turn(-225);

  horizontalFlaps.set(true);
  chassis.pid_swing_set(e_swing::LEFT_SWING, -270, 127, 100);
  chassis.pid_wait();
}

void friendlyton() {
  // modified_exit_condition();
  chassis.drive_angle_set(-90);
  // intake first triball
  intake.move(127);
  verticalFlap.set(true);
  delay(500);
  verticalFlap.set(false);

  // push matchload to goal
  dr_s(-28, 80);
  chassis.pid_swing_set(ez::LEFT_SWING, -120, 110);
  chassis.pid_wait();
  dr_s(-26, 100);
  chassis.pid_swing_set(ez::LEFT_SWING, -180, 110);
  chassis.pid_wait();

  dr_s(5, 127);

  turn_s(-340, 127);

  intake.move(-127);
  delay(700);
  intake.move(0);

  turn_s(-170, 127);
  dr_s(-18, 127);

  // drive_s(10, 127); //second push
  // complete();

  // drive_s(-14, 127);
  // complete();

  chassis.pid_swing_set(ez::LEFT_SWING, -45, 100); // grab md
  chassis.pid_wait();

  intake.move(127);
  dr_s(52, 127);

  chassis.pid_swing_set(ez::RIGHT_SWING, -90, 127);
  chassis.pid_wait();

  dr_s(-12, 127);
  dr_s(5, 127);

  turn_s(90, 127);

  intake.move(-127);
  delay(500);
  dr_s(27, 127);

  delay(100);
  intake.move(0);
  dr(-10);

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

void awp() {}
