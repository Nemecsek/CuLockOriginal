#include "SPI.h"
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <esp_wifi.h>

#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <stdio.h>
#include <string.h>
#include <ESP32Time.h>

#include <Preferences.h>
#include <nvs_flash.h>
#include "time.h"

#include "lcd.h"
#include "alphabet2.h"
#include "lang_ve.h"
#include "lang_it.h"
#include "lang_de.h"
#include "lang_en.h"
#include "lang_es.h"
#include "lang_tp.h"
#include "lang_fr.h"
#include "lang_eo.h"

#include "RTClib.h"
RTC_DS3231 rtcDs3231;

const int SCLpin = 10;
const int SDApin = 11; 

bool foundDS3231 = false;

#define EEPROM_RESET_CODE   0xcaff
#define DEF_SSID "WIFI_SSID_HERE" 
#define DEF_PWD  "WIFI_PWD_HERE"

// char map 
#define NUM_COLS  16  // chars in a row
#define NUM_ROWS   8  // rows in the screen
#define HCHAR     35  // width single char in pixels
#define WCHAR     28  // height single char

// serial buffer to receive settings commands
#define LEN_SERIAL_BUFFER  100
char serial_buffer[LEN_SERIAL_BUFFER];
int serial_ptr = 0;

#define SPrintf   Serial.printf
#define SPrint    Serial.print
#define SPrintln  Serial.println


WiFiServer server(80);

const char* NTP_SERVER = "pool.ntp.org";
// const char* NTP_SERVER = "time.nist.org";

const char* ssid     = "CuLock ω";
const char* password = "123456789";



// Variable to store the HTTP request
String header;

String html1 = R""""(
    <!DOCTYPE html>
    <html>
    <head>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link rel="icon" href="data:,">
        <style>

        body {
            font-family: Arial, Helvetica, sans-serif;
            font-size: 12pt;
            font-weight: 700;
            background-color: aliceblue;
        }

        .small_button {
            width: 35px;
            height: 25px;
            border: none;
            padding: 3px;
            margin: 2px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            background-color: lightgray;
        }

        .big_button {
            width: 100px;
            height: 25px;
            border: none;
            padding: 3px;
            margin: 2px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            background-color: lightgray;
        }

        p {
            font-family: Arial, Helvetica, sans-serif;
            font-size: 10pt;
            font-weight: 500;
            color: dodgerblue;
        }

        .nice_input {
            width: 100px;
            height: 25px;
            border: none;
            padding: 3px;
            margin: 2px;
            display: inline-block;
            background-color: yellow;
            border: none;
        }

        </style>
    </head>
    <body>
        <center><h3>CuLock &omega;</h3></center>

        <form>
            <input class="nice_background" type="text" id="wifis" name="wifis" value="" onkeydown="if (event.keyCode == 13) { this.form.submit(); }">
            <button class="big_button" style="color:black" type="submit">Set WiFi SSID</button>
        </form>
        <form>
            <input class="nice_background" type="text" id="wifip" name="wifip" value="" onkeydown="if (event.keyCode == 13) { this.form.submit(); }">
            <button class="big_button" style="color:black" type="submit">Set WiFi Pwd</button>
        </form>
        <form>
            <button class="big_button" style="color:black" disabled>Time</button>
            <input class="nice_background" type="time" id="time" name="time" step=1 onchange="this.form.submit()">
        </form>

        <br>
        <center><form>
            <button class="small_button" name="language" id="language" value="0" type=submit">EN</button>
            <button class="small_button" name="language" id="language" value="1" type=submit">IT</button>
            <button class="small_button" name="language" id="language" value="2" type=submit">VN</button>
            <button class="small_button" name="language" id="language" value="3" type=submit">DE</button>
            <button class="small_button" name="language" id="language" value="4" type=submit">ES</button>
            <button class="small_button" name="language" id="language" value="5" type=submit">FR</button>
            <button class="small_button" name="language" id="language" value="6" type=submit">TP</button>
            <button class="small_button" name="language" id="language" value="7" type=submit">EO</button>
        </form>
        <br>
        <form>
            <button class="big_button" name="text_color" id="text_color" style="background:#fff;" value="111" type="submit">white</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#ff8;" value="112" type="submit">lightyellow</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#ff2;" value="114" type="submit">yellow</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#f88;" value="122" type="submit">peach</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#f82;" value="124" type="submit">orange</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#f22;" value="144" type="submit">red</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#f28;" value="142" type="submit">light red</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#f2f;" value="141" type="submit">fuchsia</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#f8f;" value="121" type="submit">pink</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#82f;" value="241" type="submit">lila</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#828;" value="242" type="submit">red-lila</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#822;" value="244" type="submit">brown</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#444;" value="444" type="submit">dark gray</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#888;" value="222" type="submit">medium gray</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#882;" value="224" type="submit">mustard</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#288;" value="422" type="submit">sea green</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#282;" value="424" type="submit">dark green</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#2f2;" value="414" type="submit">green</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#2f8;" value="412" type="submit">light green</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#8ff;" value="211" type="submit">white sky</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#2ff;" value="411" type="submit">sky blue</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#28f;" value="421" type="submit">light blue</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#22f;" value="441" type="submit">blue</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#228;" value="442" type="submit">dark blue</button>
        </form>
        <br>
        <form>
            <button class="big_button" name="gray" id="gray" value="1" style="background:#CCC;" type="submit">Off Chars</button>
            <button class="big_button" name="gray" id="gray" value="2" style="background:#AAA;" type="submit">Off Chars</button>
            <button class="big_button" name="gray" id="gray" value="3" style="background:#888;" type="submit">Off Chars</button>
        </form>
        <form>
            <button class="big_button" name="brightness" id="brightness" value="1" style="background:#CCC;" type="submit">Backlight</button>
            <button class="big_button" name="brightness" id="brightness" value="2" style="background:#AAA; "type="submit">Backlight</button>
            <button class="big_button" name="brightness" id="brightness" value="3" style="background:#888; "type="submit">Backlight</button>
        </form>
        <form>
            <button class="big_button" name="extra_hour" id="extra_hour" value="1" type="submit">+1h</button>
            <button class="big_button" name="extra_hour" id="extra_hour" value="0" type="submit">0h</button>
            <button class="big_button" name="extra_hour" id="extra_hour" value="-1" type="submit">-1h</button>
        </form>
        <form>
            <button class="big_button" name="rotate" id="rotate" value="1" type="submit">Rotate</button>
        </form>
        <form>
            <button class="big_button" name="demo" id="demo" value="1" type="submit">Demo</button>
        </form>

        </center>
)"""";


