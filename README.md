<div id="top"></div>
<br />
<div align="center">
  <h3 align="center">M5core DHT12</h3>
        M5Stack Temperature and Humidity via Display, Wifi & MQTT client
<br/>
<br/>
  <a href="https://github.com/Zheng-Bote/M5Stack_DHT12_Displ_Wifi_MQTT/issues">Report Bug</a>
  <a href="https://github.com/Zheng-Bote/M5Stack_DHT12_Displ_Wifi_MQTT/pulls">Request Feature</a>
  <br/>
</div>

<br/>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#brief">Brief</a></li>
    <li><a href="#description">Description</a></li>
    <li><a href="#author">Author</a></li>
    <li><a href="#source">Source</a></li>
    <li><a href="#dependencies">Dependencies</a></li>
    <li><a href="#syntax">Syntax</a></li>
    <li><a href="#examples">Examples</a></li>
  </ol>
</details>
<br/>

#### BRIEF:

<span id="brief"></span>
M5Stack Temperature and Humidity via Display, Wifi & MQTT client

### VERSION:

<span id="version"></span>
1.1.0

### Status

![ops](https://img.shields.io/badge/Status-usable-green)

### DESC:

<span id="description"></span>
DHT12 sensor reads temperature, humidity and display the data on the screen and send data via MQTT.

- Deep Sleep after defined time

- Button A: Wake up from Deep Sleep

- Button B: start Deep Sleep

- Button C: shutdown M5Stack

### AUTHOR:

<span id="author"></span>
ZHENG Robert

### SOURCE:

<span id="source"></span>
https://github.com/Zheng-Bote/M5Stack_DHT12_Displ_Wifi_MQTT

### DEPENDENCIES:

<span id="dependencies"></span>

#### #include <M5Stack.h>

runs on M5core

see https://m5stack.com/

#### Arduino IDE

see https://www.arduino.cc/

#### Arduino Libraries

- #include "DHT12.h"

- #include <Wire.h> //The DHT12 uses I2C comunication.

#### ESP32 libs

- #include "credentials.h"
- #include "rz_wifi.h"
- #include "rz_version.h"
- #include "rz_system.h"

License: MIT

<p align="right">(<a href="#top">back to top</a>)</p>

#### EXAMPLES:

<span id="examples"></span>

seriell monitor output

```
M5Stack initializing...
OK

Starting
- M5Stack Temp/Hum Wifi & MQTT client v1.1.0
-- on ESP32-C0EC
- Initializing WiFi
...
-- Connected to stairway_to_lan
-- IP-Address 192.168.x.y
- Initializing MDNS responder
-- MDNS started: ESP32-C0EC.local
- Initializing MQTT client
-- MQTT publish interval in seconds: 900
-- connected
- Initializing ESP32 Deep Sleep
-- in: 15 Seconds
-- duration: 15 Minutes
```

<p align="right">(<a href="#top">back to top</a>)</p>

### SETUP:

<span id="setup"></span>

#### #include "credentials.h":

adjust the credentials in the header only library, at least WiFi credentials

```
// ##### WiFi credentials
char *wifiSsid = "stairway_to_lan";
char *wifiPassword = "top_secret_123";

// ##### DHT credentials
//=> see rz_dht.h|cpp

// ##### MQTT credentials
IPAddress mqttServer(192, 168, x, y);
int mqttPort = 1883;
char *mqttUser = "Tasmota_User";
char *mqttPwd = "Tasmota_Password";

// run MQTT and do intervall publishing
bool enableMQTT = true;

// Intervall Timer (Milliseconds) for MQTT publish
//const long mqttInterval = 300000; // 5 Mins
const long mqttInterval = 900000; // 15 Mins
//const long mqttInterval = 1800000; // 30 Mins
//const long mqttInterval = 3600000; // 60 Mins


// ##### Webserver credentials
// run webserver
bool enableWebserver = false;
int webserverPort = 80;

// ##### System credentials
// time sync
char* ntpServer = "de.pool.ntp.org";
// offset in seconds between your time zone and GMT
long gmtOffset_sec = 3600;
// offset in seconds for daylight saving time.
int daylightOffset_sec = 3600;

// run deepsleep and e.g. run mqtt publish after wakeup
bool deepSleep = true;
// Time ESP32 will go to sleep (in milliseconds)
//const unsigned long long TIME_TO_SLEEP = 0;
//const unsigned long long TIME_TO_SLEEP = 300;  // 5 Mins
const unsigned long long TIME_TO_SLEEP = 900000000;  // 15 Mins
//const unsigned long long TIME_TO_SLEEP = 1800; // 30 Mins
//const unsigned long long TIME_TO_SLEEP = 3600; // 60 Mins

// Serial Speed
const uint32_t SERIAL_SPEED{115200};

// check for firmware updates
const bool CHECK_FIRMWARE = true;
// do firmware update => not yet implemented
const bool DO_FIRMWARE_UPDATE = false;
```

<p align="right">(<a href="#top">back to top</a>)</p>

### HISTORY:

<span id="history"></span>

> | Version | Date       | Developer | Comments                |
> | ------- | ---------- | --------- | ----------------------- |
> | 1.0.0   | 2018       | RZheng    | created                 |
> | 1.1.0   | 2024-05-18 | RZheng    | some small improvements |

## Contributing

<span id="contributing"></span>

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- CONTACT -->

## Contact

<span id="contact"></span>

ZHENG Robert Zhèng Bó Tè 郑 伯特

Project Link: [https://github.com/Zheng-Bote/M5Stack_DHT12_Displ_Wifi_MQTT/](https://github.com/Zheng-Bote/M5Stack_DHT12_Displ_Wifi_MQTT/)

:vulcan_salute:

<p align="right">(<a href="#top">back to top</a>)</p>
