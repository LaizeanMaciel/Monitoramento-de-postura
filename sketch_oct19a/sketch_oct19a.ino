#include <Wire.h>
#include <MPU6050.h>
#include <SoftwareSerial.h>

// Inicializa o acelerômetro
MPU6050 mpu;

int buzzer = 7;
const int sensorPin = 4; // Pino do sensor de inclinação

// Inicializa a comunicação Bluetooth
SoftwareSerial BTSerial(10, 11); // RX, TX para o módulo Bluetooth

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(sensorPin, INPUT); // Configura o pino do sensor de inclinação como entrada
  Serial.begin(9600);  // Inicializa a comunicação serial para o monitor
  BTSerial.begin(9600); // Inicializa o módulo Bluetooth

  // Inicia o acelerômetro
  Wire.begin(); 
  mpu.initialize();
  
  // Verifica se o acelerômetro está conectado
  if (!mpu.testConnection()) {
    Serial.println("Falha ao conectar ao MPU6050");
    while (1); // Para o programa
  }
}

void loop() {
  // Lê os valores de aceleração
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);
  
  // Calcula o ângulo de inclinação (em graus)
  float angleX = atan2(ay, az) * 180 / PI;  // Inclinação em relação ao eixo X
  float angleY = atan2(ax, az) * 180 / PI;  // Inclinação em relação ao eixo Y

  // Imprime os ângulos no monitor serial
  Serial.print("Inclinação X: "); Serial.print(angleX);
  Serial.print(" | Inclinação Y: "); Serial.println(angleY);
  
  // Verifica o estado do sensor de inclinação
  int sensorState = digitalRead(sensorPin); // Lê o estado do sensor de inclinação
  if (sensorState == HIGH) {
    Serial.println("Sensor de Inclinação: Ativado (Inclinado)");
  } else {
    Serial.println("Sensor de Inclinação: Desativado (Na posição correta)");
  }
  
  // Define limites para postura correta
  // Ajuste os limites conforme necessário
  if (angleX < -15 || angleX > 15 || angleY < -15 || angleY > 15) {
    Serial.println("Alerta: Postura Incorreta!");
    BTSerial.println("Alerta: Postura Incorreta!"); // Envia mensagem via Bluetooth
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    delay(1000);
  } else {
    Serial.println("Postura Correta");
  }
  
  delay(1000);  // Aguarda um segundo entre as leituras
}