LGFX lcd;
LGFX_Sprite lcd_buff(&lcd);  

ESP32Time rtc(0);  // GMT offset set later

Preferences prefs; // preferences in eeprom

// int idx = 0;    // used for debug
int last_minute_map_was_updated = 255; // char maps is updated every minute; if the loop is too fast, we want to avoid refreshing it multiple times
struct tm timeinfo;  // used to load the time

// previous and current light status
// to make a quicker refresh, each char in previous_ and current_ are compared, if different the char is refreshed.
// if current_ is 0 the char is turned off, 1 it is turned on. 
// after refresh current_ is copied on previous_.
// to force the complete refresh, all chars in previous_ are set to 2, an invalid value
byte previous_light_status[NUM_ROWS*NUM_COLS];  // when refreshing the map, only the chars where the two array are different
byte current_light_status[NUM_ROWS*NUM_COLS];   // are refreshed.
bool map_changed = true;            // set to 1 after a new word must be printed to call for an immediate screen update
byte last_minute_map_updated = 255; // to avoid to refresh multiple times the screen when second=0, we store the last minute when it happened

// variables read from preferences
long gmtOffset_sec;   // used to calculate the real time from ntp
int daylightOffset_sec; 
int language; 
int display_rot;
int lcd_brightness;
int divR;
int divG;
int divB;
int div_gray;
int extra_hour;
int demo=0;  // if 1 fast demo
String wifi_ssid;
String wifi_pwd;

int demo_hour = 0;
int demo_5minutes = 0;


String readMaskedPwd() {
    // used to show the wifi password hiding some of the chars
    String pwd = prefs.getString("pwd","");
    if (pwd.length() > 7) { // valid pwd are at least 8 chars long, show only the first and last two
        for (int i=2; i<pwd.length()-2; i++) pwd.setCharAt(i, '*');
    }
    return pwd;
}


