# robot-bobot
Radio-controlled robot for passing an obstacle course. Bot passed 3 out of 4 obstacles in 5.34 minutes  
- [x] Marshmallow ocean
- [ ] Foggy mountain
- [x] Silent cave 
- [x] Deadly balloon

![track](https://github.com/bbbaaauuu/robot-bobot/assets/114235448/8a640eca-46e9-4ef9-88c6-f8e20737fc17)

(тут будет норм фото робота) 

A video of the robot popping the balloon 

https://github.com/bbbaaauuu/robot-bobot/assets/114235448/343317ef-ab40-43a2-bf0c-8ee1bfc98b0b

#### Components used:

- NRF;  
-	NRF+;  
-	Motor Shield;  
-	Arduino Leonardo/Amperka Iskra Neo;  
-	Arduino Pro Micro;  
-	x2 DC motor;  
-	x2 battery 18650  
-	joystick;   
-	RGB LED matrix 4x4;  
-	Powerbank.

#### Libraries installed:

-	RF24 by TMRh20;  
-	NeoPixel by Adafruit.

#### Bot code:

```C++
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
```

#### Joystick code:

```C++
#include <SPI.h> //RF24 by TMRh20
#include <nRF24L01.h>
#include <RF24.h>

#define VRx A0
#define VRy A1

RF24 radio(9, 10);
int data[2];

void setup(){
   radio.begin();
  radio.setChannel(15);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.openWritingPipe(0x1234567890LL);
  radio.stopListening();
}

void loop(){

   int valx = analogRead (VRx);
   int valy = analogRead (VRy);
   data[0] = valx;
   data[1] = valy;

  radio.write(&data, sizeof(data));
  delay(10);
  Serial.println(data[0]);
  Serial.println(data[1]);
}
```





