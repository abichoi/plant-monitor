#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ezTime.h>
//#include <arduino_secrets.h>

#include <DHT.h>
#include <DHT_U.h>
#define DHTTYPE DHT22   // DHT 22
// DHT Sensor setup
uint8_t DHTPin = 12;        // on Pin 12 of the Huzzah
DHT dht(DHTPin, DHTTYPE);   // Initialize DHT sensor. 
float Temperature;
float Humidity;

const char* ssid     = "CE-Hub";
const char* password = "()c454,w1f1";
Timezone GB;
ESP8266WebServer server(80);


void setup() {
  GB.setLocation("Europe/London");
  // open serial connection
  Serial.begin(115200);
  delay(100);

  //Timer part
  //Connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  waitForSync();
  Serial.println("UTC: " + UTC.dateTime());
  Serial.println("London time: " + GB.dateTime()); 
  
  // Moisture part
  pinMode(sensorVCC, OUTPUT); 
  digitalWrite(sensorVCC, LOW);
  
  //DHT part
  // start DHT sensor
  pinMode(DHTPin, INPUT);
  dht.begin();

  
  
}

void loop() {

  // Moisture part
    counter++;
  if(counter> 6){      // change this value to set "not powered" time. higher number bigger gap
    // power the sensor
    digitalWrite(sensorVCC, HIGH);
    delay(1000);
    // read the value from the sensor:
    moisture_val = analogRead(soilPin);   // read the resistance      
    //stop power 
    digitalWrite(sensorVCC, LOW);  
    delay(100);
    counter=0;    
  }  
  Serial.print("sensor = " );                       
  Serial.println(moisture_val);  
  
  // DHT part
  Serial.print("Temp:");
  Serial.println(dht.readTemperature()); // Gets the values of the temperature
  Serial.print("Hum:");
  Serial.println(dht.readHumidity()); // Gets the values of the humidity
  
  // Timer  
  Serial.println(GB.dateTime("H:i:s")); // UTC.dateTime("l, d-M-y H:i:s.v T")
  
  delay(100);

}
