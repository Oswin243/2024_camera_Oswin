#include "esp_camera.h"
#include <WiFi.h>
#include <Wire.h>
#include "FaBoPWM_PCA9685.h"
#include "Arduino.h"
#include "PCF8575.h"
#define CAMERA_MODEL_M5STACK_UNITCAM  // ne peut être deplacé
#include "camera_pins.h"



//#define CAMERA_MODEL_M5STACK_UNITCAM
#define P0 0
#define P1 1
#define MAX_VALUE 480
#define MIN_VALUE 80
#define MIN_ANGLE 0    // Angle minimum (en degrés)
#define MAX_ANGLE 180  // Angle maximum (en degrés)


extern const char* ssid;
extern const char* password;


//#define LABO

extern PCF8575 pcf8575;
extern FaBoPWM faboPWM;

void init_Position(void);
void Allumage_LED(void);
void init_Camera(void);
void init_PCA9685(void);
void init_PCF8575(void);
void setupLedFlash(int pin);
void startCameraServer();   
int calcul_signal(int angle); 
void IRAM_ATTR onTimer(void* param);