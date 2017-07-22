/**
 * Para esse projeto funcionar, não é necessária ligação de sensores. Apenas fazer o update de informações de wifi e brocker MQTT.
 */

#include <ESP8266WiFi.h> // Importa a Biblioteca ESP8266WiFi
#include <PubSubClient.h> // Importa a Biblioteca PubSubClient
 
#define TOPICO_SUBSCRIBE "{mqttenviar}"
#define TOPICO_PUBLISH   "{mqttreceber}"
#define ID_MQTT  "{id mqtt}"

const char* BROKER_MQTT = "iot.eclipse.org";
int BROKER_PORT = 1883;
const char* SSID = "{nome rede}";
const char* PASSWORD = "{senha rede}";


WiFiClient espClient;
PubSubClient MQTT(espClient);
char ledStatus = '0';
int portaLed = 2;
 

void setup() {
  startLed();
  connectToWiFi();
  startMQTT();
}

void loop() {   
  checkConnectionsAreStillEnabled();
  sendMqttStatus();
  MQTT.loop();
}
  
void connectToWiFi() {
  delay(10);
  reconectWiFi();
}
  
void startMQTT() {
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  MQTT.setCallback(mqtt_callback);
}
  
void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for(int i = 0; i < length; i++) {
    char c = (char)payload[i];
    message += c;
    }
    if (message.equals("L")) turnOnLed();
    if (message.equals("D")) turnOffLed();
}

void turnOnLed() {
  digitalWrite(portaLed, LOW);
  ledStatus = '1';
}

void turnOffLed() {
  digitalWrite(portaLed, HIGH);
  ledStatus = '0';
}

void reconnectMQTT() {
  while (!MQTT.connected()) {
  if (MQTT.connect(ID_MQTT)) MQTT.subscribe(TOPICO_SUBSCRIBE); 
  else delay(2000);
  }
}

void reconectWiFi() {
    if (WiFi.status() == WL_CONNECTED) return;
    
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
    }
}
 
void checkConnectionsAreStillEnabled(void) {
  if (!MQTT.connected()) reconnectMQTT();
  reconectWiFi();
}
 
void sendMqttStatus(void) {
  if (ledStatus == '0') MQTT.publish(TOPICO_PUBLISH, "D");
  if (ledStatus == '1') MQTT.publish(TOPICO_PUBLISH, "L");
  delay(1000);
}

void startLed(void) {
  //Led da placa tem lógica invertida: HIGH para o led apagar/LOW para o led acender
  pinMode(portaLed, OUTPUT);
  digitalWrite(portaLed, HIGH);          
}

