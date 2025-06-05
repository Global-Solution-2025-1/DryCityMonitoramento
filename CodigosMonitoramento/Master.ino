// Bibliotecas para comunicação I2C e controle do display LCD
#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>

// Inicializa o display LCD usando o endereço I2C 0x27 (valor 0 representa esse endereço)
Adafruit_LiquidCrystal lcd(0);

// Define os pinos conectados aos componentes
const int redLED = 12;      // LED vermelho indica nível crítico de água
const int yellowLED = 11;   // LED amarelo indica nível de atenção
const int buzzer = 9;       // Buzzer emite som em caso de alerta
const int buttonPin = 6;    // Botão para alternar entre sensores (exceto em modo crítico)

// Variáveis para armazenar a distância medida por cada sensor (em cm)
int sensor1Distance = 0;
int sensor2Distance = 0;

// Controla qual sensor está sendo exibido no display (1 ou 2)
int selectedSensor = 1;

// Flag que indica se o sistema está em estado crítico (prioriza sensores críticos no display)
bool criticalOverride = false;

// Variáveis para controle do botão (evita múltiplos acionamentos indevidos)
bool lastButtonState = LOW;
bool currentButtonState = LOW;

void setup() {
  Wire.begin();          // Inicializa a comunicação I2C como mestre
  lcd.begin(16, 2);      // Inicia o LCD com 2 linhas de 16 caracteres
  lcd.setBacklight(HIGH); // Liga a luz de fundo do LCD

  // Define os pinos como saída ou entrada
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(buttonPin, INPUT);

  Serial.begin(9600); // (Opcional) Inicializa comunicação serial para debug
}

void loop() {
  readSlaves();       // Lê a distância dos sensores escravos via I2C
  handleDisplay();    // Atualiza o display e LEDs/buzzer conforme situação
  delay(500);         // Pequeno atraso entre as atualizações (500ms)
}

// Função que solicita e armazena a distância dos dois sensores
void readSlaves() {
  sensor1Distance = requestDistance(8);  // Endereço I2C do sensor 1
  sensor2Distance = requestDistance(9);  // Endereço I2C do sensor 2
}

// Solicita a distância de um sensor escravo pelo endereço I2C
int requestDistance(byte address) {
  Wire.requestFrom(address, 2); // Solicita 2 bytes do sensor
  if (Wire.available() >= 2) {
    int highByte = Wire.read();         // Lê byte mais significativo
    int lowByte = Wire.read();          // Lê byte menos significativo
    int distance = (highByte << 8) | lowByte; // Junta os dois bytes em um valor de 16 bits
    return distance;
  }
  return -1; // Retorna -1 se não conseguiu ler
}

// Controla o display e qual sensor deve ser mostrado com base nas leituras
void handleDisplay() {
  int d1 = sensor1Distance;
  int d2 = sensor2Distance;

  // Define se algum dos sensores está em nível crítico (< 200cm)
  bool isCritical1 = (d1 >= 0 && d1 < 200);
  bool isCritical2 = (d2 >= 0 && d2 < 200);

  // Se qualquer sensor estiver em estado crítico, entra em modo de prioridade
  if (isCritical1 || isCritical2) {
    criticalOverride = true;
    selectedSensor = isCritical1 ? 1 : 2; // Mostra o sensor que está em estado crítico
  } else {
    // Caso não esteja em estado crítico, permite alternar entre sensores com botão
    currentButtonState = digitalRead(buttonPin);
    if (currentButtonState == HIGH && lastButtonState == LOW) {
      selectedSensor = (selectedSensor == 1) ? 2 : 1; // Alterna entre 1 e 2
      criticalOverride = false; // Sai do modo crítico
      delay(10); // Pequeno debounce para evitar leituras múltiplas do botão
    }
    lastButtonState = currentButtonState;
  }

  // Define qual valor de distância será mostrado no display
  int distanceToShow = (selectedSensor == 1) ? d1 : d2;

  // Atualiza o display LCD com o sensor e nível de água
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sensor ");
  lcd.print(selectedSensor);

  lcd.setCursor(0, 1);
  if (distanceToShow >= 0) {
    lcd.print("Level: ");
    lcd.print(distanceToShow);
    lcd.print("cm");
  } else {
    lcd.print("Level: Err"); // Erro na leitura
  }

  updateAlerts(distanceToShow); // Atualiza os alertas (LEDs e buzzer)
}

// Atualiza os LEDs e buzzer com base no nível de água atual
void updateAlerts(int distance) {
  // Desliga todos os alertas inicialmente
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(buzzer, LOW);

  if (distance < 0) return; // Se a distância for inválida, não aciona nada

  // Se o nível de água for crítico (< 200cm)
  if (distance < 200) {
    digitalWrite(redLED, HIGH);    // Liga o LED vermelho
    tone(buzzer, 1000, 200);       // Emite som no buzzer com 1kHz por 200ms
  }
  // Se o nível for de atenção (entre 200cm e 250cm)
  else if (distance < 250) {
    digitalWrite(yellowLED, HIGH); // Liga o LED amarelo
  }
}
