// A basic everyday NeoPixel strip test program.

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 60

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


// setup() function -- runs once at startup --------------------------------

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  // initialize serial:
  Serial.begin(115200);
}

int num = 1;
const unsigned int MAX_MESSAGE_LENGTH = 12;
static char message[MAX_MESSAGE_LENGTH];
static unsigned int pos = 0;
// loop() function -- runs repeatedly as long as board is on ---------------
void loop() {
  if(Serial.available() > 0){
    char inByte = Serial.read();
    if (inByte != '\n' && (pos < MAX_MESSAGE_LENGTH - 1)){
      message[pos] = inByte;
      pos++;
    } else {
      message[pos] = '\0';
      int newNum = atoi(message);
      if (newNum != 0) num = newNum;
      pos = 0;
      
    }
  }
  colorSpin(strip.Color(255, 0, 255), strip.Color(0, 255, 0), 25, 5, num);
}

void downWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void upWipe(uint32_t color, int wait) {
  for(int i=strip.numPixels() - 1; i > 0; i--) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
void colorSpin(uint32_t color1, uint32_t color2, int wait, int width, int num){
  strip.fill(color1, 0);
  int y;
  for(int i = 0; i < strip.numPixels()/num; i++){
    for(int n = 0; n < num; n++){
      for(int x = 0; x < width; x++){
        strip.setPixelColor((n*strip.numPixels()/num) + i + x, color2);
        if(i > 0){
          strip.setPixelColor((n*strip.numPixels()/num) + i - 1, color1);
        }
      }
    }
    strip.show();
    delay(wait);
  }
}
