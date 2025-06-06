
# 💧 DRYCity — Sistema de Monitoramento Inteligente Contra Enchentes

Este projeto foi desenvolvido com o objetivo de oferecer uma **solução autônoma, de baixo custo e replicável** para o monitoramento de áreas de risco de enchentes. Utilizando comunicação I2C entre microcontroladores, sensores ultrassônicos e interface visual com LEDs, buzzer e LCD, o sistema detecta níveis críticos de água em tempo real, emitindo alertas imediatos e facilitando a resposta rápida em comunidades vulneráveis.

Ideal para regiões sem acesso à internet, zonas ribeirinhas, áreas urbanas de risco ou fins educacionais.

---

## 📦 Funcionalidades Principais

- Leitura de **nível de água** em tempo real com sensores ultrassônicos.
- Exibição no **display LCD I2C 16x2** com alternância manual e priorização automática de alertas críticos.
- Sistema de **alerta visual** (LEDs) e **sonoro** (buzzer).
- **Comunicação I2C** entre 1 Arduino mestre e 2 escravos.
- Operação totalmente **offline**, sem necessidade de conexão à internet.

---

## ✅ Dependências

Antes de compilar e carregar o projeto, certifique-se de instalar as seguintes bibliotecas na IDE do Arduino:

- `Wire.h`
- `LiquidCrystal_I2C.h`

Essas bibliotecas estão disponíveis no Gerenciador de Bibliotecas da IDE Arduino.

---

## 🧰 Componentes Utilizados

| Componente                    | Quantidade             |
|------------------------------|------------------------|
| Arduino Uno/Nano             | 3 (1 mestre + 2 escravos) |
| Sensor Ultrassônico HC-SR04  | 2                      |
| Display LCD I2C 16x2         | 1                      |
| LEDs (vermelho, amarelo, verde) | 3                   |
| Buzzer Piezo                 | 1                      |
| Botão Push-Button            | 1                      |
| Jumpers, resistores, protoboard | Diversos            |

---

## 💻 Montagem e Execução

### Passo a Passo:

1. Instale a [IDE do Arduino](https://www.arduino.cc/en/software).
2. Vá em **Sketch > Include Library > Manage Libraries...** e instale as bibliotecas listadas acima.
3. Conecte os dispositivos conforme o mapeamento a seguir:

#### 📘 Arduino Mestre

```
LED Verde         → D13  
LED Amarelo       → D12  
LED Vermelho      → D11  
Buzzer            → D7  
Botão             → D2  
LCD I2C           → SDA/SCL (A4/A5 no Uno)
```

#### 📗 Arduinos Escravos

```
HC-SR04 Trigger   → D9  
HC-SR04 Echo      → D8  
I2C               → SDA/SCL (A4/A5 no Uno)
```

> Cada escravo deve ter um **endereço I2C único** (ex: 8 e 9). Use `Wire.begin(address)` no `setup()` de cada escravo.

4. Crie 3 projetos separados no Tinkercad (ou use o Wokwi para simulação I2C completa).
5. Carregue o código correspondente em cada Arduino.
6. Execute a simulação ou o sistema físico.

---

## 🧑‍💻 Execução do Sistema

Após a inicialização, o display LCD mostra as leituras de nível de água de **um sensor por vez**, com alternância manual através do botão.

### Estados e Ações:

| Estado  | Ação no Sistema                      |
|---------|--------------------------------------|
| Ideal   | LED Verde aceso                      |
| Alerta  | LED Amarelo aceso                    |
| Crítico | LED Vermelho + Buzzer acionado       |

- Em caso de **nível crítico**, a exibição é automaticamente priorizada no LCD.
- O botão permite alternar entre os sensores manualmente.

---

## 🔗 Simulação Online

- ▶️ **Projeto no Tinkercad:**  
  [Acessar Simulação](https://www.tinkercad.com/things/axvVWG0wVHf/editel?returnTo=%2Fdashboard&sharecode=XTL2aAalOVtCPEbipjSoDDmAf6q0bY2dyR9jWh73FVo)

- 📹 **Vídeo Demonstrativo no YouTube:**  
  *(inserir link quando disponível)*

### 🧪 Como Simular no Tinkercad:

- Crie 3 projetos separados (1 mestre, 2 escravos).
- Configure os endereços I2C dos escravos com `Wire.begin(address)`.
- Use o "Serial Monitor" para observar a comunicação entre Arduinos.
- **Observação:** o suporte a múltiplos Arduinos em um único projeto é limitado no Tinkercad. Para simulação completa, considere usar o [Wokwi](https://wokwi.com/).

---

## 👥 Equipe de Desenvolvimento

- **Jéssica Tavares** – RM566220  
- **Luara Soares** – RM561266  
- **Miguel Amaro** – RM566200  

---

## 📂 Sobre o Projeto

Este projeto é parte de uma iniciativa educacional voltada ao desenvolvimento de **soluções tecnológicas com impacto social real**, especialmente voltadas para cidades e comunidades vulneráveis a enchentes.

A ideia é capacitar comunidades a montar seu próprio sistema de monitoramento de forma simples e eficaz, com foco em:

- Monitoramento local descentralizado  
- Ação imediata em caso de risco  
- Futuro suporte a plataformas de apoio e integração com redes de doadores