void printPrefs() {
    SPrintln("-prefs--------------------------------------");
    SPrintf("init=%d\r\n", prefs.getUInt("init", 9999));
    SPrintf("divR=%d\r\n", prefs.getInt("divR", 9999));
    SPrintf("divG=%d\r\n", prefs.getInt("divG", 9999));
    SPrintf("divB=%d\r\n", prefs.getInt("divB", 9999));
    SPrintf("div_gray=%d\r\n", prefs.getInt("div_gray", 9999));
    SPrintf("ssid=%s\r\n", prefs.getString("ssid", "").c_str());
    SPrintf("pwd=%s\r\n",  readMaskedPwd().c_str());
    SPrintf("language=%d\r\n",      prefs.getInt("language", 9999));
    SPrintf("display_rot=%d\r\n",   prefs.getInt("display_rot", 9999));
    SPrintf("extra_hour=%d\r\n",    prefs.getInt("extra_hour", 9999));
    SPrintf("gmt_offset=%d\r\n",    prefs.getInt("gmt_offset", 9999));
    SPrintf("daylight_offs=%d\r\n", prefs.getInt("daylight_offs", 9999));
    SPrintf("brightness=%d\r\n",    prefs.getInt("brightness", 9999));
    SPrintln("---------------------------------------------");
    SPrintln(&timeinfo, "%Y-%m-%d %H:%M:%S");
    SPrintln("---------------------------------------------");
}


// void cleanDebugRow() {
//     // clears the upper line of display where debug info are read
//     lcd.drawString("                                                                                ", 0, 10);
//     lcd_buff.drawString("                                                                                ", 0, 10);
// }

#include "lcd_routines.h"


unsigned char h2int(char c) {
    if (c >= '0' && c <='9'){
        return((unsigned char)c - '0');
    }
    if (c >= 'a' && c <='f'){
        return((unsigned char)c - 'a' + 10);
    }
    if (c >= 'A' && c <='F'){
        return((unsigned char)c - 'A' + 10);
    }
    return(0);
}


void accessPointSetup() {

    // Connect to Wi-Fi network with SSID and password
    Serial.print("Setting AP (Access Point)...");

    // WiFi.onEvent(OnWiFiEvent);    
    WiFi.softAP(ssid, password); // open if password is NULL

    delay(2000);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    server.begin();
}


String urldecode(String str) {
    
    String encodedString="";
    char c;
    char code0;
    char code1;
    for (int i =0; i < str.length(); i++){
        c=str.charAt(i);
        if (c == '+'){
            encodedString+=' ';  
        }
        else if (c == '%') {
            i++;
            code0=str.charAt(i);
            i++;
            code1=str.charAt(i);
            c = (h2int(code0) << 4) | h2int(code1);
            encodedString+=c;
        } 
        else{
            encodedString+=c;  
        }
      
        yield();
    }
    
   return encodedString;
}

//===================================================================================================


void setTimezone(String timezone){
  Serial.printf("  Setting Timezone to %s\n",timezone.c_str());
  setenv("TZ",timezone.c_str(),1);  //  Now adjust the TZ.  Clock settings are adjusted to show the new local time
  tzset();
}

