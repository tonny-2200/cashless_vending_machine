// function user interface of buttons
void buttons()
{
    Serial.begin(9600);
    uint16_t ID = tft.readID();
    Serial.print("TFT ID = 0x");
    Serial.println(ID, HEX);
    Serial.println("Calibrate for your Touch Panel");
    if (ID == 0xD3D3) ID = 0x9486; // write-only shield
    tft.begin(ID);
    tft.setRotation(1); 
   
    tft.setTextColor(WHITE);
   
    tft.fillScreen(BLACK); // Set background color to pink
    on_btn.initButton(&tft,  120, 230, 180,80, RED, CYAN,BLACK, "MINT", 2);
    off_btn.initButton(&tft ,350, 230, 180,80, RED, CYAN,BLACK, "STRAWBERY", 2);
    tft.setFont();
    on_btn.drawButton(false);
    off_btn.drawButton(false);
    tft.setTextColor(BLACK);
    tft.setFont(&FreeMono9pt7b);
    tft.setCursor(20,80);
    tft.drawRect(5,5,468,300,WHITE);
    drawTextWithBorder("CHOOSE TIC-TAC FLAVOR", 10, 140, 2, BLACK, YELLOW);
    tft.setFont(&FreeSansBold12pt7b);
    drawTextWithBorder("Hello !!", 160, 70, 2, BLACK,RED);
    tft.setFont();
}

void drawTextWithBorder(const char* text, int x, int y, int textSize, uint16_t textColor, uint16_t borderColor) {
  // Draw text with a border
  tft.setTextSize(textSize);
  tft.setTextColor(borderColor);
  tft.setCursor(x - 1, y);
  tft.print(text);
  tft.setCursor(x + 1, y);
  tft.print(text);
  tft.setCursor(x, y - 1);
  tft.print(text);
  tft.setCursor(x, y + 1);
  tft.print(text);

  tft.setTextColor(textColor);
  tft.setCursor(x, y);
  tft.print(text);
}

