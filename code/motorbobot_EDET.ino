#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_NeoPixel.h>

#define SPEED_1      5 
#define DIR_1        4
 
#define SPEED_2      6
#define DIR_2        7

#define MATRIX_PIN    0
#define LED_COUNT 16

Adafruit_NeoPixel matrix = Adafruit_NeoPixel(LED_COUNT, MATRIX_PIN, NEO_GRB + NEO_KHZ800);

RF24 radio(9, 10);
int data[2];

 
void setup() {
  for (int i = 4; i < 8; i++) {     
    pinMode(i, OUTPUT);
  }

 matrix.begin();    
 
  Serial.begin(9600);
  
  radio.begin();
  radio.setChannel(15);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.openReadingPipe(0, 0x1234567890LL);
  radio.startListening();
} 
 
void loop() {

  if (radio.available()){
    radio.read(&data, sizeof(data));

    if (data[0] > 900 ) {
      digitalWrite (DIR_1, LOW);
      analogWrite(SPEED_1, 200);  
      digitalWrite (DIR_2, HIGH);
      analogWrite(SPEED_2, 200);  
    }
    
    else if (data[0] < 200) {
      digitalWrite(DIR_1, HIGH);
      analogWrite(SPEED_1, 200);
      digitalWrite(DIR_2, LOW);
      analogWrite(SPEED_2, 200);
    }
    else if (data[1] < 200) {
      digitalWrite(DIR_2, HIGH);
      analogWrite(SPEED_2, 200);
      digitalWrite(DIR_1, HIGH);
      analogWrite(SPEED_1, 200);
    }

    else if (data[1] > 900) {
      digitalWrite(DIR_2, LOW);
      analogWrite(SPEED_2, 200);  
      digitalWrite(DIR_1, LOW);
      analogWrite(SPEED_1, 200); 
    }
    else {  
      digitalWrite(DIR_1, HIGH);
      analogWrite(SPEED_1, 0);
      digitalWrite(DIR_2, HIGH);
      analogWrite(SPEED_2, 0);  
    }
    Serial.println(data[0]);
    Serial.println(data[1]);   
  }

  for (int i = 0; i < matrix.numPixels(); i++) {
        matrix.setPixelColor(i, 221, 250, 5);
        matrix.show();  
    }

}

// void colorWipe(uint32_t c, uint8_t wait)
// {
//   for (uint16_t i = 0; i < matrix.numPixels(); i++) {
//     // заполняем текущий сегмент выбранным цветом
//     matrix.setPixelColor(i, c);
//     matrix.show();
//     // ждём
//     //delay(wait);
//  }
// }
