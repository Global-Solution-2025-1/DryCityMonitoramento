// Biblioteca para comunicação I2C
#include <Wire.h>

// Define os pinos utilizados pelo sensor ultrassônico
const int trigPin = 2; // Pino de disparo (envia pulso ultrassônico)
const int echoPin = 3; // Pino de eco (recebe o sinal de retorno)

void setup() {
  Wire.begin(8); // Define o endereço I2C deste Arduino como 8
  Wire.onRequest(sendDistance); // Define a função que será chamada quando o mestre solicitar dados

  // Define os modos dos pinos do sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  delay(100); // Pequena pausa (não é essencial aqui, apenas mantém o loop rodando)
}

// Função chamada automaticamente quando o mestre faz uma solicitação via I2C
void sendDistance() {
  int distance = measureDistance(); // Mede a distância com o sensor
  Wire.write((distance >> 8) & 0xFF); // Envia o byte mais significativo (high byte)
  Wire.write(distance & 0xFF);        // Envia o byte menos significativo (low byte)
}

// Função que mede a distância com o sensor ultrassônico HC-SR04
int measureDistance() {
  // Garante que o pino TRIG esteja baixo antes de iniciar
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Envia um pulso de 10 microssegundos no TRIG
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Mede quanto tempo leva para o pulso voltar (em microssegundos)
  long duration = pulseIn(echoPin, HIGH, 30000); // Timeout de 30ms (30000us) para evitar travamentos

  if (duration == 0) return 999; // Se não receber eco, retorna 999 como erro

  // Converte o tempo de ida e volta em centímetros
  int distance = duration * 0.034 / 2;

  // Limita a distância entre 0 e 500 cm, evitando valores absurdos
  return constrain(distance, 0, 500);
}
