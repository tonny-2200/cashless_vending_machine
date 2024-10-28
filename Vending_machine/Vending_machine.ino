// Importing libraries
#include <MCUFRIEND_kbv.h>
#include <SoftwareSerial.h>
#include <TouchScreen.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include<Fonts/FreeMono12pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>
#define MINPRESSURE 200
#define MAXPRESSURE 1000
MCUFRIEND_kbv tft;

const int XP = 6, XM = A2, YP = A1, YM = 7;
const int TS_LEFT = 977, TS_RT = 184, TS_TOP = 176, TS_BOT = 950;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button on_btn, off_btn;

// Define colors
#define WHITE 0xFFFF
#define BLACK 0x000000
#define GREEN 0x00FF00
#define GREEN2   0x07E0
#define GRAY    0x7BEF
#define YELLOW  0xFFE0
#define CYAN    0x07FF
#define RED 0xf800
#define BLUE    0x001F
#define MAGENTA 0xF81F
#define SKY_BLUE 0x87CEEB
#define DARK_BLUE 0x00008B

// Defining pins for motors and its direction
#define motor1PWM 45  
#define motor1Dir 23   
#define motor2PWM 44  
#define motor2Dir 25  
// Variables
int motorSpeed = 100; // Adjust the speed as needed
int rotationDelay = 1000; // Time delay for one rotation in milliseconds
int counter = 0;
int count = 0;
int pixel_x, pixel_y;     //Touch_getXY() updates global vars
bool Touch_getXY(void)
{
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        pixel_x = map(p.y, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
        pixel_y = map(p.x, TS_TOP, TS_BOT, 0, tft.height());
    }
    return pressed;
}
//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(52, 53); 
String receivedData = "";


void setup()
{ 
  //TFT setup
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  mySerial.begin(9600);
  //Begin serial communication with Arduino and SIM800L
  Serial.begin(9600);
  // Send AT command and check for "OK" response from SIM800L
  mySerial.println("AT");
  updateSerial();
  mySerial.println("AT+CMGF=1");
  updateSerial();
  mySerial.println("AT+CNMI=1,2,0,0,0");
  updateSerial();
  uint16_t ID = tft.readID();
  if (ID == 0xD3D3) ID = 0x9486; // write-only shield
  tft.begin(ID);
  tft.setRotation(1);
  tft.setRotation(1); 
  tft.setTextColor(WHITE);
  tft.fillScreen(BLACK); // Set background color to pink
  tft.setTextColor(BLACK);
  tft.setFont(&FreeMono12pt7b);
  tft.setCursor(20,80);
  tft.drawRect(10,10,460,300,WHITE);
  drawTextWithBorder("MOUTH FRESH ", 90, 60, 2, BLACK, WHITE);
  drawTextWithBorder("MOOD REFRESH:) ",60, 110, 2, BLACK, GREEN2);
  tft.setFont(&FreeSansBold12pt7b);
  drawTextWithBorder("Please Make", 100,200, 2, BLACK,WHITE);
  drawTextWithBorder(" $Payment$", 110,250, 2, BLACK,GREEN2);
  tft.setFont();
}
  

void loop() {
  updateSerial();
  // Extraction
  int amount = extractAmount(receivedData);
  if (amount == 10) {
    Serial.println("Amount extracted: " + String(amount)); // Print amount to serial monitor
    // Print received data on the display
    motor1();
    
    receivedData = "";
  } 
  else if (amount == 20){
    Serial.println("Amount extracted: " + String(amount)); // Print amount to serial monitor
    // Print received data on the display
    motor2();
    receivedData = "";
  } 
  else if (amount != 20 && amount != 10 && amount != 0){
    Serial.println("Amount extracted: " + String(amount)); // Print amount to serial monitor
    // Print received data on the display
    motor5();
    receivedData = "";
  } 
  // Wait for a new SMS message before proceeding
  while (!Serial.available() && !mySerial.available()) {
    delay(1000);
  }
  
} 
 
void updateSerial() {
  delay(500);
  while (Serial.available()) {
    char c = Serial.read();
    mySerial.write(c);
    receivedData += c;
    if (c == '\n') {
      if (receivedData.startsWith("AT") || receivedData.startsWith("OK")) {
        receivedData = "";
      }
    }
  }
  while (mySerial.available()) {
    char c = mySerial.read();
    Serial.write(c);
    receivedData += c;
    if (c == '\n') {
      if (receivedData.startsWith("AT") || receivedData.startsWith("OK")) {
        receivedData = "";
      }
    }
  }
}
int extractAmount(String text) {
  // Find the position of "Rs." in the SMS
  int rsIndex = text.indexOf("Received Rs.");
  if (rsIndex != -1) {
    // Extract the amount following "Rs."
    String amountString = text.substring(rsIndex + 12);
    // Convert the amount string to an integer
    int amount = amountString.toInt();
    return amount;
  } else {
    return 0; // Return 0 if "Rs." is not found in the SMS
  }
}