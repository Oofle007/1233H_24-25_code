//   ____            _               _
//  |  _ \    ___   | |__     ___   | |_
//  | |_) |  / _ \  | '_ \   / _ \  | __|
//  |  _ <  | (_) | | |_) | | (_) | | |_
//  |_| \_\  \___/  |_.__/   \___/   \__|

#include "hteam/robot.h"

Robot::Robot() : mogoPneumaticState(false), doinkerPneumaticState(false),
                 mogoPneumatic('C'), doinkerPneumatic('F'),
                 intake(4),
                 arm(11, 12),
                 leftMotors({-5, 1, -11}, pros::MotorGearset::blue), // Rear, Stacked, Front
                 rightMotors({9, -10, 20}, pros::MotorGearset::blue),
                 drivetrain(&leftMotors, // left motors
                            &rightMotors, // right motors
                            12.5, // Track Width
                            3.25, // Wheel
                            480, // Drive RPM
                            2 // Horizontal Drift
                 ),
                 lateralController(6, // proportional gain (kP)
                                   0, // integral gain (kI)
                                   3.5, // derivative gain (kD)
                                   0, // anti-windup
                                   1.5, // small error range, in inches
                                   100, // small error range timeout, in milliseconds
                                   3.5, // large error range, in inches
                                   500, // large error range timeout, in milliseconds
                                   50), // maximum acceleration (slew)
                 angularController(1.1, // proportional gain (kP)
                                   0, // integral gain (kI)
                                   0.1, // derivative gain (kD)
                                   0, // anti-windup
                                   1.5, // small error range, in degrees
                                   100, // small error range timeout, in milliseconds
                                   3.5, // large error range, in degrees
                                   500, // large error range timeout, in milliseconds
                                   90), // maximum acceleration (slew)
                 horizontalEncoder(-13),
                 verticalEncoder(8),
                 horizontalTrackingWheel(&horizontalEncoder, 2.75, 0),
                 verticalTrackingWheel(&verticalEncoder, 2.75, 1.625),
                 imu(12),
                 sensors(&verticalTrackingWheel, // Vertical Encoder
                         nullptr, // No second Vertical Encoder
                         &horizontalTrackingWheel, // Horizontal tracking wheel
                         nullptr, // No second Horizontal Encoder
                         &imu), // Inertial
                 throttle_curve(3, // joystick deadband out of 127
                                10, // minimum output where drivetrain will move out of 127
                                1.019), // expo curve gain
                 steer_curve(3, // joystick deadband out of 127
                             10, // minimum output where drivetrain will move out of 127
                             1.019), // expo curve gain
                 chassis(drivetrain,
                         lateralController,
                         angularController,
                         sensors,
                         &throttle_curve,
                         &steer_curve) {}


Intake::Intake(const std::int8_t intakePort) : intakeMotor(intakePort, pros::MotorGearset::blue),
                                               sortColors(false),
                                               allowedColor(RED),  // Auto default allowed color to Red
                                               currentVoltage(0),
                                               mutex(),
                                               holding(false),
                                               holdPID(100,  // kP
                                                       0,  // DON'T CHANGE FROM 0 EVER
                                                       0,  // kD
                                                       0,  // integral anti windup range
                                                       false),  // don't reset integral when sign of error flips
                                               opticalSensor(14) {
    opticalSensor.set_led_pwm(0);
}

void Intake::startIntakeTask() {
    pros::Task myTask(intakeTask, this, "IntakeMoveTask");
}

void Intake::enableColorSorting() {
    mutex.take();
    sortColors = true;
    opticalSensor.set_led_pwm(100);
    mutex.give();
}

void Intake::disableColorSorting() {
    mutex.take();
    sortColors = false;
    opticalSensor.set_led_pwm(0);
    mutex.give();
}

void Intake::holdIntake() {
    mutex.take();
    holding = true;
    intakeMotor.set_zero_position(0);
    mutex.give();
}

void Intake::stopHoldingIntake() {
    mutex.take();
    holding = false;
    mutex.give();
}

