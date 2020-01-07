#include <RCSwitch.h>

// LED
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN             A0
#define NUMPIXELS      30
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


RCSwitch mySwitch = RCSwitch();
int delayval = 50;

static const char* bin2tristate(const char* bin);
static char * dec2binWzerofill(unsigned long Dec, unsigned int bitLength);
boolean check = 0;
boolean stat = LOW;
int val = 0;
//boolean stat = LOW;

void setup() {
  // LED
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin();

  //pixels.show();
 
  Serial.begin(9600);
  pinMode(2, INPUT);  // pin #P2 is Data in
  // mySwitch.enableReceive(0);
  pinMode(3, OUTPUT); //R
  digitalWrite(3, HIGH);
  pinMode(4, OUTPUT); //G
  digitalWrite(4, HIGH);
  pinMode(5, OUTPUT); //B
  digitalWrite(5, HIGH);
   pinMode(0,INPUT);
  pinMode(1,OUTPUT);
 // attachInterrupt(1, start, HIGH);
}

void loop() {

  if (digitalRead(2) != stat) { // listen p2 voltage change
    mySwitch.handleInterrupt();
    stat = digitalRead(2);
    //Serial.println("change");
  }

  if (mySwitch.available()) {   //transform signal
    //output(mySwitch.getReceivedValue(), mySwitch.getReceivedBitlength(), mySwitch.getReceivedDelay(), mySwitch.getReceivedRawdata(),mySwitch.getReceivedProtocol());
    val = mySwitch.getReceivedBitlength();
    Serial.println("gotit");
    pixel_0();
    const char* v = dec2binWzerofill(mySwitch.getReceivedValue(), mySwitch.getReceivedBitlength());
    if (v[0] == '1' && v[1] == '0' && v[2] == '1' && v[3] == '0' && v[4] == '0')
    {
      if (v[21] == '1')
      {

        Serial.println("B");
        digitalWrite(3, LOW);
        digitalWrite(4, HIGH);
        digitalWrite(5, HIGH);
        // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
    rainbowCycle(20);

      }

    }
    if (v[22] == '1')
    { Serial.println("R");
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
     
      /*theaterChase(pixels.Color(125, 0, 0), 50);//red
        theaterChase(pixels.Color(255, 165, 0), 50);//orange
        theaterChase(pixels.Color(255, 255, 0), 50);//yellow
        theaterChase(pixels.Color(0, 125, 0), 50);//green
        theaterChase(pixels.Color(30, 144, 225), 50);//blue
        theaterChase(pixels.Color(0, 0, 255), 50);//darkblue
        theaterChase(pixels.Color(85, 26, 139), 50);//purple*/
   }
    if (v[23] == '1')
    {
      Serial.println("G");
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
      
    }
    //Serial.println(v[21]);
  }
  // Serial.println("out");
 // delay(200);
  //pixels.show();
  mySwitch.resetAvailable();
}
void pixel_0() {
  for (int i = 0; i < NUMPIXELS; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

  }
}

void a() {

  for (int i = 0; i < NUMPIXELS; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0, 150, 0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    //delay(delayval); // Delay for a period of time (in milliseconds).
  }
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
