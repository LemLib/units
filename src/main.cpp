#include "main.h"
#include "units/Pose.hpp"
#include "units/Temperature.hpp"

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
    pros::lcd::register_btn1_cb(on_center_button);
    units::AccelerationPose a(1_mps2, 2_mps2);
    Number num = Number(1.0);
    num = Number(0.0);
    a.theta().convert(Degree);
    a.setOrientation(Quantity<std::ratio<0>, std::ratio<0>, std::ratio<-2>, std::ratio<0>, std::ratio<1>, std::ratio<0>,
                              std::ratio<0>, std::ratio<0>>(1.0));
    a.getOrientation() += 2_rpm2;
    2_rpm2 -= a.getOrientation();
    units::conversions::to_cDeg(Quantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>, std::ratio<0>,
                     std::ratio<0>, std::ratio<0>>(5.0) -
            a.theta() + 5_cDeg);
    Quantity<std::ratio<0>, std::ratio<0>, std::ratio<1>, std::ratio<0>, std::ratio<1>, std::ratio<0>, std::ratio<0>,
             std::ratio<0>>
        c = Multiplied<Angle, Time>();
    Length x = unit_cast<Length>(num);
    Angle y = toAngular<Length>(x, 2_cMeter);
    Length z = toLinear<Angle>(y, 2_cMeter);
    static_assert(Angle(5.1) >= Quantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>,
                                         std::ratio<0>, std::ratio<0>, std::ratio<0>>(5.0));
    units::clamp(2_cDeg, a.theta(), Quantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>,
                                         std::ratio<0>, std::ratio<0>, std::ratio<0>>(5.0));
    units::max(10_celsius, Quantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>,
                              std::ratio<0>, std::ratio<0>>(1.0));
}

/**
 * Runs while the Probot is in the disabled state of Field Management System or
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
void autonomous() {}

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
    pros::Controller master(pros::E_CONTROLLER_MASTER);
    pros::MotorGroup left_mg({1, -2, 3}); // Creates a motor group with forwards ports 1 & 3 and reversed port 2
    pros::MotorGroup right_mg({-4, 5, -6}); // Creates a motor group with forwards port 4 and reversed ports 4 & 6

    while (true) {
        pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
                         (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,

                         (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0); // Prints status of the emulated screen LCDs

        // Arcade control scheme
        int dir = master.get_analog(ANALOG_LEFT_Y); // Gets amount forward/backward from left joystick
        int turn = master.get_analog(ANALOG_RIGHT_X); // Gets the turn left/right from right joystick
        left_mg.move(dir - turn); // Sets left motor voltage
        right_mg.move(dir + turn); // Sets right motor voltage
        pros::delay(20); // Run for 20 ms then update
    }
}