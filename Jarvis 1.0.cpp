//Developed by Elektropest.hu

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
  if(analogRead(1) < 500)
  {
    xmotor.step(-1);
    xmotor.setSpeed(map(analogRead(1), 500, 0, 10, 150));
  }
  else if(analogRead(1) > 510)
  {
    xmotor.step(1);
    xmotor.setSpeed(map(analogRead(1), 510, 1023, 10, 150));
  }

  //ymotor
  ymotor.write(map(analogRead(0), 0, 1023, 80, 10));

  //zmotor
  if(digitalRead(11) != lastRead)
  {
    if(digitalRead(11) == HIGH)
    {
      if(zstate == HIGH)
      {
        for (int i = 0; i <= 180; i++)
        {
          zmotor.write(i);
          delay(15);
        }
        zstate = LOW;
      }
      else
      {
        for (int i = 180; i >= 0; i--)
        {
          zmotor.write(i);
          delay(15);
          zstate = HIGH;
        }
      }
    }
    lastRead = digitalRead(11);
  }

  Serial.println(digitalRead(11));
}
