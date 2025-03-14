# 📡 Morse Code Message com Buzzer (BitdogLab + RP2040)

Este projeto converte uma mensagem em **Código Morse** e a emite usando um buzzer conectado à Raspberry Pi Pico W (BitdogLab). A cada caractere da mensagem, o sistema gera um som curto para o ponto (`.`) e um som longo para o traço (`-`), de acordo com o alfabeto Morse.

---

## ⚙️ Funcionamento

O sistema converte uma string fornecida para código Morse e emite os sinais correspondentes usando um buzzer:

- **Ponto (`.`)**: Emitido como um beep curto.
- **Traço (`-`)**: Emitido como um beep longo.
- **Espaço entre palavras**: Representado por uma pausa maior entre os sinais.
  
O código foi desenvolvido para ser configurado com a Raspberry Pi Pico W (BitdogLab) utilizando PWM para controlar o buzzer.

---

## 📁 Arquivo Principal

### `morse-code-message.c`

O código-fonte principal que:

- Configura o buzzer com PWM.
- Converte cada caractere da mensagem fornecida em código Morse e emite o som correspondente.
- Utiliza uma tabela de mapeamento de caracteres para código Morse, incluindo letras de A-Z e os números de 0-9.
- Realiza logs detalhados durante o processo de conversão para auxiliar no diagnóstico e na visualização do processo.

---

## 🔌 Conexões de Hardware

| Componente | GPIO | Função        |
|------------|------|----------------|
| Buzzer     | 21   | Saída de som   |

---

## 🛠️ Como Compilar

1. Instale o SDK do Raspberry Pi Pico W.
2. Adicione este arquivo ao seu projeto.
3. Compile com `cmake` e `make` ou utilize o comando "Compile Pico Project" da extensão Raspberry Pi Pico [extension id: raspberry-pi.raspberry-pi-pico]:

```bash
mkdir build
cd build
cmake ..
make
```

ou (Se estiver usando o "Compile Pico Project" da extensão)

- Ctrl + Shift + P
- Digite "Compile Pico Project estando na pasta da biblioteca que estiver usando (manual-morse-code, morse-code-message e colored-noise)"

4. Copie o .uf2 gerado para a placa via modo BOOTSEL.