// import generic libraries
#include <WiFi.h>
#include <HTTPClient.h>
#include <string>

// import libraries for temp.sensor
#include <OneWire.h> 
#include <DallasTemperature.h>

// declare data pins for respective sensors
#define ONE_WIRE_BUS 22
int sensorPin = 36;

// Wifi Initiation
const char * ssid = "<SSID>";
const char * password = "<Password>";
WiFiClientSecure client;

// declare variables
int sendInterval=10000; //time between vitals ingestion

// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
    Serial.begin(115200);
    delay(10);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    Serial.println("Started");
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    } 

    Serial.println("Ready to go");
}

void loop() 
{

  sensors.requestTemperatures(); 
  Serial.print(sensors.getTempCByIndex(0)); 
  Serial.print(" *C ");
  
  delay(3000);
  
  //float pulse;
  float heartRate;
  int sum = 0;
  int hbConstant = 24; // int hbConstant = 42;
  for (int i = 0; i < 20; i++)
//    portDISABLE_INTERRUPTS();
    sum += analogRead(sensorPin);
//    portENABLE_INTERRUPTS();
  //pulse = sum / 20.00;
  heartRate = sum / (20.00*hbConstant);
  
  String bufT = String(sensors.getTempCByIndex(0));
  //String bufHR = String(heartRate);
  String bufHR = String(heartRate, DEC);

  Serial.print(bufHR);

  sendData(bufT,bufHR);
 
  delay(sendInterval);
}

void sendData(String bufT, String bufHR) {
    HTTPClient http;
    
    //Your Domain name with URL path or IP address with path
    //const char* serverName = "http://192.168.1.9:5000/add_vital";
    http.begin("http://192.168.1.5:5000/add_vital");
    http.addHeader("Content-Type", "application/json");
    // JSON data to send with HTTP POST, you need to hardcode patientID for each unique sensor here
    String httpRequestData = "{\"patientID\":\"" + String(2) + "\",\"temp\":\"" + bufT + "\",\"heartbeat\":\"" + bufHR + "\"}";
    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
    

    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
}

 
  
