/**
 * Para esse projeto funcionar, não é necessária ligação de sensores. Apenas fazer o update de informações de wifi e brocker MQTT.
 */

#include <ESP8266WiFi.h> // Importa a Biblioteca ESP8266WiFi
#include <PubSubClient.h> // Importa a Biblioteca PubSubClient
 
#define TOPICO_SUBSCRIBE "MQTTVanessaCEnvia"
#define TOPICO_PUBLISH   "MQTTVanessaCRecebe"
#define ID_MQTT  "vanessacaetano"
#define portSpeak D2

const char* BROKER_MQTT = "iot.eclipse.org";
int BROKER_PORT = 1883;
const char* SSID = "ILG_MOBILE";
const char* PASSWORD = "incorrect";

//melodia do MARIO THEME
int melodia[] = {660,660,660,510,660,770,380,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,500,500,500,580,660,500,430,380,500,500,500,500,580,660,870,760,500,500,500,500,580,660,500,430,380,660,660,660,510,660,770,380};
//duraçao de cada nota
int duracaodasnotas[] = {100,100,100,100,100,100,100,100,100,100,100,80,100,100,100,80,50,100,80,50,80,80,80,80,100,100,100,100,80,100,100,100,80,50,100,80,50,80,80,80,80,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,150,200,80,80,80,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,150,200,80,80,80,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,100,100,100,60,80,60,80,80,80,80,80,80,60,80,60,80,80,80,80,80,60,80,60,80,80,80,80,80,80,100,100,100,100,100,100,100};



WiFiClient espClient;
PubSubClient MQTT(espClient);
char ledStatus = '0';
int portaLed = 2;
 

void setup() {
  pinMode(portSpeak,OUTPUT);
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
    if (message.equals("L")) {
      turnOnLed();
      tocaMusica();
      }
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

void tocaMusica() {
//for para tocar as 156 notas começando no 0 ate 156 ++ incrementado
        for (int nota = 0; nota < 156; nota++) {

              int duracaodanota = duracaodasnotas[nota];
              tone(portSpeak, melodia[nota],duracaodanota);
  //pausa depois das notas
              int pausadepoisdasnotas[] ={150,300,300,100,300,550,575,450,400,500,300,330,150,300,200,200,150,300,150,350,300,150,150,500,450,400,500,300,330,150,300,200,200,150,300,150,350,300,150,150,500,300,100,150,150,300,300,150,150,300,150,100,220,300,100,150,150,300,300,300,150,300,300,300,100,150,150,300,300,150,150,300,150,100,420,450,420,360,300,300,150,300,300,100,150,150,300,300,150,150,300,150,100,220,300,100,150,150,300,300,300,150,300,300,300,100,150,150,300,300,150,150,300,150,100,420,450,420,360,300,300,150,300,150,300,350,150,350,150,300,150,600,150,300,350,150,150,550,325,600,150,300,350,150,350,150,300,150,600,150,300,300,100,300,550,575};
              delay(pausadepoisdasnotas[nota]);}

              noTone(portSpeak);
    }

