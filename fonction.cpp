#include "2024_camera_Oswin.h"


#ifdef GOAT
const char* ssid = "KAIROS";
const char* password = "0487371190";
#endif

#ifdef Inraci
const char* ssid = "INRACI_4G";
const char* password = "Students-INRaCi";
#endif

#ifdef LABO
const char* ssid = "#LaboD5";  
const char* password = "0123456789";
#endif

#ifdef Chambre
const char* ssid = "Proximus 2,4 GHz";
const char* password = "6qp7W7n2FEtT";
#endif

#ifdef M_WIFI
const char* ssid = "iPhone de Oswin";
const char* password = "Dragon200";
#endif

/*****************************************Objet**************************************/

PCF8575 pcf8575(0x20);
FaBoPWM faboPWM;

void init_PCF8575(void) {
  pcf8575.pinMode(P0, INPUT);
  pcf8575.pinMode(P1, INPUT);
  if (pcf8575.begin()) {
    Serial.println("PCF8574 trouver");
  } else {
    Serial.println("PCF8574 n'est pas trouver");
  }
}

void init_PCA9685(void) {
  if (faboPWM.begin()) {  // vérification
    Serial.println(" PCA9685 trouver");
    faboPWM.init(300);
  } else {
    Serial.println("PCA9685 n'est pas trouver");
  }
}

int calcul_signal(int angle) {
  return (angle * (MAX_VALUE - MIN_VALUE) / MAX_ANGLE) + MIN_VALUE;  // Calcul, convertie les valeurs d’angles en impulsions de largeur
}

void IRAM_ATTR onTimer(void* param) {
  static int cpt = 0;
}

void allumage_LED(void) {
  faboPWM.set_channel_value(2, 1500);  // led U11
  faboPWM.set_channel_value(3, 4095);  // infra.led  U13
  faboPWM.set_channel_value(4, 4095);  // infra.led  U15
}

void init_position_axe_y() {
  int angle_servo_axe_y = 0;
  int PWM = calcul_signal(angle_servo_axe_y);
  faboPWM.set_channel_value(0, PWM);   // servomoteur axe Y(haut/bas) 
}

void init_position_axe_x(void){  
  int angle_servo_axe_x = 90;
  int PWM = calcul_signal(angle_servo_axe_x);
  faboPWM.set_channel_value(1, PWM);   //servomoteur axe X (gauche/droite)

}

void init_Camera(void) {
  camera_config_t config;                      // paramètre pour configurer la caméra
  config.ledc_channel = LEDC_CHANNEL_0;        //broche GPIO (General Purpose Input/Output) de l'ESP32
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
  config.xclk_freq_hz = 20000000;                 //paramètre de la caméra ov3660
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

#if defined(CAMERA_MODEL_ESP_EYE)  // pour seulement un autre modele de caméra
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

  Serial.print("Attends la connexion à : ");   // connexion au WIFI
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  WiFi.setSleep(false);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connecter");

  startCameraServer();                            // serveur de la caméra

  Serial.print("Caméra prêt! Utiliser 'http://");  
  Serial.print(WiFi.localIP());
  Serial.println("' pour se connecter");
}
