#include <AFMotor.h>

#define left_ir 5
#define right_ir 4

#define trigPinF 10 // Front
#define echoPinF 6

#define trigPinR 12 // Right
#define echoPinR 13

#define trigPinL 8 // Left
#define echoPinL 9
long durfront, durright, durleft;
int FrontSensor, RightSensor, LeftSensor;
int min_range = 2;
int i;
int stuck = 0;
int frontstuck[4];
int rightstuck[4];
int leftstuck[4];
int frontstuckAVG;
int rightstuckAVG;
int leftstuckAVG;
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);

int modus = 1;
void setup()
{
    int modus = 1;
    motor2.setSpeed(65);
    motor1.setSpeed(65);
    pinMode(left_ir, INPUT);
    pinMode(right_ir, INPUT);
    Serial.begin(9600);
}

void ir_sens()
{
    digitalRead(left_ir);
    digitalRead(right_ir);
}

void forward()
{

    motor1.setSpeed(35);
    motor2.setSpeed(35);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
}

void veryfast()
{

    motor1.setSpeed(35);
    motor2.setSpeed(35);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
}

void turn_left()
{

    motor1.setSpeed(35);
    motor2.setSpeed(35);
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
}

void turn_right()
{

    motor1.setSpeed(35);
    motor2.setSpeed(35);
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
}

void reverse()
{

    motor1.setSpeed(35);
    motor2.setSpeed(35);
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
}

void stop()
{

    motor1.run(RELEASE);
    motor1.setSpeed(0);
    motor2.run(RELEASE);
    motor2.setSpeed(0);
}

int US_F()
{
    digitalWrite(trigPinF, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinF, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinF, LOW);
    delayMicroseconds(2);
    durfront = pulseIn(echoPinF, HIGH);
    delayMicroseconds(200);
    FrontSensor = durfront * 0.03435 / 2;
    delayMicroseconds(200);
    return FrontSensor;
}

int US_R()
{
    digitalWrite(trigPinR, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinR, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinR, LOW);
    delayMicroseconds(2);
    durright = pulseIn(echoPinR, HIGH);
    delayMicroseconds(200);
    RightSensor = durright * 0.03435 / 2;
    delayMicroseconds(200);
    return RightSensor;
}

int US_L()
{
    digitalWrite(trigPinL, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinL, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinL, LOW);
    delayMicroseconds(2);
    durleft = pulseIn(echoPinL, HIGH);
    delayMicroseconds(200);
    LeftSensor = durleft * 0.03435 / 2;
    delayMicroseconds(200);
    return LeftSensor;
}
void loop()
{
    if (!digitalRead(left_ir) || !digitalRead(right_ir)) // if there is no obstacle
    {                                                    // obstacle left and right
        // see if there is no obstacle in the front

        if (US_F() > 7)
        {
            forward();
            delay(500);
        }
        else
        {
            stop();
            reverse();
            delay(100);
            stop();
            // check the right and left sensor
            // if left is greater than right
            // turn left

            if (US_R() > US_L())
            {
                turn_right();
                delay(1000);
            }
           else if (US_L() > US_R())
            {
                turn_left();
                delay(1000);
            }else{
                reverse();
            }
        }
    }
}