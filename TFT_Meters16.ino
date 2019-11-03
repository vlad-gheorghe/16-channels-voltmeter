/*
 Example animated analogue meters using a HX8357 TFT LCD screen

 Needs Font 2

 */

#include <TFT_HX8357.h> // Hardware-specific library

TFT_HX8357 tft = TFT_HX8357();       // Invoke custom library

#define TFT_GREY 0x5AEB

uint32_t updateTime = 0;       // time for next update

int value[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int old_value[16] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int d = 0;

void setup(void) {
  tft.init();
  tft.setRotation(1);
  Serial.begin(57600); // For debug
  tft.fillScreen(TFT_BLACK);

  // Draw 16 linear meters
  byte d = 60;
  plotLinear("A0", 0 * d, 0);
  plotLinear("A1", 1 * d, 0);
  plotLinear("A2", 2 * d, 0);
  plotLinear("A3", 3 * d, 0);
  plotLinear("A4", 4 * d, 0);
  plotLinear("A5", 5 * d, 0);
  plotLinear("A6", 6 * d, 0);
  plotLinear("A7", 7 * d, 0);

  plotLinear("B0", 0 * d, 160);
  plotLinear("B1", 1 * d, 160);
  plotLinear("B2", 2 * d, 160);
  plotLinear("B3", 3 * d, 160);
  plotLinear("B4", 4 * d, 160);
  plotLinear("B5", 5 * d, 160);
  plotLinear("B6", 6 * d, 160);
  plotLinear("B7", 7 * d, 160);

  updateTime = millis(); // Next update time
}


void loop() {
  if (updateTime <= millis()) {
    updateTime = millis() + 25; // Delay to limit speed of update
 
    d += 4; if (d >= 360) d = 0;

    // Create a Sine wave for testing, must be a vlaue in range 0-100
    /*value[0] = 50 + 50 * sin((d + 0) * 0.0174532925);
    value[1] = 50 + 50 * sin((d + 60) * 0.0174532925);
    value[2] = 50 + 50 * sin((d + 120) * 0.0174532925);
    value[3] = 50 + 50 * sin((d + 180) * 0.0174532925);
    value[4] = 50 + 50 * sin((d + 240) * 0.0174532925);
    value[5] = 50 + 50 * sin((d + 300) * 0.0174532925);
    value[6] = 50 + 50 * sin((d + 0) * 0.0174532925);
    value[7] = 50 + 50 * sin((d + 60) * 0.0174532925);
    value[8] = 50 + 50 * sin((d + 120) * 0.0174532925);
    value[9] = 50 + 50 * sin((d + 180) * 0.0174532925);
    value[10] = 50 + 50 * sin((d + 240) * 0.0174532925);
    value[11] = 50 + 50 * sin((d + 300) * 0.0174532925);
    value[12] = 50 + 50 * sin((d + 0) * 0.0174532925);
    value[13] = 50 + 50 * sin((d + 60) * 0.0174532925);
    value[14] = 50 + 50 * sin((d + 120) * 0.0174532925);
    value[15] = 50 + 50 * sin((d + 180) * 0.0174532925);*/

     // The value placed in the value[] array must be mapped to the range 0-100
    value[0] = map(analogRead(A0), 0, 1023, 0, 100); // Test with value form Analogue 0
    value[1] = map(analogRead(A1), 0, 1023, 0, 100); // Test with value form Analogue 1
    value[2] = map(analogRead(A2), 0, 1023, 0, 100); // Test with value form Analogue 2
    value[3] = map(analogRead(A3), 0, 1023, 0, 100); // Test with value form Analogue 3
    value[4] = map(analogRead(A4), 0, 1023, 0, 100); // Test with value form Analogue 4
    value[5] = map(analogRead(A5), 0, 1023, 0, 100); // Test with value form Analogue 5
    value[6] = map(analogRead(A6), 0, 1023, 0, 100); // Test with value form Analogue 6
    value[7] = map(analogRead(A7), 0, 1023, 0, 100); // Test with value form Analogue 7
    value[8] = map(analogRead(A8), 0, 1023, 0, 100); // Test with value form Analogue 8
    value[9] = map(analogRead(A9), 0, 1023, 0, 100); // Test with value form Analogue 9
    value[10] = map(analogRead(A10), 0, 1023, 0, 100); // Test with value form Analogue 10
    value[11] = map(analogRead(A11), 0, 1023, 0, 100); // Test with value form Analogue 11
    value[12] = map(analogRead(A12), 0, 1023, 0, 100); // Test with value form Analogue 12
    value[13] = map(analogRead(A13), 0, 1023, 0, 100); // Test with value form Analogue 13
    value[14] = map(analogRead(A14), 0, 1023, 0, 100); // Test with value form Analogue 14
    value[15] = map(analogRead(A15), 0, 1023, 0, 100); // Test with value form Analogue 15
   


    //unsigned long t = millis(); 
    plotPointer(); // It takes aout 3.5ms to plot each gauge for a 1 pixel move
    //Serial.println(millis()-t); // Print time taken for meter update
  }
}


// #########################################################################
//  Draw a linear meter on the screen
// #########################################################################
void plotLinear(char *label, int x, int y)
{
  int w = 56;
  tft.drawRect(x, y, w, 155, TFT_GREY);
  tft.fillRect(x+2, y + 19, w-3, 155 - 38, TFT_WHITE);
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.drawCentreString(label, x + w / 2, y + 2, 2);

  for (int i = 0; i < 110; i += 10)
  {
    tft.drawFastHLine(x + 40, y + 27 + i, 6, TFT_BLACK);
  }

  for (int i = 0; i < 110; i += 50)
  {
    tft.drawFastHLine(x + 40, y + 27 + i, 9, TFT_BLACK);
  }
  
  tft.fillTriangle(x+3, y + 127, x+3+36, y+127, x + 3, y + 127 - 5, TFT_RED);
  tft.fillTriangle(x+3, y + 127, x+3+36, y+127, x + 3, y + 127 + 5, TFT_RED);
  
  tft.drawCentreString("---", x + w / 2, y + 155 - 18, 2);
}

// #########################################################################
//  Adjust 16 linear meter pointer positions
//  value[x] must be in range 0-100
// #########################################################################
void plotPointer(void)
{
  int  dy = 47;
  byte pw = 36;

  tft.setTextColor(TFT_GREEN, TFT_BLACK);

  // Move the 16 pointers one pixel towards new value
  for (int i = 0; i < 16; i++)
  {
    int my = 160;
    if (i < 8) my = 0;
    char buf[8]; dtostrf(value[i], 4, 0, buf);

    int dx = 3 + 60 * i;
    if (i > 7) dx -= 8 * 60;
    tft.drawRightString(buf, dx + 33 - 5, my + 155 - 18, 2);

    if (value[i] < 0) value[i] = 0; // Limit value to emulate needle end stops
    if (value[i] > 100) value[i] = 100;

    while (!(value[i] == old_value[i])) {
      dy = my + 27 + 100 - old_value[i];
      if (old_value[i] > value[i])
      {
        tft.drawLine(dx, dy - 5, dx + pw, dy, TFT_WHITE);
        old_value[i]--;
        tft.drawLine(dx, dy + 6, dx + pw, dy + 1, TFT_RED);
      }
      else
      {
        tft.drawLine(dx, dy + 5, dx + pw, dy, TFT_WHITE);
        old_value[i]++;
        tft.drawLine(dx, dy - 6, dx + pw, dy - 1, TFT_RED);
      }
    }
  }
}
