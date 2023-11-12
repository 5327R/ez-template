#include "main.h"
/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////
pros::Motor intake_motor(4);	//
pros::ADIDigitalOut flaps('A');
pros::Motor slapper_motor(-10);	 //
pros::ADIDigitalOut blocker('C');

bool slapper_on = false;
bool flaps_out = false;
bool blocker_on = false;
// true
bool intake_running = false;
// false
bool intake_in = true;
//bool force_out = false;

bool intake = false;
bool outtake = false;

// Chassis constructor
Drive chassis(
    // Left Chassis Ports (negative port will reverse it!)
    //   the first port is the sensored port (when trackers are not used!)
    {-15, -17, -6}

    // Right Chassis Ports (negative port will reverse it!)
    //   the first port is the sensored port (when trackers are not used!)
    ,
    {19, 18, 3}

    // IMU Port
    ,
    7

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
    // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
    // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
    ,
    1.667

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

// Subsystems
// --------------------------------------------------------------------------------------------------------------------------------

void run_intake(bool in) {
  if (intake_running && (in == intake_in)) {
    intake_motor.move(0);
    intake_running = false;
  }
  else if (in) {
    intake_motor.move(-127);
    intake_running = true;
    intake_in = true;
  }
  else {
    intake_motor.move(127);
    intake_running = true;
    intake_in = false;
  }
}

void move_flaps()
{
  flaps_out = !flaps_out;

  if (flaps_out)
  {
    flaps.set_value(true);
  }
  else
  {
    flaps.set_value(false);
  }
}

void run_slapper()
{
  if (!blocker_on){
    return;
  }
  slapper_on = !slapper_on;

  if (slapper_on)
  {
    slapper_motor.move(127);
  }
  else
  {
    slapper_motor.move(0);
  }
}

void set_blocker()
{
  blocker_on = !blocker_on;

  if (blocker_on)
  {
    blocker.set_value(true);
  }
  else
  {
    blocker.set_value(false);
  }
}


// Game Loop Functions
// --------------------------------------------------------------------------------------------------------------------------------
void debugDataTask() {
  while (true){
    std::cout << chassis.imu.get_heading() << std::endl;
    //std::cout << "I love kevin\n";
    pros::delay(100);
  }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
  // Print our branding over your terminal :D
  // ez::print_ez_template();

  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0);                       // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(0, 0);                   // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)
  default_constants();                               // Set the drive to your own constants from autons.cpp!
  exit_condition_defaults();                         // Set the exit conditions to your own constants from autons.cpp!

  pros::Task dataTask(debugDataTask);
  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used.
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.add_autons({
      Auton("(friendlyton) right side ABSOLUTE CLASSIC", friendlyton), 
      //Auton("(oppsteal) left side (with matchload and push center ball to other side)", oppsteal),
      //Auton("(oppton) starts on enemy side (match loads)", oppton),
      //Auton("(ProgSkills) Just runs flywheel the whole time.", skillsProg),
      
  
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
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
  chassis.reset_pid_targets();               // Resets PID targets to 0
  chassis.reset_gyro();                      // Reset gyro position to 0
  chassis.reset_drive_sensor();              // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.

  //ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
  std::cout << "Autonomous Has Run";
  //drive_example();
  friendlyton();
  //skillsProg();
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
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);

  while(true)
  {
    // chassis.tank(); // Tank control
    chassis.arcade_standard(ez::SPLIT); // Standard split arcade
    // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade

    // Intake
    if (master.get_digital_new_press(DIGITAL_R1))
    {
      run_intake(true);
    }
    if (master.get_digital_new_press(DIGITAL_R2))
    {
      run_intake(false);
    }

    // Flaps
    if (master.get_digital_new_press(DIGITAL_A))
    {
      move_flaps();
    }

    if (master.get_digital_new_press(DIGITAL_L1))
    {
      run_slapper();
    }

    if (master.get_digital_new_press(DIGITAL_Y))
    {
      set_blocker();
    }

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
