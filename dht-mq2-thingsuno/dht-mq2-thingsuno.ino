
  const char *devAddr = "26011ACC";
  const char *nwkSKey = "2D24B9EC6CFB6C9CC7462C6133FEC1EB";
  const char *appSKey = "737424E5105B9FB7A60689E70683240C";

 

  #include <DHT.h>
  #include <TheThingsNetwork.h>
 
 
 
  #define DHTPIN 10

 
  #define DHTTYPE DHT11
  #define loraSerial Serial1
  #define debugSerial Serial
  #define freqPlan TTN_FP_EU868
 
  uint16_t humidity;
  uint16_t temparature;

 
 
  DHT dht(DHTPIN, DHTTYPE);


  TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);
 
void setup() {

  loraSerial.begin(57600);
  debugSerial.begin(9600);

  // Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 10000)
    ;

  debugSerial.println("-- PERSONALIZE");
  ttn.personalize(devAddr, nwkSKey, appSKey);

  debugSerial.println("-- STATUS");
  ttn.showStatus();
  Serial.begin(9600);
  dht.begin();

}

void loop() {

  
    Serial.println();
    debugSerial.println("-- LOOP");
    
int sensorValue = analogRead(A0);
    
    humidity = dht.readHumidity();
    temparature = dht.readTemperature();
  

    byte payload[6];
     payload[0] = highByte(temparature);
    payload[1] = lowByte(temparature);
     payload[2] = highByte(humidity);
    payload[3] = lowByte(humidity);
     payload[4] = highByte(sensorValue);
    payload[5] = lowByte(sensorValue);
 
 
   

    Serial.print("Temperature:");
    Serial.print(temparature);
    Serial.println(" *C");
  
    Serial.print("Humidity is:");
    Serial.println(humidity);

    Serial.print("Sensor Value:");
    Serial.println(sensorValue);
 
 
    

    ttn.sendBytes(payload, sizeof(payload));
  
    delay(10000);

}