void Intake::setVoltage(std::int32_t voltage) {
    mutex.take();
    currentVoltage = voltage;
    mutex.give();
}

void Intake::setAllowedColor(Color color) {
    mutex.take();
    allowedColor = color;
    mutex.give();
}

void Intake::intakeTask(void *param) {
    Intake *intake = static_cast<Intake *>(param);

    // Declare variables for color sorting
    const float REVERSE_TIME = 50;  // Time that the intake will reverse in MILLISECONDS
    const int MIN_PROX = 110; // Minimum proximity (distance) that the color sorter "detects" a ring
    const double BLUE_RING_HUE = 70;
    double timeStartReverse;  // The time in milliseconds when we set the intake to run in reverse
    const std::uint8_t INTAKE2TARGET = 0;  // The intake's goal will always be 0
    float holdPIDoutput;

    while (true) {
        intake->mutex.take();  // lock mutex to ensure exclusive excess

        if (intake->holding && intake->currentVoltage == 0) {  // Hold the intake when the lift is up and I don't give it a voltage
            // PID to keep the intake from moving when the lift is up so rings can't fall off
            holdPIDoutput = intake->holdPID.update(INTAKE2TARGET - intake->intakeMotor.get_position());
            intake->intakeMotor.move_voltage(holdPIDoutput);

        } else if (intake->sortColors) {  // COLOR SORTING

            if (intake->opticalSensor.get_proximity() > MIN_PROX) {  // If there is a ring in front of the optical sensor
                // If the ring detected is red and we want to only allow blue rings, reset our time stamp to start reversing
                if ((intake->allowedColor == BLUE && intake->opticalSensor.get_hue() < BLUE_RING_HUE) ||
                    (intake->allowedColor == RED && intake->opticalSensor.get_hue() >= BLUE_RING_HUE)) {
                    timeStartReverse = pros::c::millis();  // Create a timestamp of the last time a ring of the opposing alliance was detected
                }
            }

            // Check if we should be reversing the intake depending on the time of the last ring detected and how long the intake should be reversed for
            if ((pros::c::millis() - timeStartReverse) >= REVERSE_TIME) {
                intake->intakeMotor.move_voltage(intake->currentVoltage);
                intake->intakeMotor.set_zero_position(0);  // If lift is up, we need to reset the position so the PID keeps it where the intake was last
            } else {
                // Eject the ring off of the hook by spinning the intake in reverse
                intake->intakeMotor.move_voltage(-12000);
                intake->intakeMotor.set_zero_position(0);  // If lift is up, we need to reset the position so the PID keeps it where the intake was last
            }

        } else {  // Not sorting colors
            intake->intakeMotor.move_voltage(intake->currentVoltage);
            intake->intakeMotor.set_zero_position(0);  // If lift is up, we need to reset the position so the PID keeps it where the intake was last

        }

        intake->mutex.give();
        pros::delay(20); // don't hog CPU
    }
}

Arm::Arm(const std::int8_t motor1Port, const std::int8_t motor2Port) : armMotors({motor1Port, motor2Port}),
             armPID(10,
                    0,
                    0,
                    0,
                    false),
             mutex(),
             targetPosition(0) {}

void Arm::startArmTask() {
    pros::Task myTask1(armTask, this, "ArmTask");
}

void Arm::setPosition(int position) {
    mutex.take();
    targetPosition = position;
    mutex.give();
}

void Arm::setZeroPosition() {
    mutex.take();
    armMotors.tare_position();
    mutex.give();
}

void Arm::armTask(void *param) {
    Arm *arm = static_cast<Arm *>(param);

    double error;
    double output;

    while (true) {
        arm->mutex.take();

        error = arm->targetPosition - arm->armMotors.get_position();
        output = arm->armPID.update(error);

        // Ensure we don't over-volt the 5.5w motors
        if (output > 6000) {
            output = 6000;
        } else if (output < -6000) {
            output = -6000;
        }

        arm->armMotors.move_voltage(output);

        arm->mutex.give();

        pros::delay(20);
    }
}
