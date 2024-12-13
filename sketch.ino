#include <WiFi.h>
#include <HTTPClient.h>

#define led_verde 2 // Pino utilizado para controle do led verde
#define led_vermelho 40 // Pino utilizado para controle do led vermelho
#define led_amarelo 9 // Pino utilizado para controle do led amarelo

const int buttonPin = 18;  // Número do pino do botão
int buttonState = 0;  // Variável que lê o estado do botão

const int ldrPin = 4;  // Número do pino do LDR
int threshold=600;

void setup() {

  // Configuração inicial dos pinos para controle dos leds como OUTPUTs (saídas) do ESP32
  pinMode(led_amarelo,OUTPUT);
  pinMode(led_verde,OUTPUT);
  pinMode(led_vermelho,OUTPUT);

  // Inicialização das entradas
  pinMode(buttonPin, INPUT); // Inicializa o botão como um input

  digitalWrite(led_verde, LOW); // Deixa o led verde desligado
  digitalWrite(led_vermelho, LOW); // Deixa o led vermelho desligado
  digitalWrite(led_amarelo, LOW); // Deixa o led amarelo desligado

  Serial.begin(9600); // Configuração para debug por interface serial entre ESP e computador com baud rate de 9600

  WiFi.begin("Wokwi-GUEST", ""); // Conexão à rede WiFi aberta com SSID Wokwi-GUEST

  while (WiFi.status() != WL_CONNECT_FAILED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("Conectado ao WiFi com sucesso!"); // Considerando que saiu do loop acima, o ESP32 agora está conectado ao WiFi (outra opção é colocar este comando dentro do if abaixo)

  sinalFechado = digitalWrite(led_vermelho);

  // Verifica estado do botão
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    Serial.println("Botão pressionado!");
  } else {
    Serial.println("Botão não pressionado!");
  }

  if(WiFi.status() == WL_CONNECTED){ // Se o ESP32 estiver conectado à Internet
    HTTPClient http;

    String serverPath = "http://www.google.com.br/"; // Endpoint da requisição HTTP

    http.begin(serverPath.c_str());

    int httpResponseCode = http.GET(); // Código do Resultado da Requisição HTTP

  if (httpResponseCode>0) {
      Serial.print("Código de resposta HTTP: ");
      Serial.println(httpResponseCode); 
      String payload = http.getString();
      Serial.println(payload);
      }
  else {
      Serial.print("Erro de número: ");
      Serial.println(httpResponseCode);
      }
      http.end();
    }

  else {
    Serial.println("WiFi desconectado");
  }

}

void loop() {
  int ldrstatus = analogRead(ldrPin); // Define a variável que lê o estado do LDR

  if(ldrstatus<=threshold){
    Serial.print("Está escuro, ligue o led"); // Define uma ação para caso esteja escuro
    Serial.println(ldrstatus);
  }
  else{
    Serial.print("Está claro, desligue o led"); // Define uma ação para caso esteja claro
    Serial.println(ldrstatus);
  }

  // Caso esteja escuro, liga o modo noturno piscando o led amarelo
  if(ldrstatus<=threshold){
    digitalWrite(led_amarelo, HIGH);
    delay(1000);
    digitalWrite(led_amarelo, LOW);
}
  // Se não estiver escuro, continua o funcionamento normal do semáforo
  else{
  digitalWrite(led_vermelho, HIGH);
  digitalWrite(led_amarelo, LOW); // Sinal fechado
  digitalWrite(led_verde, LOW);
  
  delay(5000);
  
  digitalWrite(led_vermelho, LOW);
  digitalWrite(led_amarelo, LOW); // Sinal Aberto
  digitalWrite(led_verde, HIGH);
  
  delay(3000);
  
  digitalWrite(led_vermelho, LOW);
  digitalWrite(led_amarelo, HIGH); // Sinal de atenção
  digitalWrite(led_verde, LOW);
  
  delay(2000);
  }

  // Caso esteja claro, o sinal esteja fechado e o botão seja apertado, o semáforo abrirá, acendendo o led verde
  if(ldrstatus>threshold && sinalFechado = HIGH && buttonState == HIGH ){
  delay(1000);
  
  digitalWrite(led_vermelho, LOW);
  digitalWrite(led_amarelo, LOW);
  digitalWrite(led_verde, HIGH);
  }

  if(ldrstatus>threshold && sinalFechado = HIGH && buttonState == HIGH){
    http.begin(serverPath.c_str()); // Manda uma requisição HTTP
  }
}