#include "main.h"
#include "liblvgl/llemu.hpp"
#include <sstream>

//Config
pros::MotorGroup left_mtrs({11,-12,-13});
pros::MotorGroup right_mtrs({-14,15,16});
pros::Rotation v_encoder(20);
pros::Rotation h_encoder(8);
pros::Imu imu(19);
lemlib::ControllerSettings lateral_controller(10, 0 , 8 , 10 , 1 , 100, 3 , 500, 10);
lemlib::ControllerSettings angular_controller(6 , 0 , 20, 5 , 1 , 100, 3 , 500, 20);
lemlib::Drivetrain drive_train(&left_mtrs, &right_mtrs, 15.25, 3.25, 450, 8);
lemlib::TrackingWheel v_tracking_wheel(&v_encoder, 3.25, -1.77);
lemlib::TrackingWheel h_tracking_wheel(&h_encoder, 3.25, 1);
lemlib::OdomSensors sensors(&v_tracking_wheel, nullptr , &h_tracking_wheel, nullptr, &imu);
lemlib::Chassis chassis(drive_train, lateral_controller, angular_controller, sensors);

//Init code
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(0, "Code booted");
}

//Auton code
void autonomous() {

}

//Positioning testing
void opcontrol() {
	std::stringstream output("");
	output << "Pos X: " << chassis.getPose().x << " ";
	output << "Pos Y: " << chassis.getPose().y << " ";
	output << "Theta: " << chassis.getPose().theta << "\n";
	pros::lcd::set_text(1, output.str());
}