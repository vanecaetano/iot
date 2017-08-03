#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
#define TOPICO_SUBSCRIBE "engCellEnvia"
#define TOPICO_PUBLISH   "engCellRecebe"
#define ID_MQTT  "engCellId"

const char* BROKER_MQTT = "iot.eclipse.org";
int BROKER_PORT = 1883;
const char* SSIDT = "ssidrede";
const char* PASSWORD = "password";

WiFiClient espClient;
PubSubClient MQTT(espClient);

//PORTA DO LED
int portaLed = 13;

void setup() {
  Serial.begin(9600);
  pinMode(portaLed, OUTPUT);
  pinMode(portaLed, HIGH);
  Serial.print('setup');
  connectToWiFi();
  Serial.print("conectei wifi");
  startMQTT();
  Serial.print("conectei mqtt");

}

void loop() {   
  checkConnectionsAreStillEnabled();
  MQTT.loop();
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for(int i = 0; i < length; i++) {
    char c = (char)payload[i];
    message += c;
  }
  Serial.print(message);
  if (message.equals("x")) digitalWrite(portaLed, HIGH);
  if (message.equals("y")) digitalWrite(portaLed, LOW);
}
  
void connectToWiFi() {
  Serial.println("connect entrada MQTT\n");
  delay(10);
  reconectWiFi();
}
  
void startMQTT() {
  Serial.println("start MQTT\n");
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  MQTT.setCallback(mqtt_callback);
}

void reconnectMQTT() {
  Serial.println("entrada MQTT\n");
  while (!MQTT.connected()) {
  if (MQTT.connect(ID_MQTT)) MQTT.subscribe(TOPICO_SUBSCRIBE); 
  else delay(2000);
  }
}

void reconectWiFi() {
    if (WiFi.status() == WL_CONNECTED) return;
    
    WiFi.begin(SSIDT, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
    }
}
 
void checkConnectionsAreStillEnabled(void) {
  if (!MQTT.connected()) reconnectMQTT();
  reconectWiFi();
}
 

