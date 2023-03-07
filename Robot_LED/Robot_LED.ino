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
# define DATA_SIZE 128
bool *data[DATA_SIZE];

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(100); // Set BRIGHTNESS to about 1/5 (max = 255)

  // initialize serial:
  Serial.begin(115200);

  for(int i = 0; i < DATA_SIZE; i++){
    *data[i] = false;
  }
}


// loop() function -- runs repeatedly as long as board is on ---------------
int counter = 0;
int num = 1;
const unsigned int MAX_MESSAGE_LENGTH = 12;
static char message[MAX_MESSAGE_LENGTH];
static unsigned int pos = 0;
void loop() {
  /*
  // Fill along the length of the strip in various colors...
  colorWipe(strip.Color(255,   0,   0), 10); // Red
  colorWipe(strip.Color(255,   200,   0), 10); // Yellow
  colorWipe(strip.Color(  0, 255,   0), 10); // Green
  colorWipe(strip.Color(0,   255,  255), 10); // Cyan
  colorWipe(strip.Color(  0,   0, 255), 10); // Blue
  colorWipe(strip.Color(  255,   0, 255), 10); // Magenta
  colorWipe(strip.Color(  255,   255, 255), 10); // White
  colorWipe(strip.Color(  0,   0, 0), 10); // black

  */
  /*
  // Do a theater marquee effect in various colors...
  theaterChase(strip.Color(127, 127, 127), 50); // White, half brightness
  theaterChase(strip.Color(127,   0,   0), 50); // Red, half brightness
  theaterChase(strip.Color(  0,   0, 127), 50); // Blue, half brightness
  
  */
  

  //rainbow(1);             // Flowing rainbow cycle along the whole strip
  
  //theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
/*
  if (counter < 2){
    inWipe(strip.Color(255, 0, 0), 25); // Red
    outWipe(strip.Color(255, 150, 0), 25); // Yellow
    inWipe(strip.Color(0, 255, 0), 25); // Green
    outWipe(strip.Color(0, 255, 175), 25); // Cyan
    inWipe(strip.Color(0, 0, 255), 25); // Blue
    outWipe(strip.Color(255, 0, 255), 25); // Magenta
  }else if (counter < 4){
    downWipe(strip.Color(255, 0, 0), 25); // Red
    upWipe(strip.Color(255, 150, 0), 25); // Yellow
    downWipe(strip.Color(0, 255, 0), 25); // Green
    upWipe(strip.Color(0, 255,175), 25); // Cyan
    downWipe(strip.Color(0, 0, 255), 25); // Blue
    upWipe(strip.Color(255, 0, 255), 25); // Magenta
  }else if (counter < 7){
    colorSpin(strip.Color(255, 0, 255), strip.Color(0, 255, 0), 25, counter - 3, counter - 2);
    colorSpin(strip.Color(255, 0, 255), strip.Color(0, 255, 0), 25, counter - 3, counter - 2);
    colorSpin(strip.Color(255, 0, 255), strip.Color(0, 255, 0), 25, counter - 3, counter - 2);
  }else if(counter < 9){
    colorFlash2(strip.Color(0, 255, 0), strip.Color(0, 0, 255), 1000);
  }else{
    counter = 0;
  }
  if (counter == 1){
    inWipe(strip.Color(  255,   255, 255), 25);
    outWipe(strip.Color(  0,   0, 0), 25);
  }
  counter ++;

  if(Serial.available() > 0){
    char inByte = Serial.read();
    if (inByte != '\n' && (pos < MAX_MESSAGE_LENGTH - 1)){
      message[pos] = inByte;
      pos++;
    } else {
      message[pos] = '\0';
      int newNum = atoi(message);
      if (newNum != 0) num = newNum;
      strip.fill(strip.Color(0, 0, 0), 0);
      strip.show();
      pos = 0;
      delay(1000);
    }
  }
  if (num == 1){
    inWipe(strip.Color(255, 0, 0), 25); // Red
    outWipe(strip.Color(255, 75, 0), 25); // Yellow
    inWipe(strip.Color(0, 255, 0), 25); // Green
    outWipe(strip.Color(0, 255, 175), 25); // Cyan
    inWipe(strip.Color(0, 0, 255), 25); // Blue
    outWipe(strip.Color(255, 0, 255), 25); // Magenta
  } else if (num == 2){
    downWipe(strip.Color(255, 0, 0), 25); // Red
    upWipe(strip.Color(255, 150, 0), 25); // Yellow
    downWipe(strip.Color(0, 255, 0), 25); // Green
    upWipe(strip.Color(0, 255,175), 25); // Cyan
    downWipe(strip.Color(0, 0, 255), 25); // Blue
    upWipe(strip.Color(255, 0, 255), 25); // Magenta
  } else if (num == 3){
    colorSpin(strip.Color(255, 0, 65), strip.Color(150, 0, 255), 25, 3, 4);
  } else if (num == 4){
    colorFlash2(strip.Color(0, 255, 0), strip.Color(0, 0, 255), 1000);
  } else {
    strip.fill(strip.Color(255, 255, 255), 0);
    strip.show();
  }
  */
  displayMorseCode(strip.Color(255, 255, 255), strip.Color(0, 0, 0), "-.-. .- -/-.. --- --.");

}



