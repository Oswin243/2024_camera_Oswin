/*****************************************Caméra*****************************************
 Kanema Oswin 6ème Electronique
 Hardware: M5Stack-Timer-CAM; visionnage + PCA9685; i2c (pwm)  + PCF8574
 24/03/2024
*****************************************librairies**************************************/

#include "esp_camera.h"
#include <WiFi.h>
#include <Wire.h>
#include "FaBoPWM_PCA9685.h"
#include "Arduino.h"
#include "PCF8575.h"
#define CAMERA_MODEL_M5STACK_UNITCAM  // ne peut être deplacé
#include "camera_pins.h"


//#define test_mouvement

/*****************************************Constante**************************************/
//#define CAMERA_MODEL_M5STACK_UNITCAM
#define P0 0
#define P1 1
#define MAX_VALUE 480
#define MIN_VALUE 80
PCF8575 pcf8575(0x20);

/*****************************************Variable**************************************/

FaBoPWM faboPWM;
esp_timer_handle_t timer;
unsigned long timeElapsed;
//const char *ssid     = "KAIROS";
//const char *password = "0487371190";
//const char *ssid     = "INRACI_4G";
//const char *password = "Students-INRaCi";
const char* ssid = "#LaboD5";  //ok
const char* password = "0123456789";
//const char* ssid = "Wifi1";
//const char* password = "6qp7W7n2FEtT";
//const char *ssid     = "iPhone de Oswin";
//const char *password = "Dragon200";

/*****************************************Fonctions***************************************/
void setupLedFlash(int pin);
void startCameraServer();
void IRAM_ATTR onTimer(void* param) {
  static int cpt = 0;
}
/*****************************************Intialisation***********************************/
void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  pcf8575.pinMode(P0, INPUT);
  pcf8575.pinMode(P1, INPUT);
  pcf8575.begin();
  if (faboPWM.begin()) {                  // vérification 
    Serial.println("Find PCA9685");
    faboPWM.init(300);
  }
  faboPWM.set_hz(50);

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.frame_size = FRAMESIZE_UXGA;
  config.pixel_format = PIXFORMAT_JPEG;
  config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
  config.fb_location = CAMERA_FB_IN_PSRAM;
  config.jpeg_quality = 12;
  config.fb_count = 1;

  if (config.pixel_format == PIXFORMAT_JPEG) {
    if (psramFound()) {
      config.jpeg_quality = 10;
      config.fb_count = 2;
      config.grab_mode = CAMERA_GRAB_LATEST;
    } else {
      config.frame_size = FRAMESIZE_SVGA;
      config.fb_location = CAMERA_FB_IN_DRAM;
    }
  } else {
    config.frame_size = FRAMESIZE_240X240;
#if CONFIG_IDF_TARGET_ESP32S3
    config.fb_count = 2;
#endif
  }

#if defined(CAMERA_MODEL_ESP_EYE)
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
#endif

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  sensor_t* s = esp_camera_sensor_get();
  if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1);
    s->set_brightness(s, 1);
    s->set_saturation(s, -2);
  }
  if (config.pixel_format == PIXFORMAT_JPEG) {
    s->set_framesize(s, FRAMESIZE_QVGA);
  }

#if defined(CAMERA_MODEL_M5STACK_WIDE) || defined(CAMERA_MODEL_M5STACK_ESP32CAM)
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
#endif

#if defined(CAMERA_MODEL_ESP32S3_EYE)
  s->set_vflip(s, 1);
#endif

#if defined(LED_GPIO_NUM)
  setupLedFlash(LED_GPIO_NUM);
#endif

  WiFi.begin(ssid, password);
  WiFi.setSleep(false);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  startCameraServer();

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");

  int angle = 90;
  int pulseWidth = map(angle, 0, 180, MIN_VALUE, MAX_VALUE);  // Convertir l'angle en largeur d'impulsion
  faboPWM.set_channel_value(1, pulseWidth);                   //U9
  faboPWM.set_channel_value(0, pulseWidth);                   //U8
  delay(0);
}
/*****************************************Boucle**************************************/
void loop() {

  faboPWM.set_channel_value(2, 1500);  // led U11
  delay(200);
  faboPWM.set_channel_value(3, 4095);  // infra.led  U13

  uint8_t val1 = pcf8575.digitalRead(P1);  //P1=U5           P0=U4
  if (val1 == 1) {
    Serial.println("HUMAIN");
    int angle = 90;
    int pulseWidth = map(angle, 0, 180, MIN_VALUE, MAX_VALUE);
    faboPWM.set_channel_value(1, pulseWidth);  // U9
    faboPWM.set_channel_value(0, pulseWidth);  // U8
  } else if (val1 == 0) {
    Serial.println("RIEN");
    int angle = 0;
    int pulseWidth = map(angle, 0, 180, MIN_VALUE, MAX_VALUE);
    faboPWM.set_channel_value(1, pulseWidth);  // U9
    faboPWM.set_channel_value(0, pulseWidth);  // U8
  }


}
void detection(void){
  

}