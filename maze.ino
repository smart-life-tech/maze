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
float FrontSensor, RightSensor, LeftSensor;
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

    Serial.begin(9600);
}

void ir_sens()
{
    digitalRead(left_ir);
    digitalRead(right_ir);
}
void line_modus()
{

    if (left_ir == 0 && right_ir == 0)
    {
        // Forward
        motor1.run(FORWARD);
        motor1.setSpeed(30);
        motor2.run(FORWARD);
        motor2.setSpeed(30);
    }

    else if (left_ir == 1 && right_ir == 0)
    {

        motor1.run(FORWARD);
        motor1.setSpeed(45);
        motor2.run(BACKWARD);
        motor2.setSpeed(45);
    }

    else if (left_ir == 0 && right_ir == 1)
    {

        motor1.run(BACKWARD);
        motor1.setSpeed(45);
        motor2.run(FORWARD);
        motor2.setSpeed(45);
    }

    else if (left_ir == 1 && right_ir == 1)
    {

        motor1.run(RELEASE);
        motor1.setSpeed(0);
        motor2.run(RELEASE);
        motor2.setSpeed(0);

        // delay(1000);
    }
}
void maze_modus()
{

    if (RightSensor > 5 && FrontSensor > 6)
    {
        turn_left();
    }
    if (RightSensor <= 7 && FrontSensor > 6)
    {
        turn_right();
    }
    if (FrontSensor <= 5)
    {
        reverse();
    }
    if (FrontSensor > 6 && RightSensor > 5 && LeftSensor > 5)
    {
        // sackgassen modus
        reverse();
        delay(90);
        turn_left();
        delay(250);
    }

    else
    {
        forward();
        delay(90);
    }
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

void US_F()
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
}
void US_R()
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
}
void US_L()
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
}
void loop()
{
    ir_sens();
    for (stuck = 0; stuck <= 3; stuck++)
    {
        US_F();
        if (FrontSensor == 0)
        {
            US_F();
        }
        US_R();
        if (RightSensor == 0)
        {
            US_R();
        }
        US_L();
        if (LeftSensor == 0)
        {
            US_L();
        }
        frontstuckAVG = frontstuck[0] + frontstuck[1] + frontstuck[2] + frontstuck[3] / 4;
        rightstuckAVG = rightstuck[0] + rightstuck[1] + rightstuck[2] + rightstuck[3] / 4;
        leftstuckAVG = leftstuck[0] + leftstuck[1] + leftstuck[2] + leftstuck[3] / 4;
        if (frontstuckAVG = frontstuck[1])
        {
            reverse();
        }
        if (rightstuckAVG = rightstuck[1])
        {
            reverse();
        }
        if (leftstuckAVG = leftstuck[1])
        {
            reverse();
        }
    }

    Serial.print("FrontSensor");
    Serial.println(FrontSensor);
    Serial.print("RightSensor");
    Serial.println(RightSensor);
    Serial.print("LeftSensor");
    Serial.println(LeftSensor);
    if (RightSensor > 10 && LeftSensor > 10 && FrontSensor > 10)
    {
        modus = 1;
    }
    if (RightSensor <= 10 && 2 < RightSensor && LeftSensor <= 10 && 2 < LeftSensor && FrontSensor <= 10 && 2 < FrontSensor)
    {
        modus = 2;
    }
    if (left_ir == 1 && right_ir == 1)
    {
        modus = 3;
    }
    Serial.print("modus = ");
    Serial.println(modus);
    delay(1000);
}
