#include <ESP8266WiFi.h> 

#define SSID_REDE     "{nome rede}"
#define SENHA_REDE    "{senha rede}"
#define INTERVALO_ENVIO_THINGSPEAK  30000
 
char EnderecoAPIThingSpeak[] = "api.thingspeak.com";
String ChaveEscritaThingSpeak = "{id}";
long lastConnectionTime; 
WiFiClient client;
 

void EnviaInformacoesThingspeak(String StringDados) {
  if (client.connect(EnderecoAPIThingSpeak, 80)) {
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+ChaveEscritaThingSpeak+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(StringDados.length());
    client.print("\n\n");
    client.print(StringDados);
    lastConnectionTime = millis();
    Serial.println("- Informações enviadas ao ThingSpeak!");
    }   
}

void FazConexaoWiFi(void) {
  client.stop();
  Serial.println("Conectando-se à rede WiFi...");
  Serial.println();  
  delay(1000);
  WiFi.begin(SSID_REDE, SENHA_REDE);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
    
  Serial.println("");
  Serial.println("WiFi connectado com sucesso!");  
  Serial.println("IP obtido: ");
  Serial.println(WiFi.localIP());
  delay(1000);
}
 

float FazLeituraUmidade(void) {
  int umidade;
  float percent;
  
  umidade = analogRead(A0);
  Serial.print("[Leitura ADC] ");
  Serial.println(umidade);
  delay(5000);
     
  percent = map(umidade, 1000, 350, 0, 100);
  Serial.println("Umidade em:");
  Serial.print(percent);
  Serial.println(" %");
  return percent;
}

void setup() {  
  Serial.begin(9600);
  lastConnectionTime = 0; 
  FazConexaoWiFi();
}
 
void loop() {
  float UmidadePercentualLida;
  int UmidadePercentualTruncada;
  char FieldUmidade[11];
  
  if (client.connected()) {
    client.stop();
    Serial.println("Desconectado do ThingSpeak");
    Serial.println();
   }
   
   UmidadePercentualLida = FazLeituraUmidade();
   UmidadePercentualTruncada = (int)UmidadePercentualLida;
     
   if(!client.connected() && (millis() - lastConnectionTime > INTERVALO_ENVIO_THINGSPEAK)) {
    sprintf(FieldUmidade,"field1=%d",UmidadePercentualTruncada);
    EnviaInformacoesThingspeak(FieldUmidade);
   }
 
   delay(1000);
}