void setup(void) {

    delay(500);

    Serial.begin(115200);
    delay(500);
    
    // Serial.setTimeout(10);

    SPrintln("Started");

    // init preferences
    prefs.begin("cfg"); //namespace
    if (prefs.getUInt("init") != EEPROM_RESET_CODE) {
        SPrintln(">>>>>>>>>>>> Prefs initialized!");
        prefs.putUInt("init", EEPROM_RESET_CODE);
        prefs.putInt("divR", 1);
        prefs.putInt("divG", 1);
        prefs.putInt("divB", 1);
        prefs.putInt("div_gray", 48);
        prefs.putString("ssid", DEF_SSID);
        prefs.putString("pwd", DEF_PWD);
        prefs.putInt("language", 0);
        prefs.putInt("display_rot", 1);
        prefs.putInt("extra_hour", 0);
        prefs.putInt("gmt_offset", 3600);
        prefs.putInt("daylight_offs", 3600);
        prefs.putInt("lcd_brightness", 128);
    }
    else {
        SPrintln("----------------------------");
        SPrintln("Prefs values read");
    }

    printPrefs();

    // initialize parameters read from prefs
    divR = prefs.getInt("divR", 1);
    divG = prefs.getInt("divG", 1);
    divB = prefs.getInt("divB", 1);
    div_gray = prefs.getInt("div_gray", 48);
    wifi_ssid = prefs.getString("ssid", DEF_SSID);
    wifi_pwd = prefs.getString("pwd", DEF_PWD);
    language = prefs.getInt("language", 0);
    extra_hour = prefs.getInt("extra_hour", 0);
    display_rot = prefs.getInt("display_rot", 1);
    gmtOffset_sec = prefs.getInt("gmt_offset", 0);   // used to calculate the real time from ntp
    daylightOffset_sec = prefs.getInt("daylight_offs", 0);
    lcd_brightness = prefs.getInt("lcd_brightness", 128);

    rtc.offset = gmtOffset_sec;

    // init display and buffer
    lcd.init();
    lcd.setColorDepth(24);  
    lcd.setRotation(display_rot);  // landscape
    lcd.setBrightness(lcd_brightness);  // brightness

    lcd_buff.setColorDepth(24);
    lcd_buff.setPsram(true);
    lcd_buff.createSprite(480, 320);
    lcd_buff.clear();
    lcd_buff.fillScreen(lcd.color888(0,0,0));

    force_complete_redraw();  

    // cleanDebugRow();

    // check if DS3231 is available
    Wire.begin(SDApin, SCLpin);

    if (rtcDs3231.begin()) {
        Serial.println("RTC has been found!");
        foundDS3231 = true;

        if (rtcDs3231.lostPower()) {
            Serial.println("RTC lost power, let's set the time!");
            // When time needs to be set on a new device, or after a power loss, the
            // following line sets the RTC to the date & time this sketch was compiled
            rtcDs3231.adjust(DateTime(2023, 1, 1, 3,4,5));
        }

        // at start transfer the current time from DS3231 to internal rtc
        DateTime now = rtcDs3231.now();
        rtc.setTime(now.second(), now.minute(), now.hour(), 1, 1, 2023);
    }
    else {
        Serial.println("RTC not found");
        foundDS3231 = false;
    }
    
    // read date/time from WIFI
    if (!foundDS3231) { 
    
        String maskedPwd = readMaskedPwd();

        SPrint("Trying WiFi connection with SSID ");
        SPrint(wifi_ssid.c_str());
        SPrint(" and PWD ");
        SPrintln(maskedPwd.c_str());
        delay(500);
        
        lcd.drawString("WiFi", 10,10);
        lcd.drawString(wifi_ssid.c_str(), 10, 20);
        lcd.drawString(maskedPwd.c_str(), 10, 30);
        delay(500);

        //connect to WiFi
        int timeout_counter = 20; // 10 seconds wifi timeout

        if (wifi_ssid == "" || wifi_pwd == "") {
            SPrintln("Missing ssid/pwd");
            timeout_counter = 0;   // don't enter wifi search
        }
        else {
            SPrintf("Connecting to %s ", wifi_ssid.c_str());
            WiFi.begin(wifi_ssid.c_str(), wifi_pwd.c_str());

            while ((WiFi.status() != WL_CONNECTED) && timeout_counter) {
                delay(500);
                SPrint(".");
                timeout_counter--;
            }
        }

        if (timeout_counter) {  // connection was ok
            Serial.print("Setting NTP time ");
            configTime(gmtOffset_sec, daylightOffset_sec, NTP_SERVER);
            delay(500);
            setTimezone("CET-1CEST,M3.5.0,M10.5.0/3");
            getLocalTime(&timeinfo);
            SPrintln(&timeinfo, "to %Y-%m-%d %H:%M:%S");
        }
        else {
            lcd.fillScreen(0);
            lcd.drawString("NTP failed", 0, 0);
            SPrintln("NTP Failed");

            rtc.setTime(0, 0, 0, 1, 1, 2023);
        }
        lcd.fillScreen(0);
        
        //disconnect WiFi as it's no longer needed
        WiFi.disconnect(true);
        WiFi.mode(WIFI_OFF);
    }
    
    clear_map();

    accessPointSetup();

    esp_wifi_set_ps(WIFI_PS_NONE);
    // WiFi.setTxPower(WIFI_POWER_MINUS_1dBm);
    // setCpuFrequencyMhz(80);
}

