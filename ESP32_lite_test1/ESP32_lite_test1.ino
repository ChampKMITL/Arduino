//#include<WiFi.h>
////#include<HTTPClient.h>
//#include <HttpClient.h>
//
////url for send data
//String URL = "http://192.168.112.1/PHP-BASIC/showData.php";
//
////set wifi
//const char* ssid = "iphoneCC";
//const char* password = "champ123";
//
////var. senser
//int temp = 50;
//int hum = 61.5;
//
//
////#define LED 2
//void setup() {
//  Serial.begin(115200);
//  conWifi();
//  // Set pin mode
//  //pinMode(LED,OUTPUT);
//}
//void loop() {
////  delay(1000);
////  digitalWrite(LED,HIGH);
////  delay(300);
////  digitalWrite(LED,LOW);
//  if(WiFi.status() != WL_CONNECTED) {
//    conWifi();
//    }
//    
//    String postData = "temp=" + String(temp) + "&hum=" + String(hum);
//
//    //HTTPClient http;
//    HttpClient http;
//    http.begin(URL);
//
//    int httpCode = http.POST(postData);
//    
//    //show string in page showData.php
//    String payload = http.getString();
//    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
//
//    Serial.print("URL is : ");Serial.println(URL);
//    Serial.print("Data is : ");Serial.println(postData);
//    Serial.print("httpCode is : ");Serial.println(httpCode);
//    Serial.print("payload is : ");Serial.println(payload);
//    Serial.println("--------------------------------------------------------");
//    
//}
//
//void conWifi(){
//  WiFi.mode(WIFI_OFF);
//  delay(1000);
//  //view wifi
//  WiFi.mode(WIFI_STA);
//
//  WiFi.begin(ssid,password);
//  Serial.println("Connect WiFi....");
//
//  while (WiFi.status() != WL_CONNECTED){
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.print("Connect to : ");Serial.println(ssid);
//  Serial.print("IP Address : ");Serial.println(WiFi.localIP());
//  
//  
//
//
//}

#include <WiFi.h>
#define DHTPIN 4
#include "DHT.h"
#include <HTTPClient.h>



#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);
//url for send data
//String URL = "http://172.20.10.3/PHP-BASIC/showData.php";
//String URL = "http://192.168.100.198/PHP-BASIC/insertData.php";
String URL = "http://192.168.86.198/PHP-BASIC/insertData.php";
//set wifi
//const char* ssid = "iphoneCC";
//const char* password = "champ123";
const char* ssid = "Galaxy A30sC1E6";
const char* password = "dr@#2565";

//String URL = "http://computer_ip/project_folder/project_file.php";
//
//const char* ssid = "ENTER_WIFI_SSID"; 
//const char* password = "ENTER_WIFI_PASSWORD"; 

float temperature ;
float humidity ;

void setup() {
  Serial.begin(115200);

  dht.begin();
  
  connectWiFi();
}

void loop() {
  if(WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

//  Load_DHT22_Data();
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
//  String postData = "temperature=" + String(temperature) + "&humidity=" + String(humidity);
String postData = "temperature=" + String(temperature) + "&humidity=" + String(humidity);
  
  HTTPClient http;
  http.begin(URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  int httpCode = http.POST(postData);
  String payload = http.getString();

  Serial.print("URL : "); Serial.println(URL); 
  Serial.print("Data: "); Serial.println(postData);
  Serial.print("httpCode: "); Serial.println(httpCode);
  Serial.print("payload : "); Serial.println(payload);
  Serial.println("--------------------------------------------------");
  delay(10000);
}


void Load_DHT22_Data() {
  //-----------------------------------------------------------
//float  temperature = dht.readTemperature(); //Celsius
//float  humidity = dht.readHumidity();
  //-----------------------------------------------------------
  // Check if any reads failed.
//  if (isnan(temperature) || isnan(humidity)) {
//    Serial.println("Failed to read from DHT sensor!");
//    temperature = 0;
//    humidity = 0;
//  }
//  //-----------------------------------------------------------
//  Serial.printf("Temperature: %d °C\n", temperature);
//  Serial.printf("Humidity: %d %%\n", humidity);
}

void connectWiFi() {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  //This line hides the viewing of ESP as wifi hotspot
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
    
  Serial.print("connected to : "); Serial.println(ssid);
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
}
