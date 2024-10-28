// function when invalid amount is found
void motor5()
{
  tft.setTextColor(WHITE);
    
  tft.fillScreen(BLACK); // Set background color to pink

  tft.setTextColor(BLACK);
  tft.setFont(&FreeMono9pt7b);
  tft.setCursor(20,80);
  tft.drawRect(10,10,460,300,WHITE);
  drawTextWithBorder("INVALID AMOUNT", 10, 200, 3, BLACK, RED);
  tft.setFont(&FreeSansBold12pt7b);
  drawTextWithBorder("SORRY :(", 80,120, 3, BLACK,MAGENTA);
  delay(2000);
  tft.setFont();
  resetArduino();
  
}
