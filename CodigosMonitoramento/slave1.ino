// Importa a biblioteca necessária para comunicação I2C
#include <Wire.h>

// Define os pinos usados pelo sensor ultrassônico
const int trigPin = 2; // Pino que envia o pulso ultrassônico (TRIG)
const int echoPin = 3; // Pino que recebe o eco do pulso (ECHO)

void setup() {
  // Inicializa este Arduino como escravo I2C com endereço 9
  Wire.begin(9);

  // Define a função que será chamada automaticamente
  // sempre que o mestre solicitar dados via I2C
  Wire.onRequest(sendDistance);

  // Define os modos dos pinos do sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Pequeno delay para manter o loop leve (não é essencial aqui)
  delay(100);
}

// Esta função é chamada automaticamente quando o Arduino mestre
// solicita dados por I2C. Aqui, medimos a distância e enviamos em 2 bytes.
void sendDistance() {
  int distance = measureDistance(); // Mede a distância com o sensor ultrassônico

  // Envia a distância dividida em dois bytes (para valores maiores que 255)
  Wire.write((distance >> 8) & 0xFF); // Envia o byte mais significativo (high byte)
  Wire.write(distance & 0xFF);        // Envia o byte menos significativo (low byte)
}

// Função que mede a distância usando o sensor ultrassônico
int measureDistance() {
  // Garante que o pino TRIG esteja em nível baixo antes de iniciar
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Envia um pulso de 10 microssegundos no pino TRIG
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Mede o tempo que o sinal leva para retornar no pino ECHO
  long duration = pulseIn(echoPin, HIGH, 30000); // Timeout de 30ms para evitar travamento

  // Se não houve retorno (sem eco), retorna 999 como valor de erro
  if (duration == 0) return 999;

  // Calcula a distância com base no tempo do pulso (em cm)
  int distance = duration * 0.034 / 2;

  // Limita a distância entre 0 e 500 cm, evitando leituras inválidas
  return constrain(distance, 0, 500);
}
