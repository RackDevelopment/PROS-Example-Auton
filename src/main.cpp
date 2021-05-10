// Copyright (c) 2021 RackDevelopment All Rights Reserved.

#include "main.h" // All VEX / PROS Functions
#include "okapi/api.hpp" // All Chassis Control Options

using namespace okapi;

/**
 * All Electronics Initialization
*/

// Controller
pros::Controller master(pros::E_CONTROLLER_MASTER);

// Drive Motors (2 Motors on the Back)
pros::Motor leftDrive1(1);
pros::Motor leftDrive2(2);
pros::Motor rightDrive1(3);
pros::Motor rightDrive2(4);

okapi::MotorGroup leftGroup({leftDrive1.get_port(), leftDrive2.get_port()});
okapi::MotorGroup rightGroup({rightDrive1.get_port(), rightDrive2.get_port()});

// Intake Motors
pros::Motor leftIntake(9);
pros::Motor rightIntake(10);

// Indexers
pros::Motor bottomIndexer(11);
pros::Motor topIndexer(20);

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);

	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	//pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

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
void autonomous() {

	std::shared_ptr<ChassisController> chassis =
		okapi::ChassisControllerBuilder()
		.withMotors(leftGroup, rightGroup)
		.withDimensions(AbstractMotor::gearset::green, {{4_in, 15.5_in}, imev5GreenTPR})
		.build();

		// set max speed
		chassis->setMaxVelocity(100);
		// move foward
		chassis->moveDistance(2_ft);
		chassis->waitUntilSettled();
		// start the cycle, move foward 6 feet
		chassis->moveDistance(6_ft);
		chassis->waitUntilSettled();
		// turn to the left
		chassis->turnAngle(270_deg);
		chassis->waitUntilSettled();
		// move foward 6 feet
		chassis->moveDistance(6_ft);
		chassis->waitUntilSettled();
		// turn to the left
		chassis->turnAngle(270_deg);
		chassis->waitUntilSettled();
		// move foward 6 feet
		chassis->moveDistance(6_ft);
		chassis->waitUntilSettled();
		// turn to the left
		chassis->turnAngle(270_deg);
		chassis->waitUntilSettled();
		// move foward 6 feet
		chassis->moveDistance(6_ft);
		chassis->waitUntilSettled();
		// rotate for the last time
		chassis->turnAngle(270_deg);
		chassis->waitUntilSettled();
		// return to the start position
		chassis->moveDistance(-2_ft);

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
void opcontrol() {
	while (true) {
		// Tank Controls... I think this would include slew mode but who knows lmao
		leftDrive1.move(master.get_analog(ANALOG_LEFT_Y));
		leftDrive2.move(master.get_analog(ANALOG_LEFT_Y));
		rightDrive1.move(master.get_analog(ANALOG_RIGHT_Y));
		rightDrive2.move(master.get_analog(ANALOG_RIGHT_Y));

		pros::delay(2);
	}
}
