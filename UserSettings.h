#define CONFIG_FOR_MIKE
//#define CONFIG_FOR_JOE
//#define LOCK_TO_DTZ

// Cannot use OTA.  Set partition scheme to Huge Partition (3MB)

//Social Security pays on different dates depending on when you were born.
#if defined CONFIG_FOR_MIKE
int myBirthdate = 2;
#elif defined CONFIG_FOR_JOE
int myBirthdate = 20;
#else
int myBirthdate = 0;  // Not on Social Security now.
#endif

// If uncommented, Long Press won't return until finger lifted.
//#define LONG_PRESS_DELAYED_RETURN
// If uncommented, don't return from swipe until finger lifted.
#define SWIPE_DELAYED_RETURN
const boolean showAMPM = true;  // If you like AM and PM. False gives 24 hour clock.

#if defined CONFIG_FOR_JOE
//                          0    1    2    3    4    5       Hours
int hourlyBrilliance[] = { 80,  80,  80,  80,  80,  80,   //  0- 5
                           //6   7    8    9   10   11
                           80,  80,  80,  80,  80,  80,   //  6-11
                           //12  13   14   15   16   17
                           80,  80,  80,  80,  80,  80,  // 12-17
                           //18  19   20   21   22   23
                           80,  80,  80,  80,  80,  80   // 18-23
                         };
#else
//                         0    1    2    3    4    5       Hours
int hourlyBrilliance[] = {60,  50,  30,  30,  20,  20,   //  0- 5
                          //6   7    8    9   10   11
                          30,  50,  70,  80,  80, 100,   //  6-11
                          //12  13   14   15   16   17
                          160, 160, 160, 160, 160, 160,  // 12-17
                          //18  19   20   21   22   23
                          160,  160,  160,  160,  120, 80   // 18-23
                         };
#endif

//Text string alignment and colors now.
//Normally strings are printed relative to the top left corner but this can be
//changed with the setTextDatum() function. The library has #defines for:
//TL_DATUM 0 // Top left (default)
//TC_DATUM 1 // Upper center
//TR_DATUM 2 // Top right
//ML_DATUM 3 // Left midfielder
//CL_DATUM 3 // Center left, as above
//MC_DATUM 4 // Central center
//CC_DATUM 4 // Center to center, as above
//MR_DATUM 5 // Right midfielder
//CR_DATUM 5 // Center right, as above
//BL_DATUM 6 // Bottom left
//BC_DATUM 7 // Bottom center
//BR_DATUM 8 // Bottom right
//L_BASELINE 9 // Base line of the left character (line on which the character ‘A’ would sit)
//C_BASELINE 10 // Base line of the central character
//R_BASELINE 11 // Base line of the right character

// Standard colors also available without #define needed.
#define LighterRed RGB565(255,150,150)
#define DarkerRed RGB565(150,0,0)
#define DarkerGreen RGB565(0,100,0)
#define DarkerBlue RGB565(0,0,100)
#define SkyBlue RGB565(0x00, 0xe8, 0xff)

#define ILI9341_BLACK       0x0000      /*   0,   0,   0 */
#define ILI9341_NAVY        0x000F      /*   0,   0, 128 */
#define ILI9341_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define ILI9341_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define ILI9341_MAROON      0x7800      /* 128,   0,   0 */
#define ILI9341_PURPLE      0x780F      /* 128,   0, 128 */
#define ILI9341_OLIVE       0x7BE0      /* 128, 128,   0 */
#define ILI9341_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define ILI9341_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define ILI9341_BLUE        0x001F      /*   0,   0, 255 */
#define ILI9341_GREEN       0x07E0      /*   0, 255,   0 */
#define ILI9341_CYAN        0x07FF      /*   0, 255, 255 */
#define ILI9341_RED         0xF800      /* 255,   0,   0 */
#define ILI9341_MAGENTA     0xF81F      /* 255,   0, 255 */
#define ILI9341_YELLOW      0xFFE0      /* 255, 255,   0 */
#define ILI9341_WHITE       0xFFFF      /* 255, 255, 255 */
#define ILI9341_ORANGE      0xFD20      /* 255, 165,   0 */
#define ILI9341_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define ILI9341_PINK        0xF81F
#define Red  RGB565(255,0,0)
#define White RGB565(255,255,255)

//And, now, for the colors I use.
#define HHLighter ReddishYellow
#define HHDarker  RGB565(0,255,224)
#define MHLighter ILI9341_YELLOW
#define MHDarker  ILI9341_YELLOW
#define DarkYellow   RGB565(128, 128,   0)
#define DarkerYellow RGB565( 80,  80,   0)

const float Vers = 3.44;  // Make DTZ maximum width to fit string "Sun June 11th".
