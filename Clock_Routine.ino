/***************************************************************************/
void drawBubbles()
/***************************************************************************/
{
  int loopControl, rndX, rndY;
  for (loopControl = 0; loopControl < 2000; loopControl++) {
    rndX = random(tft.width());
    rndY = random(tft.height());
    tft.fillCircle(rndX, rndY, random(40) + 4, GetRndRGB565());
    myWait(1);  // Just slow it down slightly for each circle.
  }
}
/***************************************************************************/
uint32_t GetRndRGB565()
/***************************************************************************/
{
  R = random(200) + 25;
  G = random(200) + 25;
  B = random(200) + 25;
  return (RGB565(R, G, B));
}
/***************************************************************************/
void myWait(unsigned long waitMillis)
/***************************************************************************/
{
  unsigned long startMillis = millis();
  while (millis() < startMillis + waitMillis) {
    //wait approx. [period] ms
  }
  return;
}
/***************************************************************************/
void draw_Clock_Face()
/****draw_Clock_Face********************************************************/
{
  int indiciaNear = dispHeight * 0.43;  // 0.408333333;  // By ratio
  int indiciaFar = dispHeight * 0.48;   // By ratio
  int nearX, nearY, farX, farY;
  int nearX1, nearY1, farX1, farY1;
  int nearX2, nearY2, farX2, farY2;

  // draw hour pointers around the face of a clock
  for (int i = 0; i < 12; i++) {
    nearX  = (indiciaNear * sin(PI - (2 * PI) / 12 * i)) + xCenter;
    nearY  = (indiciaNear * cos(PI - (2 * PI) / 12 * i)) + yCenter;
    farX   = (indiciaFar  * sin(PI - (2 * PI) / 12 * i)) + xCenter;
    farY   = (indiciaFar  * cos(PI - (2 * PI) / 12 * i)) + yCenter;
    tft.drawLine(nearX, nearY, farX, farY, ILI9341_YELLOW);

    //These 4 will be thicker than the others (0, 3, 6, & 9).
    if (i == 0 || i == 6) {
      nearX1 = (indiciaNear * sin(PI - (2 * PI) / 12 * i)) + xCenter + 1;
      nearY1 = nearY;
      farX1  = (indiciaFar  * sin(PI - (2 * PI) / 12 * i)) + xCenter + 1;
      farY1  = farY;
      nearX2 = (indiciaNear * sin(PI - (2 * PI) / 12 * i)) + xCenter - 1;
      nearY2 = nearY;
      farX2  = (indiciaFar  * sin(PI - (2 * PI) / 12 * i)) + xCenter - 1;
      farY2  = farY;
    }
    if (i == 3 || i == 9) {
      nearX1 = nearX; nearY1 = (indiciaNear * cos(PI - (2 * PI) / 12 * i)) +
                               yCenter + 1;
      farX1  = farX;  farY1  = (indiciaFar  * cos(PI - (2 * PI) / 12 * i)) +
                               yCenter + 1;
      nearX2 = nearX; nearY2 = (indiciaNear * cos(PI - (2 * PI) / 12 * i)) +
                               yCenter - 1;
      farX2  = farX;  farY2  = (indiciaFar  * cos(PI - (2 * PI) / 12 * i)) +
                               yCenter - 1;
    }
    if (i % 3 == 0) {
      tft.drawLine(nearX1, nearY1, farX1, farY1, ILI9341_YELLOW);
      tft.drawLine(nearX2, nearY2, farX2, farY2, ILI9341_YELLOW);
    }
  }
}
/***************************************************************************/
void draw_Hands(int hour, int minute, int second)
/****draw_Hands*************************************************************/
{
  float handRadians;

  // Settings for 240

  // Length of the pointer end of the hand.
  //  int hourHandLength = 48;
  // Length the twin tails.
  //  int HourHandBackLength = 15;
  //
  // Length of the pointer end of the hand.
  //  int minuteHandLength = 62;
  // Length the twin tails.
  //  int minuteHandBackLength = 19;

  // By ratio

  // Length of the pointer end of the hand.
  int hourHandLength = dispHeight * 0.2;
  // Length the twin tails.
  int HourHandBackLength =  dispHeight * 0.0625;

  // Length of the pointer end of the hand.
  int minuteHandLength = dispHeight * 0.258333333;
  // Length the twin tails.
  int minuteHandBackLength = dispHeight * 0.079166667;

  hour = hour % 12;  // Only 12 hour indicia on a clock face.
  // First, calculate the hand positions for both.
  // Each hour gives 30° to the hour hand.
  // Every minute gives 1/2° to the hour hand.
  handRadians = ((float(hour) * -30. - float(minute) / 2.) - 180) /
                57.2957795130823;
  // This is the tip of the pointer end.
  myHX  = (hourHandLength * sin(handRadians)) + xCenter;
  myHY  = (hourHandLength * cos(handRadians)) + yCenter;
  //Now calculate the hour hand overhang past the center for hour hand.
  //Do this twice with +/-20 degrees then draw 2 triangles.
  //  handRadians = ((float(hour) * -30. - float(minute) / 2.) - 20.)
  //                / 57.2957795130823;
  //  myHXb1  = (HourHandBackLength * sin(handRadians)) + xCenter;
  //  myHYb1  = (HourHandBackLength * cos(handRadians)) + yCenter;
  //  handRadians = ((float(hour) * -30. - float(minute) / 2.) + 20.)
  //                / 57.2957795130823;
  //  myHXb2  = (HourHandBackLength * sin(handRadians)) + xCenter;
  //  myHYb2  = (HourHandBackLength * cos(handRadians)) + yCenter;

  //Now calculate the minute hand.
  //Every minute gives 6° to the minute hand. Every second gives .1°
  // to the minute hand.
  handRadians = ((float(minute) * -6. - float(second) / 10.) - 180.)
                / 57.2957795130823;
  // This is the tip of the pointer end.
  myMX = (minuteHandLength * sin(handRadians)) + xCenter;
  myMY = (minuteHandLength * cos(handRadians)) + yCenter;
  //Now the back (short) side of the minute hand across the center.
  //Do this twice with +/-20 degrees then draw 2 triangles.
  //  handRadians = ((float(minute) * -6. - float(second) / 10.) - 20.)
  //                / 57.2957795130823;
  //  myMXb1 = (minuteHandBackLength * sin(handRadians)) + xCenter;
  //  myMYb1 = (minuteHandBackLength * cos(handRadians)) + yCenter;
  //  handRadians = ((float(minute) * -6. - float(second) / 10.) + 20.)
  //                / 57.2957795130823;
  //  myMXb2 = (minuteHandBackLength * sin(handRadians)) + xCenter;
  //  myMYb2 = (minuteHandBackLength * cos(handRadians)) + yCenter;

  //  eraseColor = DarkerRed;

#if defined DO_WEDGE_HANDS
  Serial.printf("Free Heap Size: %i\r\n",  esp_get_free_heap_size());
  Serial.print("uxTaskGetStackHighWaterMark: ");
  Serial.println(uxTaskGetStackHighWaterMark(NULL));
  tft.drawWedgeLine(myHX, myHY, xCenter, yCenter, 2, 8, TFT_RED);
  tft.drawWedgeLine(myMX, myMY, xCenter, yCenter, 2, 8, TFT_WHITE);
#else
  //  if (myIsPM) eraseColor = DarkerBlue;
  //If either hand moved, must erase and rewrite both.
  // initHands opens the timed gate early.
  if (homeTime.second() % 10 == 0 || initHands) {
    //First, see if this is a new place to draw.
    if (prevHX != myHX || prevMX != myMX || prevHY != myHY || prevMY != myMY
        || initHands) {  // initHands overrides the hands moved update check.
      initHands = false;
      if (prevHX < 10000) {  // Don't erase if nothing there already!
        //It is a new place to draw so remove the previous triangles
        tft.fillTriangle(xCenter, yCenter,
                         prevHX, prevHY,
                         prevHXb1,  prevHYb1,
                         eraseColor);
        tft.fillTriangle(xCenter, yCenter,
                         prevHX, prevHY,
                         prevHXb2, prevHYb2,
                         eraseColor);
      }
      if (prevMX < 10000) {  // Don't erase if nothing there already!
        //It is a new place to draw so remove the previous triangles
        tft.fillTriangle(xCenter, yCenter,
                         prevMX, prevMY,
                         prevMXb1,  prevMYb1,
                         eraseColor);
        tft.fillTriangle(xCenter, yCenter,
                         prevMX, prevMY,
                         prevMXb2,  prevMYb2,
                         eraseColor);
      }
      //Remember for next time through, for erasing.
      prevHX   = myHX;   prevHY   = myHY;
      prevHXb1 = myHXb1; prevHYb1 = myHYb1;
      prevHXb2 = myHXb2; prevHYb2 = myHYb2;
      prevMX   = myMX;   prevMY   = myMY;
      prevMXb1 = myMXb1; prevMYb1 = myMYb1;
      prevMXb2 = myMXb2; prevMYb2 = myMYb2;
      //Now, finally, put in the new hour and minute triangles.
      tft.fillTriangle(xCenter, yCenter, myHX, myHY,
                       myHXb1, myHYb1, HHDarker);
      tft.fillTriangle(xCenter, yCenter, myHX, myHY,
                       myHXb2, myHYb2, HHDarker);
      tft.fillTriangle(xCenter, yCenter, myMX, myMY,
                       myMXb1, myMYb1, MHDarker);
      tft.fillTriangle(xCenter, yCenter, myMX, myMY,
                       myMXb2, myMYb2, MHDarker);
    }
  }
#endif
  tft.fillSmoothCircle(xCenter, yCenter, 3, DarkerRed);
}
/***************************************************************************/
void update_Seconds(int currMin, int currSec)
/****update_Seconds*********************************************************/
{ // This routine takes about 3 ms.  Way more than I thought it would.
  // I force the dots because an hour dance may take longer than 1 second
  //  and that would leave the display messed up, so totally rebuild,
  //  every second.

  //  Serial.printf("%lu - Update Seconds\r\n", millis());
  // Testing -- didn't do anything  Don't have the first idea why!
  //  tft.fillRect(0, 0, tft.width(), 100, TFT_WHITE);

  int iMySec;

  if (currMin % 2 == 0) {
    // Even minute, drawing second dots from 1 to now
    for (iMySec = 1; iMySec <= currSec; iMySec++) draw_Seconds_Dot(iMySec, ILI9341_YELLOW);
    // Erasing each dot from now + 1 second through 60 seconds.
    for (iMySec = currSec + 1; iMySec <= 60; iMySec++) draw_Seconds_Dot(iMySec, DarkYellow);
  } else {
    // Odd minute, erasing second dots from 1 to now
    for (iMySec = 1; iMySec <= currSec; iMySec++) draw_Seconds_Dot(iMySec, DarkYellow);
    // Drawing each dot from now + 1 second through 60 seconds.
    for (iMySec = currSec + 1; iMySec <= 60; iMySec++) draw_Seconds_Dot(iMySec, ILI9341_YELLOW);
  }
}
/***************************************************************************/
void draw_Seconds_Dot(int iMySecond, unsigned int iMyColor)
/****draw_Seconds_Dot*******************************************************/
{
  // Not really hand length but the distance from center where the dot goes.
  handLength = dispHeight * 0.4;

  mySX = (handLength * sin(PI - (2 * PI) / 60 * iMySecond)) + xCenter;
  mySY = (handLength * cos(PI - (2 * PI) / 60 * iMySecond)) + yCenter;
  //  Serial.printf("%lu - %02i: iMyColor %i, mySX %i, mySY %i\r\n",
  //                iMySecond, millis(), iMyColor, mySX, mySY);
  tft.fillCircle(mySX, mySY, 25, iMyColor);
  //  tft.fillSmoothCircle(mySX, mySY, 4, iMyColor);
  //  tft.fillSmoothCircle(mySX, mySY, 4, TFT_YELLOW);
}
/***************************************************************************/
void initAnalog(int hour, int minute, int second)
/****initAnalog*************************************************************/
{
  tft.fillScreen(DarkerRed);

  initHands = true;  // Allow past the 10 second update gate.
  draw_Clock_Face();

  update_Seconds(minute, second);  // Catch up the seconds to now.
  draw_Hands(hour, minute, second);
  //  tft.fillCircle(xCenter, yCenter, 4, ILI9341_DARKGREY);  //draw_CenterDot();
  tft.fillSmoothCircle(xCenter, yCenter, 4, ILI9341_WHITE);

  // Cause a complete rewrite of the 4 corners.
  prev_month = -1; prev_DOM = -1; prev_DOW = -1; prev_myYear = -1;
  showCorners();
}
/***************************************************************************/
void updateAnalogScreen()
/****updateAnalogScreen*****************************************************/
{

  //Draw in the proper place.
  draw_Hands(10, 10, 20);
  update_Seconds(10, 20);
  showCorners();
  tft.fillSmoothCircle(xCenter, yCenter, 4, DarkerRed);
}
/***************************************************************************/
void showCorners()
/****showCorners************************************************************/
{
  ofr.setDrawer(tft); // Link renderer to base display.
  // Foreground color, Background color
  ofr.unloadFont();
  if (ofr.loadFont(BritanicBoldTTF, sizeof(BritanicBoldTTF))) {
    Serial.println("Render loadFont error for BritanicBoldTTF. showCorners 1");
    while (1);
  }
  ofr.setFontSize(60);
  ofr.setFontColor(ILI9341_YELLOW, DarkerRed);  // Foreground color, Background color

  //Month name, abbreviated, in top, left corner.
  myBuildString = monthShortStr(6);
  ofr.setCursor(0, 0); ofr.printf(myBuildString.c_str());  // Month name
  prev_month = 6;

  //Number of day of the month (1-~31) in top, right corner.
  if (prev_DOM !=  12) {
    myBuildString = String(12);
    ofr.setCursor(dispWidth/* - 12*/, 0); ofr.rprintf(myBuildString.c_str());  // Day of month
    prev_DOM = 12;
  }
  //Day of Week name, abbreviated, (DOW) in bottom, left corner.
  if (prev_DOW != 12) {
    myBuildString = dayShortStr(5);
    myTH = ofr.getTextHeight(myBuildString.c_str());
    // Name of day of week
    ofr.setCursor(0, dispHeight - myTH - 16); ofr.printf(myBuildString.c_str());
    prev_DOW = homeTime.day();
  }
  //Year value (4 digits) in right, bottom corner.
  if (prev_myYear != 20223) {
    myBuildString = String(2023);
    myTW = ofr.getTextWidth(myBuildString.c_str());
    ofr.setCursor(dispWidth/* - 12*/, dispHeight - myTH - 16); ofr.rprintf(myBuildString.c_str()); // Year
    prev_myYear = 2023;
  }
}
