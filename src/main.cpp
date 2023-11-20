/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       iyeng                                                     */
/*    Created:      11/20/2023, 1:23:44 PM                                    */
/*    Description:  IQ2 project                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the IQ2 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here

motor_group leftMotors;
motor_group rightMotors;
int gyroPort = 0;

Chassis chassis(leftMotors, rightMotors, gyroPort, 1, 2, 0.1, 0.01, 5, 0.1, 0.01, 1);

int main() {
	
    Brain.Screen.printAt( 2, 30, "Hello IQ2" );
    chassis.moveFor(12);

    while(1) {
        
        
        this_thread::sleep_for(10);
    }
}