//===================================================================================================

String requestParam(String request, String param) {
    if (request.indexOf(param + "=") != -1) {
        int foundEqual = request.indexOf("=");
        int foundHTTP = request.indexOf(" HTTP/");
        String value = request.substring(foundEqual+1, foundHTTP);
        return urldecode(value);
    }
    return "";
}

void actionDisplayRotation() {
    lcd.setRotation(display_rot);
    prefs.putInt("display_rot", display_rot);
    force_complete_redraw();
}

void actionTime(int h, int m, int s) {
    rtc.setTime(s, m, h, 1, 1, 2023);

    if (foundDS3231) {  // if present set Ds3231 time
        rtcDs3231.adjust(DateTime(2023, 1, 1, h, m, s));
    }

    SPrintf("Time %02d:%02d:%02d has been set.\r\n", h,m,s);
    force_complete_redraw();
}

void actionBrightness() {
    lcd.setBrightness(lcd_brightness);
    prefs.putInt("lcd_brightness", lcd_brightness);
    SPrintf("Brightness %d has been set.\r\n", lcd_brightness);
}

void actionGray() {
    prefs.putInt("div_gray", div_gray);
    SPrintf("Gray darkness %d has been set.\r\n", prefs.getInt("div_gray", 9999));
    force_complete_redraw();
}

void actionExtraHour() {
    prefs.putInt("extra_hour", extra_hour);
    SPrintf("Extra hour %d has been set.\r\n", prefs.getInt("extra_hour", 9999));
    force_complete_redraw();
}


void actionLanguage() {
    prefs.putInt("language", language);
    SPrintf("Set language code to %d\r\n", prefs.getInt("language", 9999));
    force_complete_redraw();
}

void actionColor() {
    prefs.putInt("divR", divR);
    prefs.putInt("divG", divG);
    prefs.putInt("divB", divB);

    SPrintf("Color %d %d %d has been set.\r\n", prefs.getInt("divR", 9999),
                                                prefs.getInt("divG", 9999), 
                                                prefs.getInt("divB", 9999));
    force_complete_redraw();                
}

void actionWifiSsid(String ssid) {
    prefs.putString("ssid", ssid);
    SPrintf("New ssid '%s' has been set.\r\n", prefs.getString("ssid", "nope").c_str());
}

void actionWifiPwd(String pwd) {
    prefs.putString("pwd", pwd);
    SPrintf("New pwd '%s' has been set.\r\n", prefs.getString("pwd", "nope").c_str());
}

// void actionDebug(int debug) {
//     SPrintf("Debug on/off: %d", debug);
//     if (debug == 0) cleanDebugRow();
// }



