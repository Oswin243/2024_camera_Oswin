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

#define Projet
//#define Test_servomoteur
//#define Test_PCF8574

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
  init_position_axe_x();
  init_position_axe_y();
}
/*****************************************Boucle**************************************/
void loop() {

#ifdef Projet
  uint8_t CapteurD = pcf8575.digitalRead(P0);  // P0=U4 capteur infrarouge droite
  uint8_t CapteurG = pcf8575.digitalRead(P1);  // P1=U5 capteur infrarouge gauche

  if (CapteurD == 1) {
    if (angle_actuel != 33) {
      Serial.println("HUMAIN à droite");
      for (int angle = angle_actuel; angle >= 33; angle--) {
        faboPWM.set_channel_value(1, calcul_signal(angle));  // U9 servomoteur du bas axe x
        delay(80);
      }
      angle_actuel = 33;
      delay(1000);
    }
  }

  if (CapteurG == 1) {
    if (angle_actuel != 123) {
      Serial.println("HUMAIN à gauche");
      for (int angle = angle_actuel; angle <= 123; angle++) {
        faboPWM.set_channel_value(1, calcul_signal(angle));  // U9 servomoteur du bas axe x
        delay(80);
      }
      angle_actuel = 123;
      delay(1000);
    }
  }
#endif

#ifdef Test_PCF8574
  uint8_t etat = pcf8575.digitalRead(P1);
  if (etat == 1) {
    Serial.println(etat);
    delay(1000);
  } else if (etat == 0) {
    Serial.println(etat);
  }
#endif

#ifdef Test_servomoteur
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    int angle = input.toInt();              // Angle saisi depuis le moniteur série
    angle = constrain(angle, 0, 180);       // Limiter l'angle entre 0 et 180 degrés
    int pulseWidth = calcul_signal(angle);  // Utiliser la fonction calcul_signal pour convertir l'angle en largeur d'impulsion
    faboPWM.set_channel_value(0, pulseWidth);
    Serial.print("Position du servo mise à jour : ");
    Serial.println(angle);
  }
#endif

}

