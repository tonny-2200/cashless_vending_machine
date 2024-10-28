// function when tic-tac is dispensed
void gk()
{
  tft.setRotation(1); 
  tft.setTextColor(WHITE); 
  tft.fillScreen(BLACK); // Set background color to pink
  tft.setTextColor(BLACK);
  tft.setFont(&FreeMono12pt7b);
  tft.setCursor(20,80);
  tft.drawRect(8,8,460,300,WHITE);
  drawTextWithBorder("TicTac Dispensed", 12, 200, 2, BLACK, BLUE);
  tft.setFont(&FreeSansBold12pt7b);
  drawTextWithBorder("THANK-YOU :)", 80,120, 2, BLACK,WHITE);
  tft.setFont();
  resetArduino();
}