/*****************************************Caméra*****************************************
 Caméra connectée
 Kanema Oswin 
 6ème Electronique Inraci (Institut national de radioélectricité et cinématographie)
 Hardware: M5Stack-Timer-CAM; visionnage + PCA9685; i2c (pwm) entrées/sorties supplémentaire + PCF8574 entrées/sorties supplémentaire + servomoteur mg996r
 
*****************************************librairies**************************************/
#include "2024_camera_Oswin.h"

/*****************************************Variable**************************************/
esp_timer_handle_t timer;
unsigned long timeElapsed;
int angle_actuel = 90;
int pulseWidth;
/*****************************************Intialisation***********************************/
void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  init_PCF8575();
  init_PCA9685();
  init_Camera();
  Allumage_LED();
  init_Position();
}
/*****************************************Boucle**************************************/
void loop() {
  
  uint8_t CapteurD = pcf8575.digitalRead(P0);  // P0=U4  capteur infrarouge droite
  uint8_t CapteurG = pcf8575.digitalRead(P1);  // P1=U5  capteur infrarouge gauche
  if (CapteurD == 1) {
    Serial.println("HUMAIN a droite");
    for (int angle = angle_actuel; angle >= 33; angle--) {
      faboPWM.set_channel_value(1, calcul_signal(angle));  // U9 servomoteur
      delay(80);
    }
    angle_actuel = 33;
  }
  if (CapteurG == 1) {
    Serial.println("HUMAIN a gauche");
    for (int angle = angle_actuel; angle <= 123; angle++) {
      faboPWM.set_channel_value(1, calcul_signal(angle));  // U9 servomoteur
      delay(80);
    }
    angle_actuel = 123;
  }
}
