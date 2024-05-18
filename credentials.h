/*
LIB: credentials.h
DESC: header with customizable vars

SOURCE: https://github.com/Zheng-Bote/esp32_dht_webserver_mqtt-client

Version | Date       | Developer  | Comments
------- | ---------- | ---------- | -----------------------------------------------
0.5.0   | 2022-02-26 | RZheng     | created
1.0.0   | 2022-02-27 | RZheng     | NTP added
1.1.0   | 2022-02-27 | RZheng     | changed ESP32 deep sleep type of TIME_TO_SLEEP

*/

// ##### WiFi credentials
char *wifiSsid = "stairway_to_lan";
char *wifiPassword = "top_secret_123";

// ##### DHT credentials
//=> see rz_dht.h|cpp

// ##### MQTT credentials
IPAddress mqttServer(192, 168, 178, 253);
int mqttPort = 1883;
char *mqttUser = "Tasmota_User";
char *mqttPwd = "Tasmota_Password";

// run MQTT and do intervall publishing
bool enableMQTT = true;

// Intervall Timer (Milliseconds) for MQTT publish
// const long mqttInterval = 300000; // 5 Mins
const long mqttInterval = 900000; // 15 Mins
// const long mqttInterval = 1800000; // 30 Mins
// const long mqttInterval = 3600000; // 60 Mins

// ##### Webserver credentials
// run webserver
bool enableWebserver = false;
int webserverPort = 80;

// ##### System credentials
// time sync
char *ntpServer = "de.pool.ntp.org";
// offset in seconds between your time zone and GMT
long gmtOffset_sec = 3600;
// offset in seconds for daylight saving time.
int daylightOffset_sec = 3600;

// run deepsleep and e.g. run mqtt publish after wakeup
bool deepSleep = true;
// Time ESP32 will go to sleep (in milliseconds)
// const unsigned long long TIME_TO_SLEEP = 0;
// const unsigned long long TIME_TO_SLEEP = 300;  // 5 Mins
const unsigned long long TIME_TO_SLEEP = 900000000; // 15 Mins
// const unsigned long long TIME_TO_SLEEP = 1800; // 30 Mins
// const unsigned long long TIME_TO_SLEEP = 3600; // 60 Mins

// Serial Speed
const uint32_t SERIAL_SPEED{115200};

// check for firmware updates
const bool CHECK_FIRMWARE = true;
// do firmware update => not yet implemented
const bool DO_FIRMWARE_UPDATE = false;
