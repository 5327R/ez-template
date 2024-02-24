#include "autons.hpp"
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
  chassis.pid_heading_constants_set(3, 0, 20);
  chassis.pid_drive_constants_set(12, 0, 20);
  chassis.pid_turn_constants_set(5, 0, 40);
  chassis.pid_swing_constants_set(5, 0, 40);

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
void testAuton() { dr_s(TILE * 2, 100); }

void skills() {
  // STEP 1
  // ------------------------------------------------------------------------------------------
  //  chassis.drive_brake_set(pros::E_MOTOR_BRAKE_HOLD);
  //  chassis.drive_angle_set(-180);

  // chassis.pid_swing_set(e_swing::RIGHT_SWING, -135, 90, 0);
  // chassis.pid_wait();
  // chassis.pid_swing_set(e_swing::LEFT_SWING, -180, 127,
  //                       78); // rams both alliance into enemy goal
  // chassis.pid_wait();

  // turn(-170);
  // dr(10);    // drive back after push
  // turn(-65); // get matchload angle
  // dr(-6);    // backup and touch bar

  // slapper.move(90); // run slapper
  // delay(1000);
  // slapper.move(0);

  // turn(-80);

  // dr(41); // 45
  // turn(-180);

  // horizontalFlaps.set(true);
  // delay(500);
  // turn(-180);
  // dr_s(-72, 80); // ram mid balls

  // horizontalFlaps.set(false);
  // //
  // // -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
  // // -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
  // -- -- -- -- -- -- -- -- -- Checkpoint 1
  chassis.drive_angle_set(-180);

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

  dr(-14);

  chassis.pid_swing_set(e_swing::LEFT_SWING, -265, 80,
                        0); // swing to turn to middle
  chassis.pid_wait();

  dr(44);

  turn(-315);
  horizontalFlaps.set(true);
  delay(500);

  chassis.pid_swing_set(e_swing::RIGHT_SWING, -270, 127, 95); // mid push
  chassis.pid_wait();

  turn(-270);
  dr(20); // second push
  dr(-22);

  horizontalFlaps.set(false);

  dr(28);

  turn(-360);
  // dr(-34);

  // turn(-225);

  // horizontalFlaps.set(true);
  // chassis.pid_swing_set(e_swing::LEFT_SWING, -270, 127, 90);
  // chassis.pid_wait();
}