// Some functions of our own for creating animated effects -----------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    // strip.rainbow() can take a single argument (first pixel hue) or
    // optionally a few extras: number of rainbow repetitions (default 1),
    // saturation and value (brightness) (both 0-255, similar to the
    // ColorHSV() function, default 255), and a true/false flag for whether
    // to apply gamma correction to provide 'truer' colors (default true).
    strip.rainbow(firstPixelHue);
    // Above line is equivalent to:
    // strip.rainbow(firstPixelHue, 1, 255, 255, true);
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
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

void outWipe(uint32_t color, int wait) {
  int x = 29;
  for(int i = 30; i < strip.numPixels(); i++){
    strip.setPixelColor(i, color);
    strip.setPixelColor(x, color);
    x--;
    strip.show();
    delay(wait);
  }
}
  
void inWipe(uint32_t color, int wait) {
  int x = 0;
  for(int i = strip.numPixels() - 1; i > strip.numPixels()/2; i--){
    strip.setPixelColor(i, color);
    strip.setPixelColor(x, color);
    x++;
    strip.show();
    delay(wait);
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

void colorFlash2(uint32_t color1, uint32_t color2, int wait){
  strip.fill(color1, 0);
  strip.show();
  delay(wait);
  strip.fill(color2, 0);
  strip.show();
  delay(wait);
}

void fillDataMorseCode(String code){
  int stripIndex = 0;
  for (int i = 0; i< code.length(); i++){
    switch(code[i]){
      case '.':
//        strip.setPixelColor(stripIndex, text);
        *data[stripIndex] = true;
        stripIndex++;
        break;
      case '-':
//        strip.setPixelColor(stripIndex, text);
//        stripIndex++;
//        strip.setPixelColor(stripIndex, text);
//        stripIndex++;
//        strip.setPixelColor(stripIndex, text);
//        stripIndex++;
        *data[stripIndex] = true;
        stripIndex++;
        *data[stripIndex] = true;
        stripIndex++;
        *data[stripIndex] = true;
        stripIndex++;
        break;
      case ' ':
//        strip.setPixelColor(stripIndex, bg);
//        stripIndex++;
        *data[stripIndex] = false;
        stripIndex++;
        break;
      case '/':
//        strip.setPixelColor(stripIndex, bg);
//        stripIndex++;
//        strip.setPixelColor(stripIndex, bg);
//        stripIndex++;
//        strip.setPixelColor(stripIndex, bg);
//        stripIndex++;
//        strip.setPixelColor(stripIndex, bg);
//        stripIndex++;
//        strip.setPixelColor(stripIndex, bg);
//        stripIndex++;
        *data[stripIndex] = false;
        stripIndex++;
        *data[stripIndex] = false;
        stripIndex++;
        *data[stripIndex] = false;
        stripIndex++;
        *data[stripIndex] = false;
        stripIndex++;
        *data[stripIndex] = false;
        stripIndex++;
        break;
    }
//    strip.setPixelColor(stripIndex, bg);
//    stripIndex++;
      *data[stripIndex] = false;
      stripIndex++;
  }
//  strip.show();
}

void displayMorseCode(uint32_t on, uint32_t off, String code){
  fillDataMorseCode(code);
  int start = 0;
  for (int pixel = strip.numPixels() - 1; pixel >= 0; pixel --){
    for (int i = start; i < strip.numPixels() + start; i++){
      switch(*data[i]){
        case true:
          strip.setPixelColor(pixel, on);
          break;
        case false:
          strip.setPixelColor(pixel, off);
          break;
      }
    }
    strip.show();
  }
   
}
