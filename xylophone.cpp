/*
 * Robotic Xylophone Player
 * 
 * By: Jonathan R. Carpio
 * Date: January 24, 2021
 * 
 * For Mark Rober's Monthly Class
 * Project 2: Electronic Art
 * 
 */



// -------------------------------------------
// Include stepper and servo libraries
// -------------------------------------------
#include <Stepper.h>
#include <Servo.h>



// ===========================================
// ===========================================



// -------------------------------------------
// Definitions, constants, functions
// -------------------------------------------

// ___________ STEPPER ___________

// Define Constants:

// Number of steps per internal motor revolution 
const float STEPS_PER_REV = 32; 

//  Amount of Gear Reduction
const float GEAR_RED = 64;

// Number of steps per geared output rotation
const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED;

// *****2048 steps for 1 full revolution*****

// Create Instance of Stepper Class
// Specify Pins used for motor coils
// The pins used are 8,9,10,11 
// Connected to ULN2003 Motor Driver In1, In2, In3, In4 
// Pins entered in sequence 1-3-2-4 for proper step sequencing
Stepper steppermotor(STEPS_PER_REV, 8, 10, 9, 11);

// Position value holder
int stepperPos;

// ___________ END STEPPER ___________
// ___________________________________



// ___________ SERVO ___________

Servo myservo;

// ___________ END SERVO ___________
// _________________________________



// ___________ LIMIT SWITCH ___________

const int LSWITCH = 2;
boolean switchHit;
int switchState = 0;

// ___________ END LIMIT SWITCH ___________
// ________________________________________


// ___________ DEFINE FUNCTIONS ___________

// Hit xylophone key
void hitKey()
{
  myservo.write(90);
  delay(200);
  myservo.write(110);
  delay(200);
}

// Move to desired key and record current position
int moveStepper(int desired, int currentPos)
{
  steppermotor.step(desired);
  int position = currentPos + desired;
  return position;
}

// Reset robot and return to starting position
int returnStart(int currentPos)
{
  int returnVal = currentPos - 250;
  returnVal = (-1) * returnVal;
  steppermotor.step(returnVal);
  return 250;
}

// ___________ END FUNCTIONS ___________
// _____________________________________



// ___________ RUGRATS SONG ___________

// Standard step size for moving to next note
int note = 410;

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
  myservo.attach(3);
  pinMode(LSWITCH, INPUT);
  
  Serial.begin(9600);
  Serial.println("\n\nBREAK ----");
  Serial.println("BREAK ----");
  Serial.println("BREAK ----");
  Serial.println("BREAK ----");
  Serial.println();
  Serial.println();
  Serial.println();

  delay(2000);
  Serial.println("SYSTEM STARTING IN\n");
  delay(500);
  Serial.println("3...");
  delay(1000);
  Serial.println("2...");
  delay(1000);
  Serial.println("1...\n\n");
  delay(1000);

    
  // Calibration sequence
  Serial.println("Calibrating...");
  
  switchHit = false;
  steppermotor.setSpeed(1000);    
  
  while (switchHit == false) {
    steppermotor.step(-205);
    switchState = digitalRead(LSWITCH);

    if (switchState = HIGH) {
      Serial.println("\nLIMIT SWITCH HIT.\n");
      switchHit = true;
    } else {
      Serial.println("Moving to bottom limit...");
    }

    delay(750);
  }

  // Move stepper motor 250 steps and define current position  
  // Step 250 will be starting point of robot
  stepperPos = moveStepper(250, 0);
  
  Serial.println("\nCalibration complete.\n");
  delay(1000);
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
   
    stepperPos = moveStepper(rugrats[i], stepperPos);
    hitKey();

    // Update status on serial monitor
    Serial.print("STEP ------ ");
    Serial.print(i);
    Serial.print(", ");
    Serial.print(rugrats[i]);
    Serial.println(" step size");
    Serial.print("Current position is: ");
    Serial.println(stepperPos);

    // Delay the time between certain notes
    if (i == 5) {
      Serial.println("Delay 500 ms");
      delay(count);
    }

    if (i == 6) {
      Serial.println("Delay 500 ms");
      delay(count);
    }

    if (i == 10) {
      Serial.println("Delay 700 ms");
      delay(count+200);
    }

    if (i == 16) {
      Serial.println("Delay 500 ms");
      delay(count);
    }

    if (i == 17) {
      Serial.println("Delay 500 ms");
      delay(count);
    }

    if (i == 21) {
      Serial.println("Delay 500 ms");
      delay(count);
    }

    if (i == 27) {
      Serial.println("Delay 500 ms");
      delay(count);
    }

    if (i == 28) {
      Serial.println("Delay 500 ms");
      delay(count);
    }

    if (i == 32) {
      Serial.println("Delay 700 ms");
      delay(count + 200);
    }

    if (i == 44) {
      Serial.println("Delay 500 ms");
      delay(count);
    }

    Serial.println();
    
  }

  Serial.println("\nFINISHED.");
  delay(2000);

  // Return to starting point and restart loop sequence
  Serial.println("Resetting robot...");
  stepperPos = returnStart(stepperPos);
  Serial.print("Current position: ");
  Serial.println(stepperPos);
  delay(1000);
  Serial.println("Restarting sequence in 5 seconds...\n");
  delay(5000);

}
