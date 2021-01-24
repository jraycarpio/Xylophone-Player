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



#include <Stepper.h>
#include <Servo.h>





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

// Define Variables:

// Number of Steps Required
int StepsRequired;

// Create Instance of Stepper Class
// Specify Pins used for motor coils
// The pins used are 8,9,10,11 
// Connected to ULN2003 Motor Driver In1, In2, In3, In4 
// Pins entered in sequence 1-3-2-4 for proper step sequencing
Stepper steppermotor(STEPS_PER_REV, 8, 10, 9, 11);

// Position value holder
int stepperPos;

// ___________ END STEPPER ___________



// ___________ SERVO ___________

Servo myservo;

// ___________ END SERVO ___________



// ___________ LIMIT SWITCH ___________

const int LSWITCH = 2;
boolean switchHit;
int switchState = 0;

// ___________ END LIMIT SWITCH ___________


// ___________ DEFINE FUNCTIONS ___________

void hitKey()
{
  myservo.write(90);
  delay(200);
  myservo.write(110);
  delay(200);
}

int moveStepper(int desired, int currentPos)  // Also writes/records position
{
  steppermotor.step(desired);
  int position = currentPos + desired;
  return position;
}

int returnStart(int currentPos)
{
  int returnVal = currentPos - 250;
  returnVal = (-1) * returnVal;
  int restart = moveStepper(returnVal, currentPos);
  return restart;
}

// ___________ END FUNCTIONS ___________



// ___________ RUGRATS SONG ___________


int note = 410;

// Note that the first note will be the starting position of the robot
int rugrats[] = {0, note, note, note, note, note, (-1)*note, (-2)*note, note, (-1)*note, (-1)*note,   note, note, note, note, note, note, note, (-2)*note, note, (-1)*note, (-1)*note,   note, note, note, note, note, note, (-1)*note, (-2)*note, note, (-1)*note, (-1)*note,   note, note, note, note, note, note, note, (-1)*note, (-1)*note, (-1)*note, (-1)*note, (-1)*note, (-1)*note};

int count = 500;  // Delay between certain notes
int size = 45;    // Size of song array

// ___________ END RUGRATS SONG ___________





// -------------------------------------------
// End definitions, constants, functions
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

    
  // Calibration sequence
  Serial.println("Calibrating...");
  
  switchHit = false;
  steppermotor.setSpeed(1000);    
  int Steps  =  -205;
  
  while (switchHit == false) {
    steppermotor.step(Steps);
    switchState = digitalRead(LSWITCH);

    if (switchState = HIGH) {
      Serial.println("\nLIMIT SWITCH HIT.\n");
      switchHit = true;
    } else {
      Serial.println("Limit not yet determined.");


      // SIMULATION__________
      Serial.println("starting simulation in 5 seconds");
      switchHit = true;
    }

    delay(500);
  }

  // Move stepper motor 250 steps and define current position.  
  // Step 250 will be starting point of robot.
  stepperPos = moveStepper(250, 0);
  
  Serial.println("\nCalibration complete.");
  Serial.println("\n\n");
  
  delay(1000);
}

void loop()
{
  Serial.println("Now playing: Rugrats Theme Song\n\n");
  delay(1000);
  Serial.println("Starting in 5...");
  delay(1000);
  Serial.println("Starting in 4...");
  delay(1000);
  Serial.println("Starting in 3...");
  delay(1000);
  Serial.println("Starting in 2...");
  delay(1000);
  Serial.println("Starting in 1...\n");
  delay(1000);
  Serial.println("\n\n");
  
  for (int i = 0; i <= size; i++) {
   
    Serial.print("STEP ------ ");
    Serial.print(i);
    Serial.print(", ");
    Serial.print(rugrats[i]);
    Serial.println(" step size");
    Serial.println("Current position is: ");
    Serial.println(stepperPos);

    stepperPos = moveStepper(rugrats[i], stepperPos);
    hitKey();

    if (i == 5) {
      Serial.println("Delay 500 ms");
      delay(count);
    }

    if (i == 6) {
      Serial.println("Delay 500 ms");
      delay(count);
    }

    if (i == 10) {
      Serial.println("Delay 700 seconds");
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

  Serial.println("FINISHED.");
  delay(1000);

  // Return to starting point
  stepperPos = returnStart(stepperPos);
  
  Serial.println("Restarting sequence in 5 seconds...\n");
  delay(5000);

}
