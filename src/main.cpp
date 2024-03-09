#include "main.h"
#include "EZ-Template/sdcard.hpp"
#include "EZ-Template/util.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////
pros::Motor intake(-19); //
// pros::ADIDigitalOut verticalFlap('E');
// pros::ADIDigitalOut horizontalFlaps('F');
ez::Piston verticalFlap('E'); 
ez::Piston horizontalFlaps('D');
ez::Piston hang('F');
ez::Piston balanceHang('C');
pros::Motor slapper1(-14);
pros::Motor slapper2(15);
pros::MotorGroup slapper({slapper1, slapper2});
bool slapperOn = false;
bool verticalFlapOut = false;
bool horizontalFlapsOut = false;

// Chassis constructor
Drive chassis(
    // Left Chassis Ports (negative port will reverse it!)
    //   the first port is the sensored port (when trackers are not used!)
    {-3, 15, -9}

    // Right Chassis Ports (negative port will reverse it!)
    //   the first port is the sensored port (when trackers are not used!)
    ,
    {2, -14, 8}

    // IMU Port
    ,
    20

    // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
    //    (or tracking wheel diameter)
    ,
    3.25

    // Cartridge RPM
    //   (or tick per rotation if using tracking wheels)
    ,
    600

    // External Gear Ratio (MUST BE DECIMAL)
    //    (or gear ratio of tracking wheel)
    // eg. if your drive is 84:36 where the 36t is powered, your RATIO would
    // be 2.333. eg. if your drive is 36:60 where the 60t is powered, your
    // RATIO would be 0.6.
    ,
    1.333333

    // Uncomment if using tracking wheels
    /*
    // Left Tracking Wheel Ports (negative port will reverse it!)
    // ,{1, 2} // 3 wire encoder
    // ,8 // Rotation sensor

    // Right Tracking Wheel Ports (negative port will reverse it!)
    // ,{-3, -4} // 3 wire encoder
    // ,-9 // Rotation sensor
    */

    // Uncomment if tracking wheels are plugged into a 3 wire expander
    // 3 Wire Port Expander Smart Port
    // ,1
);

// Game Loop Functions
// --------------------------------------------------------------------------------------------------------------------------------
void autonSelectTask()
{
  while (true)
  {
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT))
    {
      std::cout << "page up\n";
      ez::as::page_up();
    }
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT))
    {
      std::cout << "page down\n";
      ez::as::page_down();
    }
  }
  pros::delay(100);
  master.clear();
  // master.print(0, 0, "Counter: %d", ez::as::);
}
void debugDataTask()
{
  while (true)
  {
    std::cout << chassis.imu.get_heading() << std::endl;
    pros::delay(100);
  }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
// --------------------------------------------------------------------------------------------------------------------------------
void initialize()
{
  // Print our branding over your terminal :D
  // ez::print_ez_template();

  pros::delay(
      500); // Stop the user from doing anything while legacy ports configure.

  // // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(false);
  chassis.opcontrol_curve_left(1);
  chassis.opcontrol_curve_right(1);
  chassis.opcontrol_drive_activebrake_set(
      0.1); // Sets the active brake kP. We recommend 0.1.
  chassis.opcontrol_curve_default_set(
      0, 0);           // Defaults for curve. If using tank, only the first parameter is
                       // used. (Comment this line out if you have an SD card!)
  default_constants(); // Set the drive to your own constants from autons.cpp!
  pros::Task controllerAutonSelectTask(autonSelectTask);

  // These are already defaulted to these buttons, but you can change the
  // left/right curve buttons here! chassis.set_left_curve_buttons
  // (pros::E_master_DIGITAL_LEFT, pros::E_master_DIGITAL_RIGHT); // If using
  // tank, only the left side is used.
  // chassis.set_right_curve_buttons(pros::E_master_DIGITAL_Y,
  // pros::E_master_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
      Auton("(friendlyton) right side ABSOLUTE CLASSIC", testAuton),
      // Auton("(oppsteal) left side (with matchload and push center ball to
      // other side)", oppsteal), Auton("(oppton) starts on enemy side (match
      // loads)", oppton), Auton("(ProgSkills) Just runs flywheel the whole
      // time.", skillsProg),

  });

  // ez::as::limit_switch_lcd_initialize(&pgUpSwitch, &pgDownSwitch);

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  master.rumble(".");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{
  // . . .
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize()
{
  // . . .
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
  chassis.pid_targets_reset();               // Resets PID targets to 0
  chassis.drive_imu_reset();                 // Reset gyro position to 0
  chassis.drive_sensor_reset();              // Reset drive sensors to 0
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps
                                             // autonomous consistency

  ez::as::auton_selector
      .selected_auton_call(); // Calls selected auton from autonomous

  // skills();
  // friendlyton();
  // testAuton();
  // descore();
  // oppton_noflaps();
  // oppton();

  std::cout << "Autonomous Has Run\n";
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
{
  // This is preference to what you like to drive on.
  chassis.drive_brake_set(MOTOR_BRAKE_COAST);
  // intake.move(0);
  while (true)
  {
    // chassis.tank(); // Tank control
    chassis.opcontrol_arcade_standard(ez::SPLIT); // Standard split arcade
    // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade

    if (master.get_digital_new_press(DIGITAL_R1))
    {
      if (intake.get_target_velocity() > 0)
      {
        intake.move(0);
      }
      else
      {
        intake.move(127);
      }
    }

    if (master.get_digital_new_press(DIGITAL_R2))
    {
      if (intake.get_target_velocity() < 0)
      {
        intake.move(0);
      }
      else
      {
        intake.move(-127);
      }
    }

    if (master.get_digital_new_press(DIGITAL_Y))
    {
      if (slapperOn)
      {
        slapper.move(0);
        slapperOn = false;
      }
      else
      {
        slapper.move(90);
        slapperOn = true;
      }
    }

    horizontalFlaps.button_toggle(master.get_digital(DIGITAL_L2));
    verticalFlap.button_toggle(master.get_digital(DIGITAL_L1));
    hang.button_toggle(master.get_digital(DIGITAL_B));
    balanceHang.button_toggle(master.get_digital(DIGITAL_A));

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!
                                       // Keep this ez::util::DELAY_TIME
  }
}

// void opcontrol() {
//   chassis.drive_brake_set(MOTOR_BRAKE_HOLD);
//   autonomous();
// }
