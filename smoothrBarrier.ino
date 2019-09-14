#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define RELAY  12                           // Port number for Relay (D6) 

const char* ssid = "SmertMoskaliam";
const char* password =  "independenceofukraine";
const char* mqttServer = "farmer.cloudmqtt.com";
const int mqttPort = 17674;
const char* mqttUser = "tdjcopeh";
const char* mqttPassword = "hdscEYdlvPVj";
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
 
  Serial.begin(115200);

  // Disable wifi AP
  WiFi.softAPdisconnect();
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  delay(100);

  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
      Serial.println("connected");  
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  client.publish("log/barrier", "esp is connected...");
  client.subscribe("command/barrier");
}
 
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  // if receive command
  // Set relay for 2 second
  // digitalWrite(RELAY, HIGH);   // Turn the LED on (Note that LOW is the voltage level
  // delay(2000);
  // digitalWrite(RELAY, LOW);  // Turn the LED off by making the voltage HIGH


  client.publish("answer/barrier", "Ok");
  Serial.println();
  Serial.println("-----------------------");
}
 
void loop() {
  client.loop();
}
