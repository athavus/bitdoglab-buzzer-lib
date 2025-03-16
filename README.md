# 📚 Repositório de Bibliotecas para Sinais Morse e Geração de Ruído Colorido

Este repositório contém uma biblioteca para o uso do buzzer na raspberry pi pico w da plataforma bitdoglab com algumas demos que se concentram na **geração de sinais Morse** e **análise de ruído colorido**. Cada biblioteca serve a um propósito distinto, mas todas estão interconectadas no contexto de geração de sinais e manipulação de dados. As bibliotecas estão organizadas da seguinte forma:


- **[morse-code-message](./morse-code-message.md)**: Converte texto para código Morse e emite os sinais usando um buzzer.
- **[manual-morse-code](./manual-morse-code.md)**: Permite a interação manual para a emissão de sinais Morse através de botões.
- **[colored-noise](./colored-noise.md)**: Gera ruído colorido e contém um script `logs.py` para registrar os dados recebidos via comunicação serial.

---

## 📂 Estrutura do Repositório

### 1. **[morse-code-message](./morse-code-message.md)**
Biblioteca em C que converte uma mensagem em texto para código Morse e emite os sinais correspondentes usando um buzzer.

### 2. **[manual-morse-code](./manual-morse-code.md)**
Biblioteca em C que permite ao usuário gerar sinais Morse manualmente, pressionando botões para emitir pontos e traços.

### 3. **[colored-noise](./colored-noise.md)**
Biblioteca que gera ruído colorido e inclui um script **`logs.py`** em Python para capturar dados recebidos via comunicação serial e registrá-los em arquivos de log.

---

## 📝 Funcionalidades

### **1. morse-code-message**
A biblioteca **morse-code-message** converte uma string de texto para código Morse e emite os sinais correspondentes (ponto e traço) usando um buzzer conectado à Raspberry Pi Pico W.

- Converte caracteres alfanuméricos em código Morse.
- Emite sinais de ponto (beep curto) e traço (beep longo) com uma pausa adequada entre cada caractere.
- Permite que uma mensagem inteira seja convertida e tocada em código Morse.

### **2. manual-morse-code**
A biblioteca **manual-morse-code** permite que o usuário emita sinais Morse manualmente por meio de dois botões conectados à Raspberry Pi Pico W:

- Pressione um botão para gerar um ponto (beep curto).
- Pressione o outro botão para gerar um traço (beep longo).
- O código utiliza PWM para controlar o buzzer e emite sinais de acordo com o tempo de pressionamento.

### **3. colored-noise**
A biblioteca **colored-noise** é responsável por gerar diferentes tipos de ruído colorido (ruído branco, rosa, entre outros), com aplicação em sistemas de áudio e simulações de sinal. Além disso, inclui um script **`logs.py`** que captura os dados recebidos de uma placa via comunicação serial (neste caso da Raspberry Pi Pico W) e os registra em um arquivo de log:

- Gera ruído colorido de várias frequências.
- Inclui um script Python para registrar os dados de entrada e armazená-los em um arquivo de log.

---