void accessPointLoop() {

    WiFiClient client = server.available();   // Listen for incoming clients

    if (client) {  
        
        String request = client.readStringUntil('\r');
        String value;

        if ((value = requestParam(request, "time")) != "") {
            int h = value.substring(0,2).toInt();
            int m = value.substring(3,5).toInt();
            int s = value.substring(6,8).toInt();
            actionTime(h, m, s);
        }
        else if ((value = requestParam(request, "rotate")) != "") {
            display_rot = display_rot == 1 ? 3:1;
            actionDisplayRotation();
        }
        // else if ((value = requestParam(request, "debug")) != "") {
        //     debug = debug ? 0:1;
        //     actionDebug(debug);
        // }
        else if ((value = requestParam(request, "wifis")) != "") {
            actionWifiSsid(value);
        }
        else if ((value = requestParam(request, "wifip")) != "") {
            actionWifiPwd(value);
        }
        else if ((value = requestParam(request, "language")) != "") {
            language = value.toInt();
            SPrint("language " + value);
            actionLanguage();
        }
        else if ((value = requestParam(request, "text_color")) != "") {
            SPrintln("text color " + value);
            int v = value.toInt();
            divR = v / 100;
            v %= 100;
            divG = v / 10;
            divB = v % 10;
            actionColor();
        }
        else if ((value = requestParam(request, "gray")) != "") {
            SPrintln("gray color " + value);
            if (value == "1") div_gray = 20;
            else if (value == "2") div_gray = 48;
            else if (value == "3") div_gray = 64;
            actionGray();
        }
        else if ((value = requestParam(request, "brightness")) != "") {
            SPrintln("lcd brightness " + value);
            if (value == "1") lcd_brightness = 255;
            else if (value == "2") lcd_brightness = 64;
            else if (value == "3") lcd_brightness = 20;
            actionBrightness();
        }
        else if ((value = requestParam(request, "extra_hour")) != "") {
            SPrintln("Extra hour " + value);
            if (value == "1")       extra_hour = 1;
            else if (value == "0")  extra_hour = 0;
            else if (value == "-1") extra_hour = -1;
            actionExtraHour();
        }
        else if ((value = requestParam(request, "demo")) != "") {
            demo = 1-demo;
            demo_hour = 0;
            demo_5minutes = 0;
            force_complete_redraw();
        }
        else Serial.println(request);

        // show current values in prefs
        char timeStringBuff[50]; //50 chars should be enough
        strftime(timeStringBuff, sizeof(timeStringBuff), "%Y-%m-%d %H:%M:%S", &timeinfo);
        String html2 = "<hr><p>" + String(timeStringBuff) + "</p><hr>";
        html2 += "<p>init=" + String(prefs.getUInt("init", 9999)) + "</p>";
        html2 += "<p>divR=" + String(prefs.getInt("divR", 9999)) + "</p>";
        html2 += "<p>divG=" + String(prefs.getInt("divG", 9999)) + "</p>";
        html2 += "<p>divB=" + String(prefs.getInt("divB", 9999)) + "</p>";
        html2 += "<p>div_gray=" + String(prefs.getInt("div_gray", 9999)) + "</p>";
        html2 += "<p>ssid=" + String(prefs.getString("ssid", "9999").c_str()) + "</p>";
        html2 += "<p>pwd=" + readMaskedPwd() + "</p>";
        html2 += "<p>language=" + String(prefs.getInt("language", 9999)) + "</p>";
        html2 += "<p>brightness=" + String(prefs.getInt("brightness", 9999)) + "</p>";
        html2 += "<p>extra_hour=" + String(prefs.getInt("extra_hour", 9999)) + "</p>";
        html2 += "</body></html>";

        client.print(html1 + html2);
        request="";

        // Close the connection
        client.stop();
        Serial.println("Client disconnected.");
        Serial.println("");

    }
}

//===================================================================================================

void loop(void) {

    getLocalTime(&timeinfo);

    int hour = timeinfo.tm_hour;
    int minute = timeinfo.tm_min;
    int second = timeinfo.tm_sec;

    if (demo) {  // demo 1 second=5 min

        second = 0;
        minute = demo_5minutes * 5;
        hour = demo_hour;

        last_minute_map_was_updated = 9999;

        demo_5minutes++;
        demo_5minutes %= 12;
        if (demo_5minutes == 0) {
            demo_hour++;
            demo_hour %= 24;
        }
    }

    if (map_changed || (second == 0 && last_minute_map_was_updated != minute)) {

        if ((extra_hour >= -1) && (extra_hour <= 1)) {
            hour += extra_hour;
            if (hour > 23) hour -= 24;
            else if (hour < 0) hour += 24;
        }

        last_minute_map_was_updated = minute;

        SPrint("\nupdate ");
        SPrint(hour);
        SPrint(":");
        SPrint(minute);
        SPrint(":");
        SPrintln(second);

        clear_map();

        // add the map to lcd_routines.h / updateChangedChars
        switch (language) {
            case 1:   IT_time(hour, minute, second); break;
            case 2:   VE_time(hour, minute, second); break;
            case 3:   DE_time(hour, minute, second); break;
            case 4:   ES_time(hour, minute, second); break;
            case 5:   FR_time(hour, minute, second); break;
            case 6:   TP_time(hour, minute, second); break;
            case 7:   EO_time(hour, minute, second); break;
            default:  EN_time(hour, minute, second); break;
        } 
    
        updateChangedChars();

        lcd_buff.pushSprite(0,0);
        map_changed = false;
    }

    // printDebugData();

    accessPointLoop();

    delay(300);  
}