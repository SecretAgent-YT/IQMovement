#include "vex.h"

/*
@note All units are in INCHES or DEGREES
*/

class Chassis {
    public:

        /*
        @return New Chassis Object
        @param leftMotors MotorGroup object for left motors
        @param rightMotors MotorGroup object for right motors
        @param inertialPort Port of Gyro Sensor
        @param wheelSize Size of wheels in terms of diameter
        @param movekP P Constant for Move PD
        @param movekD D Constant for Move PD
        @param moveExit Exit condition in terms of error for Move PD
        @param turnkP P Constant for Turn PD
        @param turnkD D Constant for Turn PD
        @param turnExit Exit condition in terms of error for Turn PD
        */
        Chassis(motor_group leftMotors, motor_group rightMotors, int inertialPort, double ratio, double wheelSize, double movekP, double movekD, double moveExit, double turnkP, double turnkD, double turnExit);

        /*
        @brief Initializes Chassis with Motor Reset's + Gyro Calibration
        */
        void initChassis();

        /*
        @return X position of robot
        */
        double getX();

        /*
        @return Y position of robot
        */
        double getY();

        /*
        @return Angle robot is facing
        */
        double getAngle();

        /*
        @brief Turns robot to face angle
        @param angle Angle to turn to
        */
        void turnTo(double angle);

        /*
        @brief Turns robot to face point
        @param x X coordinate of point
        @param y Y coordinate of point
        */
        void turnTo(double x, double y);

        /*
        @brief Moves robot for amount
        @param Amount to move in inches
        */
        void moveFor(double inches);

        /*
        @brief Moves robot to point using turnTo and moveFor
        @param x X coordinate of point
        @param y Y coordinate of point
        */
        void moveTo(double x, double y);

    private:
        motor_group leftMotors;
        motor_group rightMotors;
        gyro inertial = gyro(1, false, turnType::left);
        double ratio;
        double wheelSize;
        double movekP;
        double movekD;
        double moveExit;
        double turnkP;
        double turnkD;
        double turnExit;
        double prevLeft = 0;
        double prevRight = 0;
        double prevTheta = 0;
        double x = 0;
        double y = 0;
        int odom();
};