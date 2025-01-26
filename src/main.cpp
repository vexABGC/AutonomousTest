#include "main.h"
#include <sstream>

//Config
pros::MotorGroup left_mtrs({11,-12,-13});
pros::MotorGroup right_mtrs({-14,15,16});
pros::Rotation v_encoder(20);
pros::Rotation h_encoder(8);
pros::Imu imu(19);
lemlib::ControllerSettings lateral_controller(4.5, 0, 6, 3, 1, 10, 3, 500, 20);
lemlib::ControllerSettings angular_controller(3.25, 0, 23.5, 3, 1, 100, 3, 500, 0);
lemlib::Drivetrain drive_train(&left_mtrs, &right_mtrs, 15.25, 3.25, 450, 8);
lemlib::TrackingWheel v_tracking_wheel(&v_encoder, 3.25, -1.77);
lemlib::TrackingWheel h_tracking_wheel(&h_encoder, 3.25, 1);
lemlib::OdomSensors sensors(&v_tracking_wheel, nullptr , &h_tracking_wheel, nullptr, &imu);
lemlib::Chassis chassis(drive_train, lateral_controller, angular_controller, sensors);
pros::Controller master(pros::E_CONTROLLER_MASTER);

//Init code
void initialize() {
	chassis.calibrate();
	pros::lcd::initialize();
	pros::lcd::set_text(0, "Code booted");
	pros::delay(60);
	master.clear();
	pros::delay(60);
	master.set_text(0, 0, "Booted");
}

//Auton code
void autonomous() {
	//Angular tuning
	//chassis.setPose(0,0,0);
	//chassis.turnToHeading(90, 100000000, {}, false);

	//Lateral tuning
	//chassis.setPose(0,0,0);
	//chassis.moveToPoint(0,48,1000000000, {}, false);

	//Test movement
	chassis.setPose(0,0,0);
	chassis.moveToPose(48, 48, 90, 8000, {.forwards = true}, false);

	//Auton finish message
	master.set_text(0, 0, "Auton done");
}

void disabled(){}

//Positioning testing
void opcontrol() {
	while (true) {
		std::stringstream output("");
		output << std::fixed << std::setprecision(0);
		output << "Pos X: " << chassis.getPose().x << " ";
		output << "Pos Y: " << chassis.getPose().y << " ";
		output << "Theta: " << chassis.getPose().theta << "\n";
		pros::lcd::set_text(1, output.str());
		pros::delay(50);

		chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
		chassis.arcade(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), true, 0);
	}
}