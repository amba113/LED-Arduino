#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
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
# define DATA_SIZE 312
bool data[DATA_SIZE];

String letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 .,?;:-/\'\"_+*=)(";
String morse[] = {".- ",     //A
                  "-... ",   //B
                  "-.-. ",   //C 
                  "-.. ",    //D
                  ". ",      //E
                  "..-. ",   //F
                  "--. ",    //G
                  ".... ",   //H
                  ".. ",     //I
                  ".--- ",   //J
                  "-.- ",    //K
                  ".-.. ",   //L
                  "-- ",     //M
                  "-. ",     //N
                  "--- ",    //O
                  ".--. ",   //P
                  "--.- ",   //Q
                  ".-. ",    //R
                  "... ",    //S
                  "- ",      //T
                  "..- ",    //U
                  "...- ",   //V
                  ".-- ",    //W
                  "-..- ",   //X
                  "-.-- ",   //Y
                  "--.. ",   //Z
                  ".---- ",  //1
                  "..--- ",  //2
                  "...-- ",  //3
                  "....- ",  //4
                  "..... ",  //5
                  "-.... ",  //6
                  "--... ",  //7
                  "---.. ",  //8
                  "----. ",  //9
                  "----- ",  //0
                  "/",      //Space
                  ".-.-.- ", //.
                  "--..-- ", //,
                  "..--.. ", //?
                  "-.-.-. ", //;
                  "---... ", //:
                  "-...- ",  //-
                  "-..-. ",  ///
                  ".----. ", //'
                  ".-..-. ", //"
                  "..--.- ", //_
                  ".-.-. ",  //+
                  "-..- ",   //*
                  "-...- ",  //=
                  "-.--.- ", //)
                  "-.--. ",  //(                  
                  };

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(75); // Set BRIGHTNESS to about 1/5 (max = 255)

  // initialize serial:
  Serial.begin(115200);

}


// loop() function -- runs repeatedly as long as board is on ---------------
int num = 1;
const unsigned int MAX_MESSAGE_LENGTH = 12;
static char message[MAX_MESSAGE_LENGTH];
static unsigned int pos = 0;
void loop() {\
/*
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
  */
  colorSpin(strip.Color(0, 255, 255), strip.Color(255, 30, 20), 50, 3, 3);
}

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

void rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    strip.rainbow(firstPixelHue);
    strip.show();
    delay(wait);
  }
}

void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;
  for(int a=0; a<30; a++) {
    for(int b=0; b<3; b++) {
      strip.clear();
      for(int c=b; c<strip.numPixels(); c += 3) {
        int hue = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue));
        strip.setPixelColor(c, color);
      }
      strip.show();
      delay(wait);
      firstPixelHue += 65536 / 90;
    }
  }
}

void downWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

void upWipe(uint32_t color, int wait) {
  for(int i=strip.numPixels() - 1; i > 0; i--) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
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

int serialGet(){
  int number;
  if(Serial.available() > 0){
    number = 0;
    char inByte = Serial.read();
    if (inByte != '\n' && (pos < MAX_MESSAGE_LENGTH - 1)){
      message[pos] = inByte;
      pos++;
    } else {
      message[pos] = '\0';
      int newNum = atoi(message);
      if (newNum != 0) number = newNum;
    }
  }
  Serial.println(number);
  return number;
}

String dataToStr(){
  String out = "";
  for (int i = 0; i< DATA_SIZE; i++){
    if(data[i]){
      out += '1';
    } else {
      out += '0';
    }
  }
  return out;
}

void fillDataMorseCode(String code, bool debug){
  int index = 0;
  if(debug) Serial.println(code);
  for (int i = 0; i < code.length(); i++){
    if(debug) Serial.print(i);
    if(debug) Serial.print(", ");
    if(debug) Serial.println(code.charAt(i));
    switch(code.charAt(i)){
      case '.':
        if(debug) Serial.println("\t got . ");
        data[index] = true;
        index++;
        break;
      case '-':
        if(debug) Serial.println("\t got - ");
        data[index] = true;
        index++;
        data[index] = true;
        index++;
        data[index] = true;
        index++;
        break;
      case ' ':
        if(debug) Serial.println("\t got space");
        data[index] = false;
        index++;
        break;
      case '/':
        if(debug) Serial.println("\t got /");
        data[index] = false;
        index++;
        data[index] = false;
        index++;
        data[index] = false;
        index++;
        data[index] = false;
        index++;
        data[index] = false;
        index++;
        break;
    }
      data[index] = false;
      index++;
  }
}

void scrollMorseCode(uint32_t on, uint32_t off, String phrase, int wait){
  fillDataMorseCode(codeConvert(phrase), false);
  //Start
  for(int d = strip.numPixels() - 1; d >= 0; d--){
    for(int td = 0; td <= strip.numPixels() - d; td++){
      switch(data[td]){
        Serial.println(data[td]);
        case true:
          strip.setPixelColor(d + td, on);
          break;
        case false:
          strip.setPixelColor(d + td, off);
          break;
      }
    }
    strip.show();
    delay(wait);
  }
  //Middle
  for(int s = 1; s <= sizeof(data) - strip.numPixels() + 1; s++){
    for(int d = 0; d <= strip.numPixels(); d++){
      switch(data[s + d]){
        Serial.println(data[s + d]);
        case true:
//          Serial.println("Mid true");
          strip.setPixelColor(d, on);
          break;
        case false:
//          Serial.println("Mid false");
          strip.setPixelColor(d, off);
          break;
      }
    }
    strip.show();
    delay(wait);
  }
  //End
  for(int i = 0; i < strip.numPixels(); i++){
    for(int d = 0; d < strip.numPixels(); d++){
      strip.setPixelColor(d, strip.getPixelColor(d + 1));
    }
    strip.setPixelColor(strip.numPixels() - 1, off);
    strip.show();
    delay(wait);
  }
}

void flashMorseCode(uint32_t on, uint32_t off, String phrase, int wait){
  fillDataMorseCode(codeConvert(phrase), false);
  for(int d = 0; d < DATA_SIZE; d++){
    switch(data[d]){
      case true:
        strip.fill(on, 0);
        break;
      case false:
        strip.fill(off, 0);
        break;
    }
    strip.show();
    delay(wait);
  } 
}

String codeConvert(String word){
  word.toUpperCase();
  String out = "";
  for(int i = 0; i < word.length(); i++){
    int c = letters.indexOf(word.charAt(i));
    out += morse[c];
  }
  return out;
}