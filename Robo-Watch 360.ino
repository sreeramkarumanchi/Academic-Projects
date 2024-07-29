//RoboWatch 360 Integrated Surveillanace System with Real-Time Weather Monitoring

//Arduino UNO code

#include Wire.h
#include Adafruit_BMP085.h
#include Adafruit_Sensor.h
#include DHT.h
#include TinyGPS++.h
#include SoftwareSerial.h
#define DHTPIN 2
#define DHTTYPE DHT11
Create object named bt of the class SoftwareSerial
SoftwareSerial bt(5, 4);   (Rx,Tx)   only 2
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;
TinyGPSPlus gps;
int m1 = 8;
int m2 = 9;
int m3 = 10;
int m4 = 11;
 
char value;
void setup() {
 Serial.begin(9600);
 bt.begin(9600);
 Wire.begin();
 pinMode(m1, OUTPUT);
 pinMode(m2, OUTPUT);
 pinMode(m3, OUTPUT);
 pinMode(m4, OUTPUT);
 digitalWrite(m1, LOW);
 digitalWrite(m2, LOW);
 digitalWrite(m3, LOW);
 digitalWrite(m4, LOW);
 if (!bmp.begin()) {
   Serial.println(Could not find BMP180 sensor!);
   while (1)
     ;
 }
 dht.begin();
}
void loop() {
  Read temperature and humidity from DHT11
 float humidity = dht.readHumidity();
 float temperature = dht.readTemperature();
  Read pressure from BMP180
 float pressure = bmp.readPressure()  100.0;   Convert Pa to hPa
  Print temperature, humidity, pressure over serial
  Serial.print(Temperature );
  Serial.print(temperature);
  Serial.println( C);
  Serial.print(Humidity );
  Serial.print(humidity);
  Serial.println(%);
  Serial.print(Pressure );
  Serial.print(pressure);
  Serial.println( hPa);
 
 while (Serial.available()  0) {
   if (gps.encode(Serial.read())) {
     if (gps.location.isValid()) {
       Serial.print(Latitude );
       Serial.println(gps.location.lat(), 6);
       Serial.print(Longitude );
       Serial.println(gps.location.lng(), 6);
     }
   }
 }
 
 if (bt.available()  0) {
   value = bt.read();
    Serial.println(value);
   {
     switch (value) {
       case '1'
         right();
         Serial.println(Right);
         break;
       case '2'
         left();
         Serial.println(left);
         break;
 
       case '3'
         forward();
         Serial.println(forward);
         break;
 
       case '4'
         backward();
         Serial.println(backward);
         break;
 
       case '0'
         Stop();
         Serial.println(Stop);
         break;
       case '#'
         for (int i = 0; i  5; i++) {
 
 
            Serial.println(data upload);
             + String(gps.location.lat(), 6) + e + String(gps.location.lng(), 6) + f
            Serial.println(str);
            delay(2000);   Wait
           String uno = a + String(temperature) + b + String(humidity) + c + String(pressure) + d + String(gps.location.lat(), 6) + e + String(gps.location.lng(), 6) + f;
           Serial.println(uno);
           bt.println(uno);
           delay(1000);
         }
         break;
       default break;
     }
   }
 }
 
   Read GPS data
}
 
motor code for directions
void backward() {
 digitalWrite(m1, HIGH);
 digitalWrite(m2, LOW);
 digitalWrite(m3, LOW);
 digitalWrite(m4, HIGH);
}
void forward() {
 digitalWrite(m1, LOW);
 digitalWrite(m2, HIGH);
 digitalWrite(m3, HIGH);
 digitalWrite(m4, LOW);
}
void left() {
 digitalWrite(m1, HIGH);
 digitalWrite(m2, LOW);
 digitalWrite(m3, HIGH);
 digitalWrite(m4, LOW);
}
void right() {
 digitalWrite(m1, LOW);
 digitalWrite(m2, HIGH);
 digitalWrite(m3, LOW);
 digitalWrite(m4, HIGH);
}
void Stop() {
 digitalWrite(m1, LOW);
 digitalWrite(m2, LOW);
 digitalWrite(m3, LOW);
 digitalWrite(m4, LOW);
}



//NodeMCU Code

#include <SoftwareSerial.h>
SoftwareSerial bt(4, 5);  // (Rx,Tx)  only  4
#include <ESP8266WiFi.h>
#include "AdafruitIO_WiFi.h"
char ssid[] = "pro";        // Your Network SSID
char pass[] = "987654321";  // Your Network Password
#define IO_USERNAME "karthiksaisrinivas"
#define IO_KEY "aio_ZHLS98JjkHWoETa3j4rWeSpdTTQ9"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, ssid, pass);
AdafruitIO_Feed *string = io.feed("string");
AdafruitIO_Feed *temp = io.feed("temp");
AdafruitIO_Feed *hum = io.feed("humidity");
AdafruitIO_Feed *bpm = io.feed("bmp");
AdafruitIO_Feed *lat = io.feed("latitude");
AdafruitIO_Feed *lon = io.feed("longitude");
 
String temperature, humidity, pressure, latitude, longitude;
String data = "";
String val1, val2, val3, val4, val5;
int a, b, c, d, e, f;
 
void setup() {
 Serial.begin(9600);
 bt.begin(9600);  // Define baud rate for software serial communication
 
 while (!Serial)
   ;
 Serial.print("Connecting to Adafruit IO");
 io.connect();
 string->onMessage(handleMessage);
 while (io.status() < AIO_CONNECTED) {
   Serial.print(".");
   delay(500);
 }
 Serial.println();
 Serial.println(io.statusText());
}
 
void loop() {
 io.run();
 
 if (Serial.available() > 0)  //If data is available on serial port
 {
   data = Serial.readString();
 
   if (data.indexOf('a') != -1 && data.length() > 1) {
     a = data.indexOf("a");
     b = data.indexOf("b");
     a = a + 1;
     temperature = data.substring(a, b);
     Serial.println(temperature);
     delay(1000);
     b = data.indexOf("b");
     c = data.indexOf("c");
     b = b + 1;
     humidity = data.substring(b, c);
     Serial.println(humidity);
     delay(1000);
     c = data.indexOf("c");
     d = data.indexOf("d");
     c = c + 1;
     pressure = data.substring(c, d);
     Serial.println(pressure);
     delay(1000);
     
     d = data.indexOf("d");
     e = data.indexOf("e");
     d = d + 1;
     latitude = data.substring(d, e);
     // // Serial.println(latitude);
     // delay(1000);
 
     e = data.indexOf("e");
     f = data.indexOf("f");
     e = e + 1;
     longitude = data.substring(e, f);
     // d = data.indexOf("d");
     // a = data.indexOf("e");
     // d = d + 1;
     // val4 = data.substring(d, a);
     // Serial.println(val3);
     // delay(1000);
     temp->save(temperature);
     hum->save(humidity);
     bpm->save(pressure);
     lat->save(latitude);
     lon->save(longitude);
     // pumpFeed->save(1);
   }
 }
 // Serial.println(data1);
 delay(5000);
}
void handleMessage(AdafruitIO_Data *data) {
 String reading = data->toChar();
 // Serial.print("received <- ");
 Serial.println(reading);
