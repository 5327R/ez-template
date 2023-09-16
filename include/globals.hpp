#include "main.h"

// UPDATE MOTOR PORTS & PISTON WIRES.
pros::Motor left_motor_b(-13); //
pros::Motor left_motor_m(-11); //
pros::Motor left_motor_f(-3);  //
pros::MotorGroup left_motorgroup({left_motor_b, left_motor_m, left_motor_f});

pros::Motor right_motor_b(8);  //
pros::Motor right_motor_m(6);  //
pros::Motor right_motor_f(20); //
pros::MotorGroup right_motorgroup({right_motor_b, right_motor_m, right_motor_f});

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