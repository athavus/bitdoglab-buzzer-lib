# 📦 Biblioteca `colored-noise` - Buzzer para BitdogLab (RP2040)

Esta biblioteca implementa um sistema de reprodução de sons com diferentes frequências associadas a **"cores de ruído"** (branco, rosa, marrom, azul, violeta), utilizando um buzzer controlado por PWM. Ela permite interação por botões físicos para alternar entre frequências ou pausar o som.

---

## 🧠 Funcionalidades

- Reproduz sons no buzzer em diferentes frequências (cores de ruído).
- Alternância entre frequências usando o **Botão A**.
- Pausa e retomada do som usando o **Botão B**.
- Utiliza interrupções com debounce para os botões.
- Saída de informações pelo terminal serial (via USB).
- Captura automática de logs da porta serial via script Python.

---

## 📌 Pinos Utilizados

| Componente | GPIO |
|------------|------|
| Buzzer     | 21   |
| Botão A    | 5    |
| Botão B    | 6    |

---

## 🎵 Tabela de Frequências e Cores

| Cor do Ruído | Frequência (Hz) |
|--------------|------------------|
| Branco       | 2500             |
| Rosa         | 800              |
| Marrom       | 400              |
| Azul         | 3500             |
| Violeta      | 4500             |

---

## 🚀 Como Usar

1. Clone este repositório e adicione os arquivos ao seu projeto BitdogLab.
3. Compile o projeto com o SDK da Raspberry Pi Pico W.
4. Faça o upload para a placa.
5. Utilize um monitor serial para acompanhar os logs.

---

## 📁 Arquivos

### `lib-buzzer.c`

Contém toda a lógica de controle de PWM, interrupções dos botões e funcionamento do buzzer.

### `logs.py`

Script Python auxiliar que escuta a porta serial da placa e salva todos os logs recebidos em um arquivo `.txt`. Muito útil para debug ou análise posterior.

#### ⚙️ Configurações:

No início do arquivo `logs.py`, você pode configurar:

```python
PORTA = 'COM7'                # Altere para a porta correta do seu sistema
BAUD = 115200                 # Deve bater com o baudrate definido no código em C
ARQUIVO_LOG = 'logs_buzzer.txt'  # Nome do arquivo de saída

---

## 🧪 Comandos de Interação

- **Aperte o botão A**: Alterna entre as cores/frequências de ruído.
- **Aperte o botão B**: Ativa ou desativa o som emitido pelo buzzer.

---