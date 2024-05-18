/* BRIEF: M5core DHT12
 * 
 * Description: DHT12 sensor reads temperature, humidity and display the data on the screen and send data via MQTT.
 *              Deep Sleep after defined time
 *              Button A: Wake up from Deep Sleep
 *              Button B: start Deep Sleep
 *              Button C: shutdown M5Stack
 *
 * Version: 1.1.0
 * 
 * Author: Zheng Robert, 2018
*/

const char* appTitle = "M5Stack Temp/Hum Display, Wifi & MQTT client";
const char *appVersion = "1.1.0";

#include <M5Stack.h>
#include "DHT12.h"
#include <Wire.h>     //The DHT12 uses I2C comunication.
DHT12 dht12;          //Preset scale CELSIUS and ID 0x5c.

#include "credentials.h"
#include "rz_wifi.h"
#include "rz_version.h"
#include "rz_system.h"
#include "rz_mqtt.h"

// create instances
RZ_System *esp32System = new RZ_System(); 
RZ_WiFi *mywifi = new RZ_WiFi(wifiSsid, wifiPassword);
RZ_Version *versions = new RZ_Version();

// ##### Timer
unsigned long previousMillis = 0;

// # CPUs
TaskHandle_t  Core0TaskHnd ;  
TaskHandle_t  Core1TaskHnd ; 

void setDisplayDefault() {
  M5.Lcd.setTextSize(1);
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setTextColor(TFT_GREEN, TFT_BLACK);
}

void setup() {
  M5.begin();
  M5.Power.begin();

  xTaskCreatePinnedToCore(CoreTask0,"CPU_0",1000,NULL,1,&Core0TaskHnd,0);
  xTaskCreatePinnedToCore(CoreTask1,"CPU_1",1000,NULL,1,&Core0TaskHnd,1);
  
  M5.Power.setWakeupButton(BUTTON_A_PIN);
  Wire.begin();
  
// ###
  std::string bufferStr;
  Serial.print("\nStarting\n- "); 
  Serial.print(appTitle); Serial.print(" v"); Serial.println(appVersion);
  Serial.print("-- on "); Serial.println(esp32System->getHostName().c_str());
  
  Serial.print(F("- Initializing WiFi\n"));
  if(mywifi->startWiFi()) {
    Serial.print("\n-- Connected to ");
    Serial.println(wifiSsid);
    Serial.print("-- IP-Address "); Serial.println(mywifi->getIpAddr());

    Serial.print(F("- Initializing MDNS responder\n"));
    if(mywifi->startMDNS(esp32System->getHostName())) {
      bufferStr = esp32System->getHostName() + ".local";
      Serial.print("-- MDNS started: "); Serial.println(bufferStr.c_str());
    }
    else {
      Serial.println("-- MDNS failed");
    }
  }
  else {
    Serial.println("\n-- WiFi connect failed. => restart in 10 seconds\n");
    delay(10000);
    esp32System->doRestart();
  }

  if(enableMQTT) {
    char buffer[20];
    Serial.print(F("- Initializing MQTT client\n"));
    Serial.print("-- MQTT publish interval in seconds: ");
    Serial.println(mqttInterval / 1000);
    rz_mqttclient_start(esp32System->getHostName());
    bufferStr = esp32System->getHostName() + "/status";
    esp32System->ntpLocalTime(ntpServer, gmtOffset_sec, daylightOffset_sec);
    strcpy(buffer, esp32System->getDateTimeString().c_str()); 
    rz_mqtt_sendMsg(bufferStr, buffer); 
    sendMqttData();
    delay(1000);
  }
  
// ###

  setDisplayDefault();

  delay(1000);
}

void sendMqttData() {
  std::string bufferStr;
  char buffer[10];
  char ntpBuffer[20];

  bufferStr = esp32System->getHostName() + "/status";
  esp32System->ntpLocalTime(ntpServer, gmtOffset_sec, daylightOffset_sec);
  strcpy(ntpBuffer, esp32System->getDateTimeString().c_str()); 
  //Serial.println(
  rz_mqtt_sendMsg(bufferStr, ntpBuffer); 
  
  bufferStr = esp32System->getHostName() + "/temperature";
  dtostrf(dht12.readTemperature(), 6,2, buffer); 
  rz_mqtt_sendMsg(bufferStr, buffer); 

  bufferStr = esp32System->getHostName() + "/humidity";
  dtostrf(dht12.readHumidity(), 6,2, buffer); 
  rz_mqtt_sendMsg(bufferStr, buffer);   
}

void loop() {
  
  M5.update(); //Read the press state of the key.
  bool c=M5.Power.isResetbyPowerSW(); //Determine if M5Core is started when powered on.
  bool d=M5.Power.isResetbyDeepsleep(); //Determine if M5Core starts after deep sleep.
  
  if (M5.BtnA.wasPressed()) {
    Serial.println('A');
    setDisplayDefault();
  } else if (M5.BtnB.wasPressed()) {
    Serial.println('B');
    M5.Lcd.clear(WHITE);  // Clear the screen and set white to the background color.
    M5.Lcd.setCursor(0, 0);
    delay(2000);
    M5.Power.setPowerBoostKeepOn(false);
    M5.Power.deepSleep(TIME_TO_SLEEP);
    //esp32System->doStartDeepSleep(TIME_TO_SLEEP);
  } else if (M5.BtnC.wasPressed()) {
    Serial.println('C');
    delay(2000);
    M5.Power.powerOFF();
  }
/*  
  M5.Lcd.setTextSize(1);
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setTextColor(TFT_GREEN, TFT_BLACK);
*/   

    //Read temperature with preset scale.
    String outStr = "";
    M5.Lcd.drawString("Temperatur: ", 20, 60, 4);
    outStr.concat(dht12.readTemperature());
    outStr.concat("\x60");
    outStr.concat("C");
    M5.Lcd.drawString(outStr, 170, 60, 4);
  
  
    //Read humidity.
    M5.Lcd.drawString("Luftfeuchte : ", 20, 130, 4);
     outStr = "";
     outStr.concat(dht12.readHumidity());
     outStr.concat("%");
     M5.Lcd.drawString(outStr, 170, 130, 4);
  
  delay(2000);

    if(deepSleep) {
      int do_delay = 15000;
      Serial.println("- Initializing ESP32 Deep Sleep");
      Serial.print("-- in: ");
      Serial.print(do_delay/1000);
      Serial.println(" Seconds");
      Serial.print("-- duration: "); 
      Serial.print(TIME_TO_SLEEP/60000000); 
      Serial.println(" Minutes");
      delay(do_delay);
      M5.Power.setPowerBoostKeepOn(false);
      M5.Power.deepSleep(TIME_TO_SLEEP);
    }
}

void CoreTask0( void * parameter ) 
{ 
  for (;;) 
  { 
    //Serial.print("CoreTask0 runs on Core: "); 
    //Serial.println(xPortGetCoreID()); 

// ###
    if(enableMQTT) {
      // Serial.println("MQTT Timer Loop");
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= mqttInterval) {
        previousMillis = currentMillis;
        sendMqttData();
      }
    }
// ###
    
    yield();
    delay (600);
  } 
} 

void CoreTask1( void * parameter ) 
{ 
  for (;;) 
  { 
    //Serial.print("CoreTask1 runs on Core: "); 
    //Serial.println(xPortGetCoreID()); 
   
    delay (700);
  } 
}
