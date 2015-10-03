#include <Adafruit_NeoPixel.h>
#define MAX_VAL 64  // 0 to 255 for brightness
#define DELAY_TIME 50 
#define DELAY_TIME2 20
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, 6, NEO_GRB + NEO_KHZ800);

void setup(){
  // シリアルポートを9600 bps[ビット/秒]で初期化
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

int counter = 0;
 
void loop(){
   
  int input;
  bool ledon;
  // シリアルポートより1文字読み込む
  input = Serial.read();
  
  if(input != -1 ){
    // 受け取った文字を送信
    Serial.write(input);
    Serial.write("\n");
    if(ledon){
      ledon = false;
    }else{
      ledon = true;
    }
  }
  if(ledon && counter < 5){
    colorWipe(strip.Color(MAX_VAL, 0, 0), DELAY_TIME); // Red
    colorWipe(strip.Color(0, MAX_VAL, 0), DELAY_TIME); // Green
    colorWipe(strip.Color(MAX_VAL, MAX_VAL, 0), DELAY_TIME); // Yellow
    colorWipe(strip.Color(0, 0, MAX_VAL), DELAY_TIME); // Blue
    colorWipe(strip.Color(MAX_VAL, 0, MAX_VAL), DELAY_TIME); // Purple
    colorWipe(strip.Color(0, MAX_VAL, MAX_VAL), DELAY_TIME); // Cyan
    colorWipe(strip.Color(MAX_VAL, MAX_VAL, MAX_VAL), DELAY_TIME); // White
    rainbow(DELAY_TIME2);
    rainbowCycle(DELAY_TIME2);
    ledon = false;
    counter++;
  } else if(ledon) {
    colorWipe(strip.Color(0, 0, 0), DELAY_TIME); //Black
    //rainbow(DELAY_TIME2);
    //rainbowCycle(DELAY_TIME2);
    counter = 0;
    ledon = false;
  }  
}

 
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
 
void rainbow(uint8_t wait) {
  uint16_t i, j;
 
  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
 
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
 
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
 
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color((WheelPos * 3)*MAX_VAL/255, (255 - WheelPos * 3)*MAX_VAL/255, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color((255 - WheelPos * 3)*MAX_VAL/255, 0, (WheelPos * 3)*MAX_VAL/255);
  } else {
   WheelPos -= 170;
   return strip.Color(0, (WheelPos * 3)*MAX_VAL/255, (255 - WheelPos * 3)*MAX_VAL/255);
  }
}
