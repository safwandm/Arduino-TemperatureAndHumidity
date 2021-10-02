#define BLYNK_PRINT Serial

#include <DHT.h>
#include <ESP8266WiFi.h> //file untuk modul wifi
#include <BlynkSimpleEsp8266.h> //file untuk blynk

char auth[] = "zMlosSJ-Kq5MgKkD5smdE6Z_OzgHBxBI"; // token yang dikirim dari blynk ke email masing masing
char ssid[] = "AndroidAP3F5F";
char pass[] = "safwan030804";

#define DHTPIN 14
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();


  if (isnan(h) || isnan(t)) { //mengecek apabila suhu dan kelembapan tidak ada value
    Serial.println("Failed to read temperature and humidity");
    return;
  }

  Blynk.virtualWrite(V1, t); // setting virtual suhu di blynk
  Blynk.virtualWrite(V2, h);//setting virtual kelembapan di blynk

}


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Blynk.begin(auth, pass, ssid);
  dht.begin();// sensut mulai membaca humidity dan temperature
  timer.setInterval(1000, sendSensor); // waktu untuk mengirimkan data setiap 1 detik

}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();

}
