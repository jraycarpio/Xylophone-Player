/*
 *
 *  By: Jonathan R. Carpio
 *
 */

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
  Serial.println("HIT");
  delay(300);
  beatStick.write(neutral);
  Serial.println("OFF KEY");
}


// Define notes and song portions

// Notes
int n1 = 10;
int n2 = 50;
int n3 = 75;
int n4 = 95;
int n5 = 125;
int n6 = 155;
int n7 = 170;

// Half of portion 1
int song1_half[] = {n1, n2, n3, n4, n5, n6};
int size1_half = 6;

// Full portion 1
int song1[] = {n1, n2, n3, n4, n5, n6, n5, n3, n4, n3, n2};
int size1 = 11;

// Full portion 2
int song2[] = {n1, n2, n3, n4, n5, n6, n7, n5, n6, n5, n4};
int size2 = 11;

// Full portion 3
int song3[] = {n1, n2, n3, n4, n5, n6, n7, n6, n5, n4, n3, n2, n1};
int size3 = 13;

// Song portion sequence is 1, 2, 3

// Song function

void play(int song[], int arrSize) {
  for (int i = 0; i < arrSize; i++) {
    Serial.println(i);
    moveLoc(song[i]);
    delay(700);
    hitKey();
    delay(300);

    if (arrSize == 11) {
      if (i == 5) {
        delay(500);
      }

      else if (i == 6) {
        delay(500);
      }
    }

    else if (arrSize == 13) {
      if (i == 11) {
        delay(800);
      }
    }
  }
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

  moveLoc(10);
  beatStick.write(neutral);

  delay(1000);
}

void loop() {

//  Serial.println("Begin loop...\n\n");

  
  Serial.print("\nCurrent position is ");
  Serial.println(pos);

  Serial.println("\nWhat would you like to do?");
  Serial.println("1) Control location servo");
  Serial.println("2) Control beat stick servo");
  Serial.println("3) Play song portion");

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
  } 

  // User chooses to move beat stick servo
  else if (ans == 2) {
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

  else {
    Serial.println("You chose play song");
    Serial.println("What song portion would you like to play?");
    Serial.println("1) Half of 1st portion\n2) Full 1st\n3) Full 2nd\n4) Full 3rd\n5) Full song");

    while (Serial.available() == 0) {}
    input = Serial.readString();
    ans = input.toInt();

    if (ans == 1) {
      play(song1_half, size1_half);
    }

    else if (ans == 2) {
      play(song1, size1);
    }

    else if (ans == 3) {
      play(song2, size2);
    }

    else if (ans == 4) {
      play(song3, size3);
    }
    
    else if (ans == 5) {
      play(song1, size1);
      delay(1000);
      play(song2, size2);
      delay(1000);
      play(song1, size1);
      delay(1000);
      play(song3, size3);
    }
  }
  


  // END LOOP AND RESTART
  delay(1000);

}
