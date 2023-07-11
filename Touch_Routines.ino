/* A little chat about buttons' creation and use:

    First, they are very strange.  There are two places to set the button
    text but the one (required) overrides the first one so the first one is
    totally useless and is left blank.  So why is is there?  The first one,
    to be left blank, is in the button definition (.initButton).

    Secondly, the button background and the button text locations are totally
    separate.  Why?  Can't say.  I did not write this fairly horrible code.
    So, you have to set two groups of things.  First, the size (H & W) of
    the button and, then the location of the text that will go on top of the
    button (rounded edged rectangle).  If you get it wrong, the text will
    be located outside of the button rectangle.  It takes quite some time
    to get it all right.  At least, it did for me for the first few hours.
    I was following a horrible example and it lead me down the rabbit hole.

    Then, when you find a button has been pressed, you have to set the .press
    variable and then check it, later, to set the button showing as pressed.
    This is just, plain ludicrous!

    The button label location should be an offset from the button X and Y.
    The button selected state should be ONE operation.  Going through setting
    the .press and, then, later checking it with the .justPressed is just
    stupid!

    Yes, I came from a GOOD visual environment, VB6.  When you asked for a
    button, it did the work for you.  Here, you have to do it all, piecemeal,
    and can easily get it wrong.  AND, there is almost no documentation on
    use of the buttons.  The example code bits are atrocious.  This code is
    a better example than the demos in the TFT_eSPI library!

*/
#define NUM_BUTTONS 4
/***************************************************************************/
void showOptionsScreen()
/***************************************************************************/
{
  TFT_eSPI_Button buttons[NUM_BUTTONS];

  bool pressed;
  String s, tzString;
  int b, otd;
  TS_Point p;

  struct buttonData {
    int X;
    int Y;
    int W;
    int H;
    int outlineColor;
    int fillColor;
    int textColor;
    int textSize;
    int labelDatumX;
    int labelDatumY;
    char buttonLabel[20];
  };
  buttonData myButtons[NUM_BUTTONS];

  // Button definition settings.
  // adding to datumx and datumy moves the text down and right
  // subtracting from datumx and datumy moves the text up and left

  s = "Return"; int returnButton = 0;
  strcpy(myButtons[returnButton].buttonLabel, s.c_str());
  myButtons[returnButton].W = 120;
  myButtons[returnButton].H = 35;
  myButtons[returnButton].X = xCenter - myButtons[returnButton].W / 2;
  myButtons[returnButton].Y = dispHeight - myButtons[returnButton].H - 10;
  myButtons[returnButton].outlineColor = TFT_RED;
  myButtons[returnButton].fillColor = DarkerRed;
  myButtons[returnButton].textColor = TFT_WHITE;
  myButtons[returnButton].labelDatumX = -45;
  myButtons[returnButton].labelDatumY = -6;

  s = "Show Legend"; int showLegendButton = 1;
  strcpy(myButtons[showLegendButton].buttonLabel, s.c_str());
  myButtons[showLegendButton].W = 225;
  myButtons[showLegendButton].H = 70;
  myButtons[showLegendButton].X = 10;
  myButtons[showLegendButton].Y = 30;
  myButtons[showLegendButton].outlineColor = TFT_BLUE;
  myButtons[showLegendButton].fillColor = DarkerBlue;
  myButtons[showLegendButton].textColor = TFT_WHITE;
  myButtons[showLegendButton].labelDatumX = -90;
  myButtons[showLegendButton].labelDatumY = -8;

  s = "Show Payday"; int showPDButton = 2;
  strcpy(myButtons[showPDButton].buttonLabel, s.c_str());
  myButtons[showPDButton].W = 225;
  myButtons[showPDButton].H = 70;
  myButtons[showPDButton].X = 10;
  myButtons[showPDButton].Y = 120;
  myButtons[showPDButton].outlineColor = TFT_BLUE;
  myButtons[showPDButton].fillColor = DarkerBlue;
  myButtons[showPDButton].textColor = TFT_WHITE;
  myButtons[showPDButton].labelDatumX = -88;
  myButtons[showPDButton].labelDatumY = -8;

  s = "Reboot"; int showRebootButton = 3;
  strcpy(myButtons[showRebootButton].buttonLabel, s.c_str());
  myButtons[showRebootButton].W = 225;
  myButtons[showRebootButton].H = 70;
  myButtons[showRebootButton].X = 250;
  myButtons[showRebootButton].Y = 30;
  myButtons[showRebootButton].outlineColor = TFT_BLUE;
  myButtons[showRebootButton].fillColor = DarkerBlue;
  myButtons[showRebootButton].textColor = TFT_WHITE;
  myButtons[showRebootButton].labelDatumX = -90;
  myButtons[showRebootButton].labelDatumY = -8;

  tft.fillScreen(TFT_GREEN);
  tft.unloadFont(); tft.loadFont(BritanicBold32);  // Load a different font

  // Wait for finger off the screen before creating menu buttons.
#ifdef TARGET_DISPLAY && TARGET_DISPLAY == ILI9486
  while (tft.getTouch(&tX, &tY)) { };
#else
  while (ts.touched()) { };  // Wait for touch to return.
#endif

  //X,Y,W,H,Outline, Fill, Text colors, label (useless),
  // text size for ugly fonts.
  for (b = 0; b < NUM_BUTTONS; b++) {
    buttons[b].initButtonUL(&tft, myButtons[b].X, myButtons[b].Y,
                            myButtons[b].W, myButtons[b].H,
                            myButtons[b].outlineColor, myButtons[b].fillColor,
                            myButtons[b].textColor, // Outline, Fill color, Text
                            noPtr, KEY_TEXTSIZE); // Label (9 char max), text size
    // Button text 20 character max (I think).
    buttons[b].setLabelDatum(myButtons[b].labelDatumX,
                             myButtons[b].labelDatumY, TL_DATUM);
    buttons[b].drawButton(false, myButtons[b].buttonLabel);
  }
  unsigned long endMillis = millis() + 60000;

  // Start the wait loop.
  while (1) {  // Wait for an event
    t = homeTime.second();
    if (t != last_sec) {  // Second changed.  Need action.
      last_sec = t;
      otd = tft.getTextDatum();
      tft.setTextDatum(TL_DATUM);
      tft.setTextColor(TFT_BLACK, TFT_GREEN);
      tft.setTextPadding(tft.width());
      tft.drawString(homeTime.dateTime("D, d M y H:i:s T"), 18, 240);
      tft.drawString("Big Little Clock version " + String(Vers), 18, 200);
      tft.setTextPadding(0);
      tft.setTextDatum(otd);
    }

    if (millis() > endMillis ) return;  // Get out after a minute idle

#ifdef TARGET_DISPLAY && TARGET_DISPLAY == ILI9486
    pressed = tft.getTouch(&tX, &tY);
#else
    pressed = ts.touched();
    if (pressed) {
      p = ts.getPoint();
      tX = p.x;
      tY = p.y;
    }
#endif
    if (pressed)
      endMillis = millis() + 60000;  // Restart the minute idle wait to exit.

    // ----> Exit Button
    if (pressed && buttons[returnButton].contains(tX, tY))
    {
      buttons[returnButton].drawButton(true, myButtons[returnButton].buttonLabel);
#ifdef TARGET_DISPLAY && TARGET_DISPLAY == ILI9486
      while (tft.getTouch(&tX, &tY)) delay(250);  // Wait for untouch.
#else
      while (ts.touched()) delay(100);  // Wait for untouch.
      p = ts.getPoint(); tX = p.x; tY = p.y;
#endif
      break;  // Return button selected.  Exit the while loop (returns to the clock face selected).
    }

    // ----> Show Show Legend Button
    if (pressed && buttons[showLegendButton].contains(tX, tY))
    {
      buttons[showLegendButton].press(true);  // tell the button it is pressed
      buttons[showLegendButton].drawButton(true, myButtons[showLegendButton].buttonLabel);
#ifdef TARGET_DISPLAY && TARGET_DISPLAY == ILI9486
      while (tft.getTouch(&tX, &tY)) delay(100);  // Wait for untouch.
#else
      while (ts.touched()) delay(100);  // Wait for untouch.
      p = ts.getPoint(); tX = p.x; tY = p.y;
#endif
#ifdef TARGET_DISPLAY && TARGET_DISPLAY == ILI9486
      while (tft.getTouch(&tX, &tY)) delay(100);  // Wait for untouch.
#else
      while (ts.touched()) delay(100);  // Wait for untouch.
      p = ts.getPoint(); tX = p.x; tY = p.y;
#endif
      break;  // Return button selected.
    }

    // ----> Show Next Payday Button
    if (pressed && buttons[showPDButton].contains(tX, tY))
    {
      buttons[showPDButton].press(true);  // tell the button it is pressed
      buttons[showPDButton].drawButton(true, myButtons[showPDButton].buttonLabel);
#ifdef TARGET_DISPLAY && TARGET_DISPLAY == ILI9486
      while (tft.getTouch(&tX, &tY)) delay(100);  // Wait for untouch.
#else
      while (ts.touched()) delay(100);  // Wait for untouch.
      p = ts.getPoint(); tX = p.x; tY = p.y;
#endif
#ifdef TARGET_DISPLAY && TARGET_DISPLAY == ILI9486
      while (tft.getTouch(&tX, &tY)) delay(100);  // Wait for untouch.
#else
      while (ts.touched()) delay(100);  // Wait for untouch.
      p = ts.getPoint(); tX = p.x; tY = p.y;
#endif
      break;
    }

    // ----> Show Reboot Button
    if (pressed && buttons[showRebootButton].contains(tX, tY))
    {
      buttons[showRebootButton].press(true);  // tell the button it is pressed
      buttons[showRebootButton].drawButton(true, myButtons[showRebootButton].buttonLabel);
#ifdef TARGET_DISPLAY && TARGET_DISPLAY == ILI9486
      while (tft.getTouch(&tX, &tY)) delay(100);  // Wait for untouch.
#else
      while (ts.touched()) delay(100);  // Wait for untouch.
      p = ts.getPoint(); tX = p.x; tY = p.y;
#endif
      ESP.restart();  // Reboot button selected.
      break;  // Return Reboot selected. (Will never get here!)
    }
  }
}
/***************************************************************************/
void showSelectedClock(bool initScreen)
/****showSelectedClock******************************************************/
{
  //int analogHandsShow = 0;
  //int four_LineShow   = 1;
  //int three_LineShow  = 2;
  //int BCD_Show        = 3;
  //int dtz_Show        = 4;
  //int TooHigh         = 5;

  // Check every 10 minutes but only update each 3 hours on the top of the hour.
#if defined GET_XRATE
  if ((homeTime.minute() % 10 == 0 && homeTime.second() == 0) || initScreen)
    if (getXchangeRate()) initScreen = true;  // If the screen was changed, init it.
#endif

  if (whichToShow >= TooHigh) whichToShow = analogHandsShow;

  if (whichToShow == dtz_Show) {
    //    Serial.printf("Entering DTZ with initScreen = %s\r\n", initScreen ? "true" : "false");
    if (initScreen) {  // Hourly init

      prevTopDate[0] = 0; prevBottomDate[0] = 0;  // Easy way to clear char array.
    }
    //    doDTZ_Show();
  }

  else if (whichToShow == three_LineShow) {
    if (initScreen) {
      tft.fillScreen(DarkerRed);
      prev_Line1 = ""; prev_Line2 = ""; prev_Line3 = "";  // Force redraw
    }
    //    do3LineShow();
  }
  else if (whichToShow == four_LineShow) {
    if (initScreen) {
      tft.fillScreen(DarkerRed);
      prev_Line1 = ""; prev_Line2 = ""; prev_Line3 = "";  // Force redraw
    }
    //    do4LineShow();
  }
  else if (whichToShow == analogHandsShow) {
    if (initScreen) {
      tft.fillScreen(DarkerRed);
      initAnalog(10, 10, 20);
    } else {
      updateAnalogScreen();  //Draw all hands in the proper place immediately.
    }
  }
}
/***************************************************************************/
void touch_calibrate()
/***************************************************************************/
{
  uint16_t calData[5];
  uint8_t calDataOK = 0;

  // check file system exists
  if (!SPIFFS.begin()) {
    Serial.println("Formating file system");
    SPIFFS.format();
    SPIFFS.begin();
  }

  // check if calibration file exists and size is correct
  if (SPIFFS.exists(CALIBRATION_FILE)) {
    if (REPEAT_CAL)
    {
      // Delete if we want to re-calibrate
      SPIFFS.remove(CALIBRATION_FILE);
    }
    else
    {
      File f = SPIFFS.open(CALIBRATION_FILE, "r");
      if (f) {
        if (f.readBytes((char *)calData, 14) == 14)
          calDataOK = 1;
        f.close();
      }
    }
  }
  // For the ILI9486 with Touch, select Setup6A_ESP_SPI_ILI948
  tft.unloadFont(); tft.loadFont(BritanicBold32);  // Load a different font
  tft.setTextDatum(TC_DATUM);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.fillScreen(TFT_BLACK);

  if (calDataOK && !REPEAT_CAL) {
    // calibration data valid
    tft.setTouch(calData);
  } else {
    tft.drawString("Touch corners as indicated", xCenter, yCenter - 80);
    // data not valid so recalibrate
    Serial.println("Calibrating the display.  Set REPEAT_CAL to true to repeat.");
    if (REPEAT_CAL) {
      tft.drawString("Set REPEAT_CAL to false", xCenter, yCenter);
      tft.drawString("to stop this running again", xCenter, yCenter + 40);
      //      tft.println("Set REPEAT_CAL to false to stop this running again!");
    }

    tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.println("Calibration complete!");

    // store data
    File f = SPIFFS.open(CALIBRATION_FILE, "w");
    if (f) {
      f.write((const unsigned char *)calData, 14);
      f.close();
    }
  }
}

// 5 returns from here.  First, is the type of touch:
//  0:No Touch, 1:Short, 2:Double 3:Triple 4:Long
// Then the starting and ending values for X and Y and type of swipe.
//     17 / 10 \ 11  17:Up-Left,   10:Up,    11:Up-Right,
//     16 |  T | 12  16:Left,       T:Touch, 12:Right
//     15 \ 14 / 13  15:Down-Left, 14:Down,  13:Down-Right
/***************************************************************************/
int myGetTouch (int *iX, int *iY, int *eX, int *eY, int *dX, int *dY)
/***myGetTouch**************************************************************/
{
  /* Notes:
      - If there are multiple clicks (1, 2 or 3) only the position of the
         last one will be reported.)
      - If there is a single click that is not a swipe and a later click
         (within TOUCH_EVENT_WINDOW) only the swipe event will be reported.
  */
  static uint16_t x, y, Swipe_Type_Return;
  static int touchCt;
  static unsigned long touchStart;
  static unsigned long eventStart;
  static int eventTime;
  static bool long_touch_by_time;
  TS_Point p;
  //  Serial.println("Entering myGetTouch.");

  // Initialize the static variables that need it.
  touchStart = 0;
  eventStart = 0;
  touchCt = NO_TOUCH;
  long_touch_by_time = false;

  do
  {
    //  Serial.printf("%lu : Top of loop - eS %lu, tS %lu\r\n", millis(),
    //                eventStart, touchStart);
#ifdef TARGET_DISPLAY && TARGET_DISPLAY == ILI9486
    if (tft.getTouch(&x, &y)) {  // Someone touched the screen?
#else
    if (ts.touched()) {
      p = ts.getPoint(); x = p.x; y = p.y;
#endif
      if (eventStart == 0) eventStart = millis();
      //  Serial.printf("%lu : Setting eventStart - eventStart %lu, touchStart %lu\r\n",
      //                millis(), eventStart, touchStart);
      if (touchStart == 0) {
        touchStart = millis();  // Start the current touch timer
        //  Serial.printf("%lu ; Setting touchStart - eventStart %lu, touchStart %lu\r\n",
        //                millis(), eventStart, touchStart);
        initialX = x; initialY = y;
        //        Serial.printf("%lu : Touched - eS %lu, tS %lu\r\n", millis(),
        //                      eventStart, touchStart);
      }
      eventTime = millis() - touchStart;
      if (eventTime >= SLONG_TOUCH_TIME) {
        //  Serial.println("Touch timer found a long touch.");
        *iX = initialX; *iY = initialY; *eX = 0; *eX = 0; *dX = 0; *dY = 0;
        //  Serial.printf("%lu : long touch = true - eventStart %lu, touchStart %lu\r\n",
        //                millis(), eventStart, touchStart);
        long_touch_by_time = true;
        //  Serial.printf("%lu : long touch = true - eventStart %lu, touchStart %lu\r\n",
        //                millis(), eventStart, touchStart);
#if defined LONG_PRESS_DELAYED_RETURN
#ifdef TARGET_DISPLAY && TARGET_DISPLAY == ILI9486
        while (tft.getTouch(&x, &y));  // Wait for no touch
#else
        while (ts.touched());  // Wait for no touch
        p = ts.getPoint(); x = p.x; y = p.y;
#endif
#endif
        //  Serial.printf("y %i, endingY %i\r\n", y, endingY);
        endingX = x; endingY = y;
        //  Serial.println("Now, determine if long touch or swipe");
        distanceX = initialX - endingX; distanceY = initialY - y;
        if ((abs(distanceX) < SWIPE_MIN_X) && (abs(distanceY) < SWIPE_MIN_Y)) {
          //  Serial.println("Touch distance below the minimum for swipe. Returning long touch");
          return LONG_TOUCH;
        } else {
          //  Serial.println("Swipe distance achieved.");
          eventStart = millis();  // Extend the timer so we get to the "else" code.
        }
      }
    } else {  // The touch is ended.  If the time is less than SLONG_TOUCH_TIME, increment click count
      // First, determine if there was movement above the minimum for a swipe.
      // Note that swipe must be first, then long click, then single click(s) checked for, in order.
      //  Serial.printf("%lu : Touch ended - eS %lu, tS %lu\r\n", millis(), eventStart, touchStart);
      if (eventStart > 0 && touchStart > 0) {  // If we were in an event, show finish.
        endingX = x; endingY = y;
        distanceX = endingX - initialX;
        distanceY = endingY - initialY;
        eventTime = millis() - touchStart;
        //  Serial.printf("%lu - Event time %i, distX %i, distY %i\r\n",
        //                millis(), eventTime, distanceX, distanceY);
        // Does this event qualify as a Swipe?
        if ((abs(distanceX) > SWIPE_MIN_X) || (abs(distanceY) > SWIPE_MIN_Y))
        {
          //  Serial.println("Sub found a swipe.");
          *iX = initialX; *iY = initialY; *eX = endingX; *eX = endingY;
          *dX = distanceX; *dY = distanceY;
          if (abs(distanceX)      < SWIPE_MIN_X  && distanceY      < -SWIPE_MIN_Y) Swipe_Type_Return = SWIPE_UP;
          else if (distanceX      > SWIPE_MIN_X  && distanceY      < -SWIPE_MIN_Y) Swipe_Type_Return =  SWIPE_UP_RIGHT;
          else if (distanceX      > SWIPE_MIN_X  && abs(distanceY) < SWIPE_MIN_Y)  Swipe_Type_Return =  SWIPE_RIGHT;
          else if (distanceX      > SWIPE_MIN_X  && distanceY      > SWIPE_MIN_Y)  Swipe_Type_Return =  SWIPE_DOWN_RIGHT;
          else if (abs(distanceX) < SWIPE_MIN_X  && distanceY      > SWIPE_MIN_Y)  Swipe_Type_Return =  SWIPE_DOWN;
          else if (distanceX      < -SWIPE_MIN_X && distanceY      > SWIPE_MIN_Y)  Swipe_Type_Return =  SWIPE_DOWN_LEFT;
          else if (distanceX      < -SWIPE_MIN_X && abs(distanceY) < SWIPE_MIN_Y)  Swipe_Type_Return =  SWIPE_LEFT;
          else if (distanceX      < -SWIPE_MIN_X && distanceY      < SWIPE_MIN_Y)  Swipe_Type_Return =  SWIPE_UP_LEFT;
#if defined SWIPE_DELAYED_RETURN
#ifdef TARGET_DISPLAY && TARGET_DISPLAY == ILI9486
          while (tft.getTouch(&x, &y));  // Wait for no touch
#else
          while (ts.touched());  // Wait for no touch
          p = ts.getPoint(); x = p.x; y = p.y;
#endif
#endif
          return Swipe_Type_Return;
        }
        else if (eventTime < SLONG_TOUCH_TIME) {
          //  Serial.println("Sub found a single click");
          touchCt++; *iX = initialX; *iY = initialY; *eX = 0; *eX = 0; *dX = 0; *dY = 0;
          if (touchCt == TRIPLE_TOUCH) return TRIPLE_TOUCH;  // End this now.
          touchStart = 0;
        }
      }
    }
  } while (millis() < (eventStart + TOUCH_EVENT_WINDOW));
  //  Serial.printf("Return from myGetTouch %lu\r\n", millis());
  return touchCt;  // All that is left is DOUBLE_TOUCH
}
