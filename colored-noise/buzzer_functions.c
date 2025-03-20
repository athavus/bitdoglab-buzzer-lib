#include "buzzer_functions.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include <stdio.h>  // Necessário para printf
#include <stdlib.h> // Necessário para funções da stdlib

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
