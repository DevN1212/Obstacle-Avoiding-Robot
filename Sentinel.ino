#include <AFMotor.h>
#include <NewPing.h>  // Add this line to include the NewPing library
#include <Servo.h>

#define TRIG_PIN A4
#define ECHO_PIN A5
#define MAX_DISTANCE 200
#define MAX_SPEED 190 // sets speed of DC motors
#define MAX_SPEED_OFFSET 20
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); // Declare sonar globally

AF_DCMotor motor2(2, MOTOR12_1KHZ); // Use MOTOR12_64KHZ for more torque
AF_DCMotor motor4(4, MOTOR34_1KHZ);

Servo myservo;

boolean goesForward = false;
int distance = 100;
int speedSet = 0;

void setup()
{
  myservo.attach(10);
  myservo.write(115);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop()
{
  int distanceR = 0;
  int distanceL = 0;
  delay(40);

  if (distance <= 15)
  {
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);

    if (distanceR >= distanceL)
    {
      turnRight();
      moveStop();
    }
    else
    {
      turnLeft();
      moveStop();
    }
  }
  else
  {
    moveForward();
  }
  distance = readPing();
}
int lookRight()
{
  myservo.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(115);
  return distance;
}    
int lookLeft()
{
  myservo.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(115);
  return distance;
}
int readPing()
{
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0)
  {
    cm = 250;
  }
  return cm;
}
void moveStop()
{
  motor2.run(RELEASE);
  motor4.run(RELEASE);
}
void moveForward()
{
  if (!goesForward)
  {
    goesForward = true;
    motor2.run(FORWARD);
    motor4.run(FORWARD);
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2)
    {
      motor2.setSpeed(speedSet);
      motor4.setSpeed(speedSet);
      delay(5);
    }
  }
}
void moveBackward()
{
  goesForward = false;
  motor2.run(BACKWARD);
  motor4.run(BACKWARD);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2)
  {
    motor2.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}
void turnRight()
{ 
  motor2.run(FORWARD);
  motor4.run(BACKWARD);
  delay(500);
  motor2.run(FORWARD);
  motor4.run(FORWARD);
}
void turnLeft()
{
  motor2.run(BACKWARD);
  motor4.run(FORWARD);
  delay(500);
  motor2.run(FORWARD);
  motor4.run(FORWARD);
}