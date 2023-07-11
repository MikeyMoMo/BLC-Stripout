/* Things to do:
    1. Change LOCK_TO_DTZ to only be effective on Joe-Philippines.

   String apikey = "k5MJFkvlen6ebpAvKRpUlbbBd7uPAzAC";  // Mikey's key

   This one was burned for the month of June, 2022.
   String apikey = "gs2IkNdDcZMjmlCsfFn3PFPkBBquhu82"; // for joebauer49@gmail.com

   This is the one switched to after I ate up all of the gs2...u82 one with the overfetching.
   String apikey = "23TJj8EbyRWec1MPBECv5kLI7zAZNh3C"; // for joe@kapwa.net
*/

//For the ILI9486 with Touch, select Setup6A_ESP_SPI_ILI9486

#include "Defines_and_Docs.h"  // Lots of setups that take up a lot of space!
/***************************************************************************/
void setup()
/****setup******************************************************************/
{
  //  void* SpStart = NULL;
  //  StackPtrAtStart = (void *)&SpStart;
  //  watermarkStart =  uxTaskGetStackHighWaterMark(NULL);
  //  StackPtrEnd3.1 = StackPtrAtStart - watermarkStart;
  int ofrFontHeight;

  Serial.begin(115200); delay(1000);
  //  trySSHColor();
  //  while (1);c
  tft.begin(); // Initialize the screen.
  //  Serial.printf("TFT_BL %i\r\n", TFT_BL);
  tft.setSwapBytes(true);
  tft.invertDisplay(false);
#if defined TFT_BL
  ledcSetup(pwmLedChannelTFT, pwmFreq, pwmResolution);
  ledcAttachPin(TFT_BL, pwmLedChannelTFT); // TFT_BL, 0 - 15
  ledcWrite(pwmLedChannelTFT, 100);
#endif

  tft.setRotation(requestedOrientation);

#ifdef TARGET_DISPLAY && TARGET_DISPLAY == ILI9486
  Serial.println("Calling Touch Calibrate.");
//  touch_calibrate();
#else
  Serial.println("Skipping Touch Calibrate, starting alternate touch routine.");
  if (!ts.begin(18, 19, 40)) {
    Serial.println("Couldn't start touchscreen controller");
    while (true);
  }
#endif

  ofr.setDrawer(tft); // Link renderer to base display for init messages..

  //------------------

  ofr.unloadFont();
  if (ofr.loadFont(BritanicBoldTTF, sizeof(BritanicBoldTTF))) {
    Serial.println("Render loadFont error for BritanicBoldTTF. Init 1");
    while (1);
  }
//  Serial.print("Freetype version: "); ofr.showFreeTypeVersion(); // print FreeType version
  ofr.setFontSize(50);
  tft.fillScreen(SkyBlue);
  ofr.setFontColor(TFT_BLACK, SkyBlue);  // Foreground color, Background color
  myBuildString = "ABCabcjyWM";  // Include caps and descenders to get the full height
  ofrFontHeight = ofr.getTextHeight(myBuildString.c_str());
//  ofrFontHeight = ofr.getTextHeight(sizingChars);
  ofrFontHeight += 8;

  yPos = 50;
  myBuildString = "Little Clock v" + String(Vers);
  ofr.setCursor(dispWidth / 2, yPos); ofr.cprintf(myBuildString.c_str());
  ofr.setCursor(dispWidth / 2, yPos + 80); ofr.cprintf("Initializing");
  pinMode (LED_BUILIN, OUTPUT);
  digitalWrite(LED_BUILIN, false); // Turn it off (on some boards).
  Serial.println("\r\n\r\nThis is \"Big Little Clock\" with ezTime using WiFiMulti,");
  Serial.println("using Bedroom, LallaveWifi, MikeysHS, RaPhaEl and N_Port.");
  Serial.printf("This is version %.2f.\r\n", Vers);
  //  String moduleFname = String(__FILE__);
  //  moduleFname = moduleFname.substring(moduleFname.lastIndexOf("\\") + 1,
  //                                      moduleFname.length());
  //  Serial.printf("Running from: %s\r\n", moduleFname);
  Serial.printf("Running from: %s\r\n", __FILE__);
  Serial.printf("Compiled on %s\r\n", __TIMESTAMP__);
  Serial.printf("Working with a %ix%i pixel screen (WxH as rotated)\r\n",
                tft.width(), tft.height());
  //  Serial.print("\r\nStack: ");
  //  Serial.println(uxTaskGetStackHighWaterMark(NULL) );
  //-----------------------------------------------------------------

  Serial.println("Initializing...");

  myBuildString = "Sprite61";
  Serial.println(myBuildString);
  tft.fillRect(0, yPos + 160, dispWidth, ofrFontHeight, SkyBlue);
  ofr.setCursor(dispWidth / 2, yPos + 160); ofr.cprintf(myBuildString.c_str());
  //  Serial.print("\r\nStack before sprite61 allocation: ");
  //  Serial.println(uxTaskGetStackHighWaterMark(NULL));
  int *a;  // Sprite61 (the small one)
  a = (int*)sprite61.createSprite(spriteW, spriteH);
  if (a == 0) {
    Serial.println("sprite61 creation failed.  Cannot continue.");
    while (1);
  }
  Serial.printf("createSprite61 dispWidth x dispHeight returned: %p\r\n", a);

  int psramPresent = ESP.getPsramSize();
  if (psramPresent > 0) {
    myBuildString = "spriteHH";
    Serial.println(myBuildString);
    tft.fillRect(0, yPos + 160, dispWidth, ofrFontHeight, SkyBlue);
    ofr.setCursor(dispWidth / 2, yPos + 160); ofr.cprintf(myBuildString.c_str());
    //SpriteHH, the Half Height one.
    spriteHHOK = (int*)spriteHH.createSprite(sprite_W_HH, sprite_H_HH);
  }
  if (spriteHHOK == 0 || psramPresent == 0) {
    Serial.println("spriteHH creation failed. Using tft drawing for 3-line display.");
  } else {
    Serial.println("spriteHH creation successful. Using spriteHH drawing for 3-line display.");
    Serial.printf("createSpriteHH dispWidth x dispHeight returned: %p\r\n", spriteHHOK);
  }
  //-----------------------------------------------------------------

  tft.fillRect(0, yPos + 160, dispWidth, ofrFontHeight, SkyBlue);
  myBuildString = "Preferences";
  ofr.setCursor(dispWidth / 2, yPos + 160); ofr.cprintf(myBuildString.c_str());

  // The begin() method opens a “storage space” with a defined namespace.
  // The false argument means that we’ll use it in read/write mode.
  // Use true to open or create the namespace in read-only mode.
  // Name the "folder" we will use and set for read/write.

  preferences.begin("LittleClock", false);
  whichToShow = preferences.getInt("defaultShow", analogHandsShow);
#if defined LOCK_TO_DTZ
  whichToShow = dtz_Show;
#endif

  prevWhichToShow = whichToShow;
  Serial.printf("Which to show preference: %i (%s)\r\n",
                whichToShow, displayName[whichToShow]);
  preferences.end();  // Close LittleClock

  tft.fillRect(0, yPos + 160, dispWidth, ofrFontHeight, SkyBlue);
  myBuildString = "WiFiManager";
  ofr.setCursor(dispWidth / 2, yPos + 160); ofr.cprintf(myBuildString.c_str());

  tft.fillScreen(SkyBlue);
  yPos = 50;
  myBuildString = "Little Clock v" + String(Vers);
  ofr.setCursor(dispWidth / 2, yPos); ofr.cprintf(myBuildString.c_str());
  ofr.setCursor(dispWidth / 2, yPos + 80); ofr.cprintf("Initializing");

  myBuildString = "Calender";
  tft.fillRect(0, yPos + 160, dispWidth, ofrFontHeight, SkyBlue);
  ofr.setCursor(dispWidth / 2, yPos + 160); ofr.cprintf(myBuildString.c_str());

  tft.setTextPadding(0);  // Blanking area function disabled.

  tft.fillScreen(SkyBlue);
  ofr.setCursor(dispWidth / 2, yCenter - 90); ofr.cprintf("Initialization");
  ofr.setCursor(dispWidth / 2, yCenter + 30); ofr.cprintf("Complete");
  for (loopWait = 0; loopWait < 1500; loopWait++) delay(1);  // Wait 1.5 seconds.

  showSelectedClock(true);  // "true" will initialize the screen.
}
/***************************************************************************/
void loop()
/****loop*******************************************************************/
{
  events();
  //This must run every entry into loop.  Put nothing before it!
  touchType = myGetTouch(&myiX, &myiY, &myeX, &myeY, &mydX, &mydY);

  if (touchType != NO_TOUCH) {  // If there was a touch
    //    Serial.printf("Loop entry seeing touch value %i\r\n", touchType);
    if (touchType == SHORT_TOUCH) {
      whichToShow++;
      showSelectedClock(true);  // "true" will initialize the screen.
      delay(250);  // Try to avoid double dipping on the WT32-SC01
      return;
    }
  }

  delay(1000);
  digitalWrite(LED_BUILIN, true); // Turn it off on some boards, on on others.

  loopStartMS = millis();

  // Only save "Show" preferences at the top of the minute, only if changed,
  //  to save flash memory life.

  if (homeTime.second() == 0) {
    //    Serial.println(homeTime.dateTime());); // A debug.print, really...
    if (prevWhichToShow != whichToShow) {  // If it has been changed, save it now
      prevWhichToShow = whichToShow;  // Remember the new setting so no resaving.
      preferences.begin("LittleClock", false);         // Open LittleClock in r/w.
      preferences.putInt("defaultShow", whichToShow);  // Save the data.
      preferences.end();                               // Close LittleClock
      Serial.printf("Which to show preference: %i (%s)\r\n",
                    whichToShow, displayName[whichToShow]);
    }
  }
  // Waiting until the new hour first second is shown, then do the show.
  // On hour change, do a few things:
  //  1. Boot at 5am on Sundays
  //  2. Do the "hour dance".  In this case, some inverts.
  //  3. Change the screen brightness if needed.
  if (prevHour != homeTime.hour()) {
    prevHour = homeTime.hour();  // Reset hour.
    // Refresh (false) each call except on a new hour, then init (true).
    showSelectedClock(true);  // Show selected clock face after screen init.
    tft.invertDisplay(true);  delay(200); tft.invertDisplay(false); delay(200);
    tft.invertDisplay(true);  delay(200); tft.invertDisplay(false); delay(200);
    tft.invertDisplay(true);  delay(200); tft.invertDisplay(false); delay(200);
    tft.invertDisplay(true);  delay(200); tft.invertDisplay(false);
    if ((homeTime.hour() == 5) && (homeTime.weekday() == 2))  // Tuesday 5am
      ESP.restart();  // Weekly reboot
  } else {  // Same hour, don't init clock.  NO FLICKERING!
    showSelectedClock(false);      // Show without screen init, just update it.
  }
  // Screen brightness adjustment on the hour.
  // Don't need the DispOff command.  The PWM on the LED channel is enough.
  // Set up hourly brightness values in UserSettings.h
  if (ledcRead(pwmLedChannelTFT) != hourlyBrilliance[homeTime.hour()]) {
    Serial.printf("Setting display brightness for %i:00 to %i.\r\n",
                  homeTime.hour(), hourlyBrilliance[homeTime.hour()]);
    ledcWrite(pwmLedChannelTFT, hourlyBrilliance[homeTime.hour()]);
    delay(200);
  }
  lastLoopTime = millis() - loopStartMS;
  digitalWrite(LED_BUILIN, false); // Turn it off (on some boards).
}
