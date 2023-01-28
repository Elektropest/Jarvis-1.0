//Developed by Elektropest

#include <Stepper.h>
#include <Servo.h>

Stepper xmotor(200, 2, 4, 3, 5);
Servo ymotor;
Servo zmotor;

int lastRead;
int zstate;

void setup()
{
  xmotor.setSpeed(60);
  ymotor.attach(7);
  zmotor.attach(8);
  digitalWrite(11, HIGH);
  Serial.begin(9600);
}

void loop()
{
  //xmotor
  if(analogRead(1) < 450)
  {
    xmotor.step(-1);
  }
  else if(analogRead(1) > 550)
  {
    xmotor.step(1);
  }

  //ymotor
  ymotor.write(map(analogRead(0), 0, 1023, 70, 10));
  if(analogRead(0) > 550 || analogRead(0) < 450)
  {
    analogWrite(A2, 0);
    analogWrite(A3, 255);
  }
  else
  {
    analogWrite(A2, 255);
    analogWrite(A3, 0);
  }

  //zmotor
  if(digitalRead(11) != lastRead)
  {
    if(digitalRead(11) == HIGH)
    {
      if(zstate == HIGH)
      {
        for (int i = 0; i <= 170; i++)
        {
          zmotor.write(i);
          delay(15);
        }
        zstate = LOW;
        analogWrite(A4, 0);
        analogWrite(A5, 255);
      }
      else
      {
        for (int i = 170; i >= 0; i--)
        {
          zmotor.write(i);
          delay(15);
          zstate = HIGH;
          analogWrite(A4, 255);
          analogWrite(A5, 0);
        }
      }
    }
    lastRead = digitalRead(11);
  }
  Serial.println(analogRead(0));
}
