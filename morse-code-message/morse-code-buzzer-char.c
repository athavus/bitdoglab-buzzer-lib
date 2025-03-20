#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#define BUZZER_PIN 21
#define BUZZER_FREQUENCY 100
#define DOT_DURATION 150   // Duração do ponto em ms
#define DASH_DURATION 350  // Duração do traço em ms
#define SPACE_DURATION 700 // Espaço entre palavras

// Estrutura para mapear caracteres para código Morse
typedef struct {
    char letter;
    const char *morse;
} MorseCode;

// Tabela Morse
MorseCode morse_table[] = { 
    {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."},
    {'F', "..-."}, {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"},
    {'K', "-.-"}, {'L', ".-.."}, {'M', "--"}, {'N', "-."}, {'O', "---"},
    {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
    {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"}, {'Y', "-.--"},
    {'Z', "--.."}, {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"},
    {'4', "....-"}, {'5', "....."}, {'6', "-...."}, {'7', "--..."}, {'8', "---.."},
    {'9', "----."}, {' ', " "}
};

// Inicializa o PWM no buzzer
void pwm_init_buzzer(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (BUZZER_FREQUENCY * 4096));
    pwm_init(slice_num, &config, true);
    pwm_set_gpio_level(pin, 0);
}

// Função para emitir um beep
void beep(uint pin, uint duration_ms) {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_gpio_level(pin, 2048);
    sleep_ms(duration_ms);
    pwm_set_gpio_level(pin, 0);
    sleep_ms(100); // Pequena pausa entre sinais
}

// Converte um caractere para código Morse e emite o som
void play_morse_char(char c) {
    // Converter para maiúscula
    if (c >= 'a' && c <= 'z') {
        c -= ('a' - 'A');
    }
    
    printf("Convertendo o caractere '%c' para código Morse.\n", c);  // Log de conversão de caractere

    for (int i = 0; i < sizeof(morse_table) / sizeof(morse_table[0]); i++) {
        if (morse_table[i].letter == c) {
            const char *morse = morse_table[i].morse;
            printf("Código Morse para '%c': %s\n", c, morse);  // Log do código Morse

            while (*morse) {
                if (*morse == '.') {
                    printf("Emitindo ponto...\n");  // Log do ponto
                    beep(BUZZER_PIN, DOT_DURATION);
                } else if (*morse == '-') {
                    printf("Emitindo traço...\n");  // Log do traço
                    beep(BUZZER_PIN, DASH_DURATION);
                }
                morse++;
                sleep_ms(150); // Pausa entre símbolos
            }
            printf("Letra '%c' processada.\n", c);  // Log de letra processada
            sleep_ms(300); // Pausa entre letras
            return;
        }
    }
}

// Função para converter e tocar uma string em código Morse
void play_morse(const char *text) {
    printf("Iniciando a conversão da mensagem: %s\n", text);  // Log do início da conversão

    while (*text) {
        if (*text == ' ') {
            printf("Espaço detectado. Pausa entre palavras.\n");  // Log de espaço entre palavras
            sleep_ms(SPACE_DURATION); // Pausa maior para separar palavras
        } else {
            play_morse_char(*text);
        }
        text++;
    }

    printf("Conversão completa.\n");  // Log de término da conversão
}

int main() {
    stdio_init_all();
    pwm_init_buzzer(BUZZER_PIN);
    
    const char *message = "ANTONIO";
    printf("Mensagem a ser convertida: %s\n", message);  // Log da mensagem a ser convertida
    play_morse(message);
    
    return 0;
}
