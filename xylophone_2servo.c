/*
 * Robotic Xylophone Player
 * Double Servo configuration (no stepper)
 * 
 * By: Jonathan R. Carpio
 * Date: January 24, 2021
 * 
 * For Mark Rober's Monthly Class
 * Project 2: Electronic Art
 * 
 */



// -------------------------------------------
// Include servo library
// -------------------------------------------
#include <Servo.h>



// ===========================================
// ===========================================



// -------------------------------------------
// Definitions, constants, functions
// -------------------------------------------


// ___________ SERVO ___________

Servo beatStick;
Servo location;

int position;

// ___________ END SERVO ___________
// _________________________________


// ___________ DEFINE FUNCTIONS ___________

// Hit xylophone key
void hitKey()
{
  beatStick.write(90);
  delay(200);
  beatStick.write(110);
  delay(200);
}


// Move to specified xylophone key and record position
int movePos(int desired, int currentPos)
{
  currentPos = currentPos + desired;

  if (currentPos < 0) {
      while (true) {
        Serial.print("\n\nERROR: NEGATIVE POSITION CALCULATED = (");
        Serial.print(currentPos);
        Serial.println(" steps).  CANNOT MOVE SERVO.\n\n");
        delay(5000);
      }
    }
  
  
  location.write(desired);
  return currentPos; 
}


// Reset robot and return to starting position
int returnStart(int currentPos)
{
  int returnVal = currentPos * (-1);
  location.write(returnVal);
  return 0;
}

// ___________ END FUNCTIONS ___________
// _____________________________________



// ___________ RUGRATS SONG ___________

// Standard step size for moving to next note
int note = 24;

// Define song sequence as a set of motor positions
// Note that the first note will be the starting position of the robot
int rugrats[] = {0, note, note, note, note, note, (-1)*note, (-2)*note, note, (-1)*note, (-1)*note,   (-1)*note, note, note, note, note, note, note, (-2)*note, note, (-1)*note, (-1)*note,   (-3)*note, note, note, note, note, note, (-1)*note, (-2)*note, note, (-1)*note, (-1)*note,   (-1)*note, note, note, note, note, note, note, (-1)*note, (-1)*note, (-1)*note, (-1)*note, (-1)*note, (-1)*note};

int count = 500;  // Delay between certain notes
int size = 45;    // Size of song array

// ___________ END RUGRATS SONG ___________
// ________________________________________





// ===========================================
// ===========================================





// -------------------------------------------
// System setup
// -------------------------------------------

void setup()
{
  Serial.begin(9600);
  Serial.println("\n\nBREAK ----");
  Serial.println("BREAK ----");
  Serial.println("BREAK ----");
  Serial.println("BREAK ----");
  Serial.println();
  Serial.println();
  Serial.println();

  delay(1000);
  Serial.println("SYSTEM STARTING IN\n");
  delay(1000);
  Serial.println("3...");
  delay(1000);
  Serial.println("2...");
  delay(1000);
  Serial.println("1...");
  delay(1000);

  Serial.println("\nCalibrating servos...");
  beatStick.attach(3);
  location.attach(5);

  delay(500);

  beatStick.write(110);
  location.write(10);
  position = 10;

  delay(1000);

  Serial.println("Calibration completed.");

  delay(1000);

  Serial.println("\n\n");
}



// ===========================================
// ===========================================



// -------------------------------------------
// Loop sequence
// -------------------------------------------

void loop()
{
  Serial.println("Now playing: Rugrats Theme Song\n\n");
  delay(1000);

  // Loop function: move to each consecutive step in the Rugrats song array and hit the key
  for (int i = 0; i <= size; i++) {

    position = movePos(rugrats[i], position);
    hitKey();

    // Update status on serial monitor
    Serial.print("STEP ------ ");
    Serial.print(i);
    Serial.print(", ");
    Serial.print(rugrats[i]);
    Serial.println(" step size");
    Serial.print("Current position: ");
    Serial.println(position);

    // Delay the time between certain notes
    if (i == 5) {
      Serial.print("Delay ");
      Serial.print(count);
      Serial.println(" ms");
      delay(count);
    }

    else if (i == 6) {
      Serial.print("Delay ");
      Serial.print(count);
      Serial.println(" ms");
      delay(count);
    }

    else if (i == 10) {
      Serial.print("Delay ");
      Serial.print(count + 200);
      Serial.println(" ms");
      delay(count + 200);
    }

    else if (i == 16) {
      Serial.print("Delay ");
      Serial.print(count);
      Serial.println(" ms");
      delay(count);
    }

    else if (i == 17) {
      Serial.print("Delay ");
      Serial.print(count);
      Serial.println(" ms");
      delay(count);
    }

    else if (i == 21) {
      Serial.print("Delay ");
      Serial.print(count);
      Serial.println(" ms");
      delay(count);
    }

    else if (i == 27) {
      Serial.print("Delay ");
      Serial.print(count);
      Serial.println(" ms");
      delay(count);
    }

    else if (i == 28) {
      Serial.print("Delay ");
      Serial.print(count);
      Serial.println(" ms");
      delay(count);
    }

    else if (i == 32) {
      Serial.print("Delay ");
      Serial.print(count + 200);
      Serial.println(" ms");
      delay(count + 200);
    }

    else if (i == 44) {
      Serial.print("Delay ");
      Serial.print(count);
      Serial.println(" ms");
      delay(count);
    }

    else {
      Serial.print("Delay ");
      Serial.print("0");
      Serial.println(" ms");
    }
    Serial.println();
    
  }

  Serial.println("\nFINISHED.");
  delay(2000);

  // Return to starting point
  Serial.println("Resetting robot...");
  position = returnStart(position);
  Serial.print("\nCurrent position: ");
  Serial.println(position);
  
  delay(1000);
  
  Serial.println("\nRestarting sequence in 5 seconds...\n");
  
  delay(5000);

}
