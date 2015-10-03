//Bocchix Code for arduino
//Connected konashi and iPhone, 
//Bocchix Code - jsdo.it - Share JavaScript, HTML5 and CSS, http://jsdo.it/tezsawa/jtMj

#include <Adafruit_NeoPixel.h>
#define MAX_VAL 64  // 0 to 255 for brightness
#define DELAY_TIME 50 
#define DELAY_TIME2 1
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, 6, NEO_GRB + NEO_KHZ800);

bool ledon;
//false:OFF, true:ON
int ledstate;
//0:Black, 1:Red, 2:Green, 3:Yellow, 4:Blue, 
//5:Purple, 6:Cyan, 7:White, 8:rainbow, 9:rainboyCycle
  
void setup(){
  ledon = false;
  // シリアルポートを9600 bps[ビット/秒]で初期化
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}
  
void loop(){
  int input;
  
  // シリアルポートより1文字読み込む
  input = Serial.read();

  if(input != -1 ){
    // 受け取った文字を送信
    Serial.write(input);
    Serial.write("\n");
    
    // 文字が来たらLEDの色を変更
    /*
    if(ledstate < 9){
      ledstate++;
    }else{
      ledstate = 0;
    }
    */
    
    // 文字が来たらLEDの色を変更
    if(ledon == 0){
      ledon = 1;
    }else{
      ledon = 0;
    }
    
  }

/*
  switch(ledstate){
    case:0
        colorWipe(strip.Color(0, 0, 0), DELAY_TIME); //Black
    break;
    case:1
        colorWipe(strip.Color(MAX_VAL, 0, 0), DELAY_TIME); // Red
    break;
    case:2
        colorWipe(strip.Color(0, MAX_VAL, 0), DELAY_TIME); // Green
    break;
    case:3
        colorWipe(strip.Color(MAX_VAL, MAX_VAL, 0), DELAY_TIME); // Yellow
    break;
    case:4
        colorWipe(strip.Color(0, 0, MAX_VAL), DELAY_TIME); // Blue
    break;
    case:5
        colorWipe(strip.Color(MAX_VAL, 0, MAX_VAL), DELAY_TIME); // Purple
    break;
    case:6
        colorWipe(strip.Color(0, MAX_VAL, MAX_VAL), DELAY_TIME); // Cyan
    break;
    case:7
        colorWipe(strip.Color(MAX_VAL, MAX_VAL, MAX_VAL), DELAY_TIME); // White
    break;
    case:8
        rainbow(DELAY_TIME2);
    break;
    case:9
        rainbowCycle(DELAY_TIME2);
    break;
  }
  */
  
  if(ledon){
    //rainbow(DELAY_TIME2);
    rainbowCycle(DELAY_TIME2);
    //rainbowCycle_blink(DELAY_TIME2);
  }
  else{
    colorWipe(strip.Color(0, 0, 0), DELAY_TIME); //Black
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
 
  //for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
  for(j=0; j<256; j++) { // 1 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    //delay(wait);
  }
}

void rainbowCycle_blink(uint8_t wait) {
  uint16_t i, j;
 
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    //delay(wait);
    //delay(0);
    if(i%4 == 0){
      colorWipe(strip.Color(0, 0, 0), 0); //Black
    }
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

