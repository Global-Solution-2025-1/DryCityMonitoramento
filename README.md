💧 Dry City — Sistema de Monitoramento Inteligente Contra Enchentes
🌊 Problema Inicial
As enchentes são um dos maiores desafios ambientais e sociais no Brasil. Entre 1991 e 2022, foram mais de 21 mil inundações atingindo 110 milhões de brasileiros. Em 2023, 3,3 milhões de pessoas foram impactadas. Em 2024, o Rio Grande do Sul sofreu uma das piores tragédias de sua história, com mais de 170 mortos e R$ 20 bilhões em prejuízos econômicos.

Causas principais:

Falta de políticas públicas eficazes

Urbanização desordenada

Mudanças climáticas

Falta de tecnologia aplicada à prevenção

💡 Visão Geral da Solução
A Dry City propõe uma solução de baixo custo, autônoma e replicável para monitoramento local de áreas de risco de enchentes. O sistema é composto por:

📟 1 Arduino Mestre com LCD, LEDs, buzzer e botão de navegação

🌊 2 Arduinos Escravos com sensores ultrassônicos

🔗 Comunicação via barramento I2C

🔧 Funcionalidades:
Leitura de nível de água em tempo real

Priorização automática de alertas críticos

Sistema visual (LEDs) e sonoro (buzzer)

Alternância entre sensores com botão físico

Funcionamento offline (sem internet)

🛠️ Componentes Utilizados
Componente	Quantidade
Arduino Uno/Nano	3 (1 mestre + 2 escravos)
Sensor Ultrassônico HC-SR04	2
Display LCD 16x2 com I2C	1
LEDs (vermelho, amarelo, verde)	3
Buzzer Piezo	1
Botão Push-Button	1
Jumpers, resistores, protoboard	Diversos

📦 Diagrama do Sistema
less

Copiar

Editar

[Arduino Escravo 1]     [Arduino Escravo 2]
   HC-SR04                HC-SR04
       |                     |
       |                     |
       +---------------------+
                 |
                 v
         🧠 [Arduino Mestre]
        LCD, LEDs, Buzzer, Botão
Todos conectados via I2C:
📘 Mestre: Wire.begin()
📗 Escravos: Wire.begin(address)

🖥️ Simulação Online
▶️ 🔗 Projeto no Tinkercad: https://www.tinkercad.com/things/axvVWG0wVHf/editel?returnTo=%2Fdashboard&sharecode=XTL2aAalOVtCPEbipjSoDDmAf6q0bY2dyR9jWh73FVo

📹 🔗 Vídeo Demonstrativo no YouTube:

🧪 Como Simular no Tinkercad:

Crie 3 projetos separados (1 mestre, 2 escravos).

Configure os endereços I2C dos escravos.

Use o recurso de "Serial Monitor" para simular comunicação I2C entre as instâncias.

Nota: O suporte a múltiplos Arduinos em um mesmo projeto é limitado no Tinkercad — prefira o Wokwi.

🔍 Código (Resumo das Responsabilidades)
Arduino Escravo (cada um):
Faz a leitura do sensor ultrassônico

Envia distância medida ao Arduino mestre via I2C

Arduino Mestre:
Recebe as medições dos dois escravos

Exibe um sensor por vez no LCD

Com botão, permite alternar a exibição

Com nível crítico, prioriza a exibição automaticamente

Ativa LED e buzzer em estados críticos

✅ Benefícios
Benefício	Descrição
🛑 Alerta Imediato	LEDs e buzzer alertam em tempo real
🌐 Sem Internet	Ideal para regiões desconectadas
💸 Baixo Custo	Componentes acessíveis
⚖️ Escalável	Basta adicionar mais escravos
🔒 Confiável	Comunicação direta via I2C
💻 Integração Web	Futuro suporte a mapa interativo e doações

👥 Equipe de Desenvolvimento

Jéssica Tavares – RM566220

Luara Soares – RM561266

Miguel Amaro – RM566200

📂 Sobre o Projeto
Este projeto é parte de uma iniciativa educacional para desenvolver soluções tecnológicas com impacto social real, focando em cidades vulneráveis a enchentes. A ideia é que comunidades possam montar seu próprio sistema, sem depender de infraestrutura avançada, com foco em:

Monitoramento local

Ação imediata

Integração com plataformas de apoio e cadastro
