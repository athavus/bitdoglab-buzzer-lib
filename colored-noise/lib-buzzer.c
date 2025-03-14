#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include <stdio.h>  // Necessário para printf
#include <stdlib.h> // Necessário para funções da stdlib

#define BUZZER_PIN 21
#define BUTTONA_PIN 5 // Botão A conectado ao GPIO5
#define BUTTONB_PIN 6 // Botão B conectado ao GPIO6

// Frequências aceitáveis para o buzzer
const uint buzzer_frequencies[] = {2500, 800, 400, 3500, 4500};
const char *buzzer_colors[] = {"branco", "rosa", "marrom", "azul", "violeta"};
const uint num_frequencies = sizeof(buzzer_frequencies) / sizeof(buzzer_frequencies[0]);
volatile uint current_frequency_index = 0;

// Variável para controlar se o buzzer deve tocar ou parar
volatile bool buzzer_active = true;

// Variáveis para debouncing
volatile uint32_t last_button_a_press = 0;
volatile uint32_t last_button_b_press = 0;
const uint32_t debounce_delay = 200; // Tempo de debounce (em milissegundos)

void pwm_init_buzzer(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (buzzer_frequencies[current_frequency_index] * 4096));
    pwm_init(slice_num, &config, true);
    pwm_set_gpio_level(pin, 0);
}

void beep(uint pin) {
    if (!buzzer_active) return;
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_gpio_level(pin, 4096);
    pwm_set_gpio_level(pin, 0);
}

void button_callback(uint gpio, uint32_t events) {
    uint32_t current_time = time_us_32() / 1000; // Tempo atual em milissegundos

    // Debouncing para o botão A
    if (gpio == BUTTONA_PIN && (events & GPIO_IRQ_EDGE_FALL)) {
        if (current_time - last_button_a_press >= debounce_delay) {
            last_button_a_press = current_time;
            printf("BOTAO A FOI APERTADO\n");
            current_frequency_index = (current_frequency_index + 1) % num_frequencies;
            pwm_init_buzzer(BUZZER_PIN); // Atualiza a frequência do buzzer
            printf("Frequencia atual: %uHz, Cor: %s\n", buzzer_frequencies[current_frequency_index], buzzer_colors[current_frequency_index]);
        }
    }

    // Debouncing para o botão B
    if (gpio == BUTTONB_PIN && (events & GPIO_IRQ_EDGE_FALL)) {
        if (current_time - last_button_b_press >= debounce_delay) {
            last_button_b_press = current_time;
            printf("BOTAO B FOI APERTADO\n");
            buzzer_active = !buzzer_active; // Alterna entre ativado/desativado
            if (!buzzer_active) {
                printf("O BUZZER ESTA DESATIVADO\n");
            } else {
                printf("O BUZZER ESTA ATIVADO\n");
            }
        }
    }
}

int main() {
    stdio_init_all();  // Inicializa a comunicação serial
    pwm_init_buzzer(BUZZER_PIN);

    // Configuração dos botões com pull-up interno
    gpio_init(BUTTONA_PIN);
    gpio_set_dir(BUTTONA_PIN, GPIO_IN);
    gpio_pull_up(BUTTONA_PIN);
    gpio_set_irq_enabled_with_callback(BUTTONA_PIN, GPIO_IRQ_EDGE_FALL, true, &button_callback);
    
    gpio_init(BUTTONB_PIN);
    gpio_set_dir(BUTTONB_PIN, GPIO_IN);
    gpio_pull_up(BUTTONB_PIN);
    gpio_set_irq_enabled_with_callback(BUTTONB_PIN, GPIO_IRQ_EDGE_FALL, true, &button_callback);
    printf("INICIOS DOS TESTES\n");
    // Exibe a frequência e a cor do buzzer inicial
    printf("Buzzer inicializado na frequencia: %uHz, Cor: %s\n", buzzer_frequencies[current_frequency_index], buzzer_colors[current_frequency_index]);
    prinf("APERTE O BOTAO A PARA MUDAR A FREQUENCIA E O BOTAO B PARA PAUSAR\n");

    while (true) {
        beep(BUZZER_PIN);
    }
    return 0;
}
