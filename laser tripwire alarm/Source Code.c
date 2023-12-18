#include <Keypad.h>
#define laser 5
#define buzzer 22
#define sensor 18

double sensorReading;

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
char keys[ROWS][COLS] = { // Define the keys on the keypad
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = { 32, 33, 25, 26 }; // Connect keypad ROW0, ROW1, ROW2 and ROW3 to these ESP32 pins.
byte colPins[COLS] = { 27, 14, 12, 13 }; // Connect keypad COL0, COL1, COL2 and COL3 to these ESP32 pins.
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
char* correctPass = "93175"; 
char* resetPass   = "75368"; 

void setup() {
  digitalWrite(laser, HIGH); 
  digitalWrite(buzzer, LOW); 
  Serial.begin(9600); 
  pinMode(laser, OUTPUT); 
  pinMode(sensor, INPUT); 
  pinMode(buzzer, OUTPUT); 
   
}

void loop() {
  sensorReading = digitalRead(sensor); 
  if (sensorReading == LOW) {
    digitalWrite(laser, HIGH); 
    digitalWrite(buzzer, LOW); 
  }
  else if (sensorReading == HIGH) {
    Serial.println("ALERT! Intruder detected!"); 
    Serial.print("Enter password to stop the alarm: ");
    do {
      digitalWrite(buzzer, HIGH); 
      digitalWrite(laser, HIGH); 
    }
    while(checkPassword(correctPass) == false); 
    digitalWrite(buzzer, LOW);
    digitalWrite(laser, LOW); 
    Serial.print("Enter password to reset the security system: "); 
    if (checkPassword(resetPass) == true) {
      Serial.println("Resetting...\n"); 
      digitalWrite(laser, HIGH); 
      digitalWrite(buzzer, LOW); 
    } 
  }
}

bool checkPassword(char* password) {
  char input[6];
  int i = 0;
  while (i < 5) {
    char key = keypad.getKey();
    if (key != NO_KEY) {
      Serial.print(key); 
      input[i] = key;
      i++;
    }
  }
  input[5] = '\0';
  if (strcmp(input, password) == 0) {
    Serial.println("\nCORRECT PASS!"); 
    return true;
  } else {
    Serial.println("\nINCORRECT PASS!"); 
    return false;
  }
}