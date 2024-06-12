/*****************************************Caméra*****************************************
 Caméra connectée
 Kanema Oswin 
 6ème Electronique Inraci (Institut national de radioélectricité et cinématographie)
 Hardware: M5Stack-Timer-CAM; visionnage + PCA9685; i2c (pwm) entrées/sorties supplémentaires + PCF8574 entrées/sorties supplémentaire + servomoteur mg996r
 
*****************************************librairies**************************************/
#include "2024_camera_Oswin.h"

#define Projet
//#define Test_servomoteur
//#define Test_PCF8574
/*****************************************Variable**************************************/
esp_timer_handle_t timer;
unsigned long timeElapsed;
int angle_actuel = 90;
int pulseWidth;


  
/*****************************************Intialisation***********************************/
void setup() {
  Wire.begin();
  Serial.begin(115200);                          // vitesse de bit par seconde 
  Serial.setDebugOutput(true);
  Serial.println();
  init_PCF8575();
  init_PCA9685();
  init_Camera();
  allumage_LED();
  init_position_axe_x();
  init_position_axe_y();
}
/*****************************************Boucle**************************************/

void loop() {

 #ifdef Projet
  uint8_t CapteurD = pcf8575.digitalRead(P0);  // P0=U4 capteur infrarouge droite  `uint8_t` est un type entier non signé de 8 bits
  uint8_t CapteurG = pcf8575.digitalRead(P1);  // P1=U5 capteur infrarouge gauche

  if (CapteurD == 1) {                      
    if (angle_actuel != 33) {                  // si il est déjà à 33 il ne bouge pas
      Serial.println("HUMAIN à droite");
      for (int angle = angle_actuel; angle >= 33; angle--) { // décrémentation
        faboPWM.set_channel_value(1, calcul_signal(angle));  // U9 servomoteur du bas axe x
        delay(80);
      }
      angle_actuel = 33;
    }
  }

  if (CapteurG == 1) {
    if (angle_actuel != 123) {
      Serial.println("HUMAIN à gauche");
      for (int angle = angle_actuel; angle <= 123; angle++) { // incrémentation
        faboPWM.set_channel_value(1, calcul_signal(angle));  // U9 servomoteur du bas axe x
        delay(80);
      }
      angle_actuel = 123;
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
    int angle = input.toInt();                    // Convertir la chaîne en un entier (angle)
    angle = constrain(angle, 0, 180);             
    int pulseWidth = calcul_signal(angle);        // Convertir l'angle en largeur d'impulsion
    faboPWM.set_channel_value(1, pulseWidth);     
    Serial.print("Position du servo mise à jour : "); // Afficher la position du servomoteur mise à jour
    Serial.println(angle);
  }
}
#endif
}

