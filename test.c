// Test servos

#include <Servo.h>

Servo location;
int pos;
int newLoc;
String input;
String testInput = "test";

void moveLoc(int desired) {
  location.write(desired);
  pos = desired;
  Serial.print("\nMoving to ");
  Serial.print(pos);
  Serial.println(" step location");
}


// test if movement of note is correct
void testNote() {
  moveLoc(90);
  delay(1000);
  
  moveLoc(90-24);
  delay(2000);
  moveLoc(90-48);
  delay(2000);

  moveLoc(90-24);
  delay(2000);
  moveLoc(90);
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

  pos = 0;

  moveLoc(90);

  delay(1000);
}

void loop() {

//  Serial.println("Begin loop...\n\n");

  
  Serial.print("\nCurrent position is ");
  Serial.println(pos);
  Serial.println("\nWhat position would you like to move to?");

  while (Serial.available() == 0) {}
  // read the incoming byte:
  input = Serial.readString();
  if (input.equals(testInput)) {
    Serial.println("you wrote test");
    testNote();
  } else {
    newLoc = input.toInt();
    moveLoc(newLoc);  
  }
  

  delay(1000);

  
  
//  Serial.println("Restarting loop in 3...");
//  delay(1000);
//  Serial.println("Restarting loop in 2...");
//  delay(1000);
//  Serial.println("Restarting loop in 1...");
//  delay(1000);
}
 
