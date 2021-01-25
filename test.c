// Test location servo

#include <Servo.h>

Servo location;
int pos;

void moveLoc(int desired) {
  desired = pos + desired;
  desired = pos;
  location.write(desired);
  Serial.print("Moving ");
  Serial.print(desired);
  Serial.println(" steps");
}


// test if movement of note is correct
void testNote() {
  moveLoc(24);
  delay(2000);
  moveLoc(24);
  delay(2000);

  moveLoc(-24);
  delay(2000);
  moveLoc(-24);
  delay(2000);
}

void setup() {
  Serial.begin(9600);
  Serial.println("\n\nBREAK ----");
  Serial.println("BREAK ----");
  Serial.println("BREAK ----");
  Serial.println("BREAK ----");
  Serial.println();
  Serial.println();
  Serial.println();

  delay(500);
  Serial.println("SYSTEM START\n");
  location.attach(5);

  moveLoc(90);

  delay(2000);

}

void loop() {

  Serial.println("Begin loop...\n\n");
  Serial.print("Current position is ");
  Serial.println(pos);
  
  testNote();

  
  
  Serial.println("Restarting loop in 5 seconds");
  delay(5000);
}
