// gingerbreadhouse_lights: 
//
// Sound-activated lightshow for Circuit Playground Express board
// Used as part of a gingerbreadhouse display
//

#include <Adafruit_NeoPixel.h>
#include <Adafruit_CircuitPlayground.h>

#define NEOPIXEL_PIN 8 // internal neopixels on the Circuit Playground Express

// Setup for Neopixels
Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
uint16_t hue = 0;
float value;
int fade_val = 0;
uint8_t fade_dir = 0;

void setup() {
  strip.begin();
  strip.setBrightness(0);
  strip.show();

  CircuitPlayground.begin();
}
 
void loop() {
  // check microphone sound level
  // may need to vary from board to board
  value = CircuitPlayground.mic.soundPressureLevel(10);
  if ( (value > 90.0) && (fade_dir < 1) ) { // fade in if off or fading out
    fade_dir = 1;
  }
  if (fade_dir == 1) { // fading in
    fade_val++;
    if (fade_val >= 400) {
      fade_dir = 0; // start fade out
    }
  }
  else { // fading out or off
    if (fade_val > 0) {
      fade_val--;
    }
  }
  if (fade_val > 255) { // fade val can exceed 255 to create period of time where lights remain at maximum
    strip.setBrightness(255);
  }
  else {
    strip.setBrightness(fade_val);
  }
  for (int i = 0; i < 10; i++) { // Rainbow colours
    strip.setPixelColor(i, strip.ColorHSV(hue+5000*i));
  }
  strip.show();
  delay(20);
  hue = hue + 200; // cycle through colours
}

