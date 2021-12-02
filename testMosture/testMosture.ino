uint8_t soilPin = 0;  
int moisture_val;

int sensorVCC = 13;
int counter = 0;

void setup() {
  Serial.begin(115200);     //open serial port
  pinMode(sensorVCC, OUTPUT); 
  digitalWrite(sensorVCC, LOW);
}

void loop() {
  counter++;
  if(counter> 6){      
    // power the sensor
    digitalWrite(sensorVCC, HIGH);
    delay(1000);
    // read the value from the sensor:
    // read the resistance  
    moisture_val = analogRead(soilPin);       
    //stop power 
    digitalWrite(sensorVCC, LOW);  
    delay(100);
    counter=0;    
  }  
  //wait
  Serial.print("sensor = " );                       
  Serial.println(moisture_val);     
  delay(100);
}
