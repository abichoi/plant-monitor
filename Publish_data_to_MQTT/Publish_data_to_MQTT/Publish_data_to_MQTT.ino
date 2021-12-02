#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Wifi and MQTT
#include "arduino_secrets.h" 

const char* ssid     = SECRET_SSID;
const char* password = SECRET_PASS;
const char* mqttuser = SECRET_MQTTUSER;
const char* mqttpass = SECRET_MQTTPASS;
const char* mqtt_server = "mqtt.cetools.org";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  // Initialize the BUILTIN_LED pin as an output 
  pinMode(BUILTIN_LED, OUTPUT);     
  // Turn LED off
  digitalWrite(BUILTIN_LED, HIGH);  

  // open serial connection
  Serial.begin(115200);
  // delay for the serial connection to opern
  delay(100);

  // Initiate the connecting to wifi routine
  startWifi();

  // Once connected to wifi establish connection to mqtt broker
  client.setServer(mqtt_server, 1884);
  
  // Callback listens for instructions to change the state of the LED 
  // Intialise callback function
  client.setCallback(callback);

}

void loop() {
  delay(5000);
  sendMQTT();
}


// Set-up the connection to the wifi using the user and passwords defined in the secrets file
// It then prints the connection status to the serial monitor

void startWifi(){
  //Connect to WiFi 
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // check to see if connected or not
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// check if the arduino is connected to MQTT broker before it send a msg
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {    // while not (!) connected....
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqttuser, mqttpass)) {
      Serial.println("connected");
      // ... and subscribe to messages on broker
      client.subscribe("student/CASA0014/plant/ucjtdjw/inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

// publish an incremented  to a MQTT topic (student/CASA0014/plant/ucfnsmc) once a connection is established with the broker
void sendMQTT() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  ++value;
  snprintf (msg, 50, "hello world #%ld", value);
  Serial.print("Publish message: ");
  Serial.println(msg);
  client.publish("student/CASA0014/plant/ucfnsmc", msg);

}

// Callback function is called when an incoming message is received from the MQTT broker 
// If the first character of the message has "1", turn an LED on. Otherwise, turn off
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

 //LED is active low
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off
  }

}
