# plant-monitor
A monitor that uses Feather Huzzah ESP8266 Wifi and other components to monitor the mositure of the soil.

## Schematic of the plant monitor  
<!-- ![Plant_Monitor_Schematic](https://github.com/abichoi/plant-monitor/blob/main/images/circuit_diagram.png|height=50%) -->
<img src="https://github.com/abichoi/plant-monitor/blob/main/images/circuit_diagram.png" width="80%"/>

## Photos of the plant  
<!-- ![PlantPhoto_1](https://github.com/abichoi/plant-monitor/blob/main/images/plant_photo_1.jpg?raw=true) -->
<!-- ![PlantPhoto_2](https://github.com/abichoi/plant-monitor/blob/main/images/plant_photo_2.jpg?raw=true) -->

<table><tr>
<td><img src="https://github.com/abichoi/plant-monitor/blob/main/images/plant_photo_1.jpg" width="50%"/></td>
<td><img src="https://github.com/abichoi/plant-monitor/blob/main/images/plant_photo_2.jpg" width="50%"/><td>
</tr></table>

## Details of the plant  
**Link**: https://forest.london/collections/indirect-light/products/syngonium-podophyllum  
          https://www.gardeningknowhow.com/houseplants/arrowhead-plant/arrowhead-plant-care-arrowhead-plant-or-syngonium-podophyllum.htm  
**Name**: Syngonium Podophyllum  
**Leaves**: soft-green and white foliage  
**Lighting needs**: Bright but indirect -- Direct sunlight with cause the plant to bleach/ burn  
**Watering needs**: Frequent  
    **Warmer months**: Water when the top of soil is dry  
    **Cooler months**: Water when at least half the pot of the soil has dried  
    **Every week**: Mist the leaves (Some said daily, from my experience daily misting is needed)  
**Humidity needs**: High  
    **Caution**: Keep it away from air dryers -- e.g. heaters  
**Temperature needs**: 16-25 C  
**Fertilise needs**: Monthly with a balnced fertilizer  
**Repot** : Every spring due to the spreading roots, gloves are adviced  
  
## Codes   
- **testing/feather_testing**  
  - A code that blinks the LED on Adafruit Huzzah ESP8266 to check if it is working  
- **connecting_to_WIFI**  
  - Workshop step 4    
  - Connect the ESP8266 to the CE-hub wifi and print out the state of the connection on the Serial monitor  
- **Getting_the_time**  
  - Workshop step 5  
  - Grab the time from the NTP server -- ezTime library and print it out on the Serial monitor  
- **Publish_data_to_server**  
  - Workshop step 6  
  - Connect to the WIFI and MQTT  
  - Turn the LED on the ESP8266 on and off by publishing a message to the MQTT  
  - If the first character of the msg is 1, then the LED turns on, otherwise turn off  
- **testMosture**  
  - Workshop step 8  
  - Test if the circuit works or not  
  - The output value represents the mositure of the soil, which changes according to the resistance between the nails  
  - The moisture value can be shown on Serial monitor and plotter  
- **testDHT22**  
  -  Workshop step 8  
  -  Test if the DHT22 sensor works or not  
  -  It will output the temperature and the humidity on the serial monitor  
- **Sensing_Soil_and_environment**  
  - Workshop step 8 extension  
  - Display the soil moisture + environment temperature and humidity + time  
- **actual_code**  
     - Workshop step 9   
     - A code that publishes the temperature and humidity of the environment and the moisture of the soil to the MQTT server  
