// Test servos

#include <Servo.h>

Servo location;
Servo beatStick;
int pos;
int newLoc;
int hit;
int neutral;
int ans;
String input;
String testInput = "test";
boolean done;


// Move to desired location
void moveLoc(int desired) {
  Serial.print("\nMoving to ");
  Serial.print(desired);
  Serial.println(" step location");
  location.write(desired);
  pos = desired;
}

// Hit xylophone key
void hitKey()
{
  beatStick.write(hit);
  delay(300);
  beatStick.write(neutral);
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
  beatStick.attach(3);

  pos = 0;
  hit = 110;
  neutral = 80;

  moveLoc(90);
  beatStick.write(neutral);

  delay(1000);
}

void loop() {

//  Serial.println("Begin loop...\n\n");

  
  Serial.print("\nCurrent position is ");
  Serial.println(pos);

  Serial.println("\nWhich servo would you like to control?");
  Serial.println("1) Location");
  Serial.println("2) Beat stick");

  while (Serial.available() == 0) {}
  input = Serial.readString();
  ans = input.toInt();

  // User chooses to move location servo
  if (ans == 1) {
    Serial.println("\nYou chose location\nWhat position would you like to move to?");
  
    while (Serial.available() == 0) {}
    input = Serial.readString();
    newLoc = input.toInt();
    Serial.print("You wrote ");
    Serial.println(newLoc);
    moveLoc(newLoc);  

//    ans = 100;
  } 

  // User chooses to move beat stick servo
  else {
    Serial.println("\nYou chose beat stick\nWhat would you like to do?");
    Serial.println("1) Manual control\n2) Hit key function\n 3) Change hit position\n4) Change neutral position");
  
    while (Serial.available() == 0) {}
    input = Serial.readString();
    ans = input.toInt();

    // USER CHOICES FOR BEAT STICK CONTROL

    // Option 1: Manual
    if (ans == 1) {
      done = false;

      while (done == false) {
        Serial.println("\nYou chose manual control\nPlease specify a position:");
        while (Serial.available() == 0) {}
        input = Serial.readString();
        ans = input.toInt();
  
        Serial.print("Moving beat stick to ");
        Serial.print(ans);
        beatStick.write(ans);

        Serial.println("Would you like to continue manual control?");
        Serial.println("1) Yes\n 2) No");
        while (Serial.available() == 0) {}
        input = Serial.readString();
        ans = input.toInt();

        if (ans == 2) {
          done = true;
        }
      }
    }

    // Option 2: Hit key function
    else if (ans == 2) {
      done = false;
      
      while (done == false) {
        hitKey();
  
        Serial.println("Would you like to hit the key again?");
        Serial.println("1) Yes\n2) No");
        while (Serial.available() == 0) {}
        input = Serial.readString();
        ans = input.toInt();

        if (ans == 2) {
          done = true;
        }
      } 
    }

    // Option 3: Change hit position
    else if (ans == 3) {
      Serial.println("Enter a new hit position (0-180):");
      while (Serial.available() == 0) {}
      input = Serial.readString();

      Serial.print("You entered ");
      Serial.println(input);
      
      hit = input.toInt();
    }

    // Option 4: Change neutral position
    else {
      Serial.println("Enter a new neutral position (0-180):");
      while (Serial.available() == 0) {}
      input = Serial.readString();
      
      Serial.print("You entered ");
      Serial.println(input);
      
      neutral = input.toInt();
    }
  }
  


  // END LOOP AND RESTART
  delay(1000);

}
