#include <ESP8266WiFi.h>

const char* ssid ="WIFI_Name";
const char* password ="WIFI_PASSWORD";
const char* host ="iot.io";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(100);

  //connect to WIFI
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid,password);

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(5000);

  Serial.println("-------------------------------");
  Serial.print("Connecting to ");
  Serial.println(host);

  //Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if(!client.connect(host, httpPort)){
    Serial.println("connection failed");
    return;
  }
  //Create a URL for the request
  String url = "/data/index.html";
  Serial.print("Requesting URL: ");
  Serial.println(host + url);

  //send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  delay(500);

  //read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  Serial.println("closing connection");
}
