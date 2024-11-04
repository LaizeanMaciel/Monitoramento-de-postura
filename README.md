# SISTEMA DE MONITORAMENTO DE POSTURA COM ARDUINO

### Descrição 💡
Este projeto tem como objetivo desenvolver um sistema de monitoramento de postura utilizando um sensor de inclinação. O sistema alerta o usuário quando a postura está inadequada, promovendo hábitos de saúde e ergonomia.

### Tabela de Conteúdos 📋
- [Descrição](#descrição)
- [Componentes Utilizados](#componentes-utilizados)
- [Esquema de Circuitos](#esquema-de-circuitos)
- [Código Fonte](#codigo-fonte)
- [Resultados](#resultados)
- [Possíveis Melhorias](#possiveis-melhorias)
- [Licensa](#licensa)
- [Conclusão](#conclusao)

### Componentes Utilizados 📦
- Arduino Uno
- Protoboard
- Jumpers
- Acelerometro
- Sensor de Inclinação
- Modúlo Bluetooth
- LED
- Buzzez

### Esquema de Circuitos ⚡

**Arduino:**

- Pino GND conectado ao GND do sensor e do buzzer.
- Pino 9 conectado ao buzzer.
- Pino 10 conectado ao LED.

**Sensor de Inclinação:**

Pino VCC conectado ao 5V do Arduino.
Pino GND conectado ao GND do Arduino.
Pino de sinal conectado a um pino analógico do Arduino.

**Acelerômetro:**
- Pino VCC conectado ao 5V do Arduino.
- Pino GND conectado ao GND do Arduino.
- Pino de sinal conectado a um pino analógico (ex.: A0) do Arduino.

**Bluetooth:**
- Pino TX do Bluetooth conectado ao pino RX do Arduino.
- Pino RX do Bluetooth conectado ao pino TX do Arduino.
- Pino GND conectado ao GND do Arduino.

**Buzzer:**
- Pino positivo do buzzer conectado ao pino 9 do Arduino.
- Pino negativo do buzzer conectado ao GND do Arduino.

**LED:**
- Pino positivo do LED conectado ao pino 10 do Arduino (com um resistor, se necessário).
- Pino negativo do LED conectado ao GND do Arduino.

### Imagens:

<div style="display: flex; flex-wrap: wrap; gap: 10px;">

  <img src="images/01.jpg" alt="Imagem 1" width="200"/>
  <img src="images/02.jpg" alt="Imagem 2" width="200"/>
  <img src="images/03.jpg" alt="Imagem 3" width="200"/>
  <img src="images/04.jpg" alt="Imagem 4" width="200"/>

</div>

### Código Fonte 💻
```cpp

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

```

### Resultados ✔️
Após configurar o sistema, o buzzer e o LED acionam quando uma postura incorreta é detectada. Este sistema é ideal para ajudar na correção de postura durante o trabalho ou estudo.

### Possíveis Melhorias 🔧
Implementar conectividade Bluetooth para monitoramento remoto via app.
Adicionar uma interface de display LCD para indicar a inclinação atual.

### Licensa 📜
Este projeto está licenciado sob a licença MIT - consulte o arquivo LICENSE para mais detalhes.

### Conclusão 📝
O projeto de monitoramento de postura foi desenvolvido com o objetivo de auxiliar os usuários a manter uma boa postura durante atividades diárias, utilizando um sistema de sensores integrados. 

Os principais resultados obtidos incluem:

- **Detecção Eficiente da Postura**: O uso do acelerômetro permitiu monitorar a inclinação do corpo em tempo real, enviando dados precisos para o Arduino.
- **Alertas Sonoros e Visuais**: O sistema acionou o buzzer e o LED para alertar os usuários sobre posturas inadequadas, promovendo maior conscientização sobre a importância de uma boa postura.
- **Comunicação Sem Fio**: A integração do módulo Bluetooth possibilitou a comunicação com dispositivos móveis, facilitando o acesso às informações de monitoramento.


