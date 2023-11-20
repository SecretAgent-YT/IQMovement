#include "vex.h"

using namespace vex;

Chassis::Chassis(motor_group _leftMotors, motor_group _rightMotors, int _inertialPort, double _ratio, double _wheelSize, double _movekP, double _movekD, double _moveExit, double _turnkP, double _turnkD, double _turnExit) {
    leftMotors = _leftMotors;
    rightMotors = _rightMotors;
    inertial = gyro(_inertialPort, false, turnType::left);
    ratio = _ratio;
    wheelSize = _wheelSize;
    movekP = _movekP;
    movekD = _movekD;
    moveExit = _moveExit;
    turnkP = _turnkP;
    turnkD = _turnkD;
    turnExit = _turnExit;
}

double length_to_position(double length, double wheelSize, double ratio)
{
    return (length / (wheelSize * M_PI)) * 360 * ratio;
}

double position_to_length(double position, double wheelSize, double ratio) {
    return (position * wheelSize * M_PI) / (360 * ratio);
}

double constrain_angle_error(double error)
{
    if (error >= 180)
    {
        error -= 360;
    }
    else if (error < -180)
    {
        error += 360;
    }
    return error;
}


int Chassis::odom() {
    while (true) {
        double left = leftMotors.position(rotationUnits::deg);
        double right = rightMotors.position(rotationUnits::deg);
        double dist = ((left - prevLeft) + (right - prevRight)) / 2;
        double thetaChange = constrain_angle_error(inertial.heading(rotationUnits::deg) - prevTheta);
        x += dist * sin(thetaChange);
        y += dist * cos(thetaChange);
        prevLeft = left;
        prevRight = right;
        prevTheta = inertial.heading(rotationUnits::deg);
        this_thread::sleep_for(10);
    }
    return 0;
}

void Chassis::initChassis() {
    leftMotors.resetPosition();
    rightMotors.resetPosition();
    inertial.calibrate(gyroCalibrationType::calNormal, true);
    //setup task
}

double Chassis::getX() {
    return position_to_length(x, wheelSize, ratio);
}

double Chassis::getY() {
    return position_to_length(y, wheelSize, ratio);
}

double Chassis::getY() {
    return inertial.heading(rotationUnits::deg);
}