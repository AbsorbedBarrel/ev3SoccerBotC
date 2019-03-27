﻿#pragma config(Sensor, S1,     lineSensorLeft, sensorEV3_Color)
#pragma config(Sensor, S2,     colorSensor,    sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S3,     IRSensor,       sensorEV3_IRSensor, modeEV3IR_Seeker)
#pragma config(Sensor, S4,     lineSensorRight, sensorEV3_Color)
#pragma config(Motor,  motorB,          left,          tmotorEV3_Large, PIDControl, reversed, driveLeft, encoder)
#pragma config(Motor,  motorC,          right,         tmotorEV3_Large, PIDControl, reversed, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


//!!Code automatically generated by 'ROBOTC' configuration wizard!! \_(* ^ *)_/ //


/*This is the main code for the Striker Robot for
the Storming Robots Soccer League*/


//Function Initializations
void whenBall();
void whenNotBall();
void reset();
void spin(int speed);
void robotMove(int speed);
void angleTurn(int speed);
bool ballInRange(int distance);
bool hasBall(int minColor,int maxColor,int distance);
//float calculateEncoderValue(float wheelCirc, float distance, float degrees);




// Global Constants
const int goalieDistance = 15;
const int minOrangeColor = 1;
const int maxOrangeColor = 6;


/*MAIN::MAIN::MAIN::MAIN*/
task main()
{
        reset();
        do{
                robotMove(50);
                sleep(400);
                robotMove(50);
                writeDebugStreamLine("main: ballinrange, %b", ballInRange(getIRDistance(IRSensor)));
        }while(ballInRange(getIRDistance(IRSensor)) == true);
        //spin(20);
        robotMove(50);
        sleep(1000);
        //spin(-20);
        while(true) {
                if (hasBall(minOrangeColor, maxOrangeColor, goalieDistance) == true)
                {
                        whenBall();
                } else if (hasBall(minOrangeColor, maxOrangeColor, goalieDistance) == false)
                {
                        whenNotBall();
                } else{continue;}
        }
}
/*MAIN::MAIN::MAIN::MAIN*/


/*Function Definitions*/


//Resets moter values
void reset() {
        writeDebugStreamLine("reset");
        resetMotorEncoder(left);
        resetMotorEncoder(right);
        return;
}


//When the Robot has the ball
void whenBall() {
        /*Hue Value for White*/float whiteLine = 0.00;
        float colorYellow = 60.00;
        //spins until it sees the yellow goal
        
        do
        {
                //spin(25);
                sleep(1000);
                writeDebugStreamLine("whenBall 1st while:getcolor= %d, irdistance= %d", getColorHue(colorSensor), getIRDistance(IRSensor));
        }while(getColorHue(colorSensor) != colorYellow || getIRDistance(IRSensor) >= 45);
        //moves until it reaches the goal
        do
        {
                robotMove(50);
                sleep(1000);
                writeDebugStreamLine("whenBall 2nd while:rightlight= %d,leftLight=%d, irdistance= %d", getColorHue(lineSensorRight),getColorHue(lineSensorLeft), getIRDistance(IRSensor));
        }while(!(getColorHue(lineSensorRight) == whiteLine && getColorHue(lineSensorLeft) == whiteLine && getIRDistance(IRSensor) < goalieDistance));
        //Checks if the Robot is in the penalty box
        if ((getColorHue(lineSensorRight) == whiteLine && getColorHue(lineSensorLeft) == whiteLine && getIRBeaconStrength(S3) > 15) || (getColorHue(lineSensorRight) == whiteLine && getColorHue(lineSensorLeft) == whiteLine && getIRDistance(IRSensor) > goalieDistance))
        {
                writeDebugStreamLine("whenBall in penalty line ");
                robotMove(50);
                sleep(1000);
                robotMove(50);
                sleep(1000);
        }
        else {
                writeDebugStreamLine("whenBall not in penalty line ");
                robotMove(50);
                sleep(2000);
                spin(100);
                sleep(1000);
        }
        return;
}


//When the robot doesn't have the ball
void whenNotBall() {
        writeDebugStreamLine("whenNotBall ");
        angleTurn(360);
        sleep(1000);
        do
        {
                writeDebugStreamLine("getIRDistance => %d, goalieDistance = %d",getIRDistance(IRSensor), goalieDistance);
                robotMove(50);
                sleep(2000);
        }while(!(getIRDistance(IRSensor) <= goalieDistance));
        return;
}


//Spins the robot to throw the ball
void spin(int speed) {
        writeDebugStreamLine("spin : %d", speed);
        if(speed == NULL)
        {
                speed = 75;
                sleep(1000);
        }
        else{
                motor[left] = speed;
                sleep(500);
        }
        return;
}


//Tells the robot that the ball is 1 ft away from it
bool ballInRange(int distance){
        bool return1;        
        if(distance == NULL)
        {
                writeDebugStreamLine("ballInRange: %d", distance);
                distance = getIRDistance(IRSensor);
                sleep(1000);
        }else
        {
                writeDebugStreamLine("ballInRange else : %d", distance);
                if(distance > 30 && distance < 80){return1 = true;playSound(soundBeepBeep);}
                else {return1 = false;}
        } 
        return return1;
}


/* Function to calculate encoders
float calculateEncoderValue(float wheelCirc, float distance, float degrees) {
float ticks = degrees/wheelCirc;
float TotalTick = distance/ticks;
return TotalTick;
}*/


//Moves the robot forward
void robotMove(int speed)
{
        if(speed == NULL)
        {
                writeDebugStreamLine("robotMove: %d", speed);
                speed = 50;
                sleep(500);
        }else
        {
                writeDebugStreamLine("robotMove else(speed !== null): %d", speed);
                motor[left] = -(speed);
                sleep(1000);
                motor[right] = -(speed);
                sleep(325);
        }
        return;
}


//The robot will make a right angle turn
void angleTurn(int speed)
{
        if(speed == NULL)
        {
                writeDebugStreamLine("angleTurn (speed == null): %d", speed);
                speed = 75;
                sleep(1000);
        }else
        {
                writeDebugStreamLine("angleTurn else: %d", speed);
                motor[left] = speed;
                sleep(1000);
                motor[right] = -(speed);
                sleep(325);
        }
}


//Checks if the robot has the ball
bool hasBall(int minColor,int maxColor, int distance)
{
        bool return1;
        if(minColor == NULL || maxColor == NULL)
        {
                writeDebugStreamLine("hasball:minColor= %d, maxColor= %d, distance= %d", minColor,maxColor,distance);
                minColor = 40;
                maxColor = 60;
        }else if(distance == NULL)
        {
                writeDebugStreamLine("hasball else if distance == NULL : %d, %d, %d", minColor,maxColor,distance);
                distance = 5;
        }else
        {
                writeDebugStreamLine("hasball else :minColor= %d, maxColor= %d, distance= %d", minColor,maxColor,distance);
                if (SensorValue(IRSensor) <= 3)
                {
                        playSound(soundBlip);
                        return1 = true;
                } else if (SensorValue(IRSensor) <= 3)
                {
                        return1 = false;
                }
        }
        return return1;
}