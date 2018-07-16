#include<AFMotor.h>




//Variables
#define p1 A2
#define p2 A4

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
//Define pins ultrasonic(trig,echo)
int distance;
char incomingByte =0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  motor1.setSpeed(70);
    motor2.setSpeed(90);
      motor3.setSpeed(90);
    motor4.setSpeed(70);


}

void loop() {
  
        int i = digitalRead(51);

          //int duration,distance;
              if(i==1)
               {
               

              motor1.run(FORWARD);
                 motor2.run(FORWARD);
               motor3.run(FORWARD);
                 motor4.run(BACKWARD);
                 delay(500);
               }
               else
               {
                  motor1.run(BACKWARD);
                 motor2.run(BACKWARD);
               motor3.run(BACKWARD);
                 motor4.run(FORWARD);
               }
               
                   /*  motor1.run(BACKWARD);
                 motor2.run(BACKWARD);
              motor3.run(BACKWARD);
                 motor4.run(BACKWARD);
                 delay(3000);
               /*digitalWrite(p1, HIGH);
                delay(200);
                digitalWrite(p1, LOW);
                duration = pulseIn(p2, HIGH);
                distance = (duration/2)/29.1;
                Serial.println(distance);*/

              // }
}
