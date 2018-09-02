
/*  Pulse Sensor Amped 1.5
----------------------  Notes ----------------------  ----------------------
This code:
Determines BPM and Prints to LCD 16x2
 ----------------------       ----------------------  ----------------------
*/

#include "ShiftLCD.h"

//  Variables
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0

//  LCD pins
uint8_t DATAPIN = 11;//SER   - Data
uint8_t CLOCKPIN = 12;//SCK  - Clock
uint8_t LATCHPIN = 13;//RCK  - Reset Clock

boolean clean_LCD = true;

const String lbl_BPM = "BPM: ";
const String lbl_IBI = "IBI: "; 
const String lbl_Pulse = " Pulse:";

// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded!
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat".
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

// initialize the library with the numbers of the interface pins
ShiftLCD lcd(DATAPIN, CLOCKPIN, LATCHPIN, 4);

void setup(){
  // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
    lcd.setCursor(0, 0);
    lcd.print("   I LOVE YOU   ");
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    lcd.print(" *** PRANSH ***");
    interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS 
  //IF YOU ARE POWERING The Pulse Sensor AT VOLTAGE LESS THAN THE BOARD VOLTAGE, UN-COMMENT THE NEXT LINE AND APPLY THAT VOLTAGE TO THE A-REF PIN
  //  analogReference(EXTERNAL);
}


//  Where the Magic Happens
void loop(){
  if (QS == true){     // A Heartbeat Was Found BPM and IBI have been Determined Quantified Self "QS" true when arduino finds a heartbeat
    if(clean_LCD){
        lcd.setCursor(0, 0);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        lcd.print("                ");
        clean_LCD = false;
    }
    // A Beat Happened, Print a message to the LCD.
    lcd.setCursor(0, 0);
    lcd.print(lbl_BPM + BPM + lbl_Pulse + Pulse);
    lcd.setCursor(0, 1);
    lcd.print(lbl_IBI + IBI);
    QS = false;                      // reset the Quantified Self flag for next time
  }
  delay(20);                             //  take a break
}
