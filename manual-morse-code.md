# 🔠 Manual Morse Code com Buzzer (BitdogLab + RP2040)

Este projeto permite que você **envie manualmente sinais em código Morse** utilizando dois botões físicos conectados à Raspberry Pi Pico W (BitdogLab). O sistema utiliza um buzzer PWM para emitir os sons correspondentes aos sinais curtos (**ponto**) e longos (**traço**), conforme os botões pressionados.

---

## ⚙️ Funcionamento

- **Botão A**: Envia um *ponto* (`.`) com som curto.
- **Botão B**: Envia um *traço* (`-`) com som longo.
- O buzzer emite os sons manualmente conforme o usuário pressiona os botões.
- Ideal para treinar Morse de forma auditiva.

---

## 📁 Arquivo Principal

### `morse-code-buzzer.c`

Código-fonte principal que:

- Inicializa o PWM no pino do buzzer.
- Configura os botões com pull-up.
- Em um laço infinito, escuta os botões:
  - Botão A: emite um beep curto (150ms).
  - Botão B: emite um beep longo (350ms).
- Utiliza `pwm_set_gpio_level()` para gerar os tons via PWM.

---

## 🔌 Conexões de Hardware

| Componente | GPIO | Função        |
|------------|------|----------------|
| Buzzer     | 21   | Saída de som   |
| Botão A    | 5    | Envia Ponto    |
| Botão B    | 6    | Envia Traço    |

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