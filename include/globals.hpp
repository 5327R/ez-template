#include "main.h"

pros::Motor intake_motor(4);	//
pros::Optical intake_color(17); //
pros::ADIDigitalOut flaps('G');
pros::Imu IMU(14); //
pros::Motor flywheel_motor(9);	 //
pros::ADIDigitalOut arm('H');

bool flywheel_on = false;
bool flaps_out = false;
bool arm_on = false;
bool intake_running = true;
bool intake = false;
bool force_out = false;