#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

// Configuração do pino do buzzer
#define BUZZER_PIN 21
#define BUTTONA_PIN 5
#define BUTTONB_PIN 6

// Configuração da frequência do buzzer (em Hz)
#define BUZZER_FREQUENCY 100

// Definição de uma função para inicializar o PWM no pino do buzzer
void pwm_init_buzzer(uint pin) {
    // Configurar o pino como saída de PWM
    gpio_set_function(pin, GPIO_FUNC_PWM);

    // Obter o slice do PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Configurar o PWM com frequência desejada
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (BUZZER_FREQUENCY * 4096)); // Divisor de clock
    pwm_init(slice_num, &config, true);

    // Iniciar o PWM no nível baixo
    pwm_set_gpio_level(pin, 0);
}

// Definição de uma função para emitir um beep com duração especificada
void beep(uint pin, uint duration_ms) {
    // Obter o slice do PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Configurar o duty cycle para 50% (ativo)
    pwm_set_gpio_level(pin, 2048);

    // Temporização
    sleep_ms(duration_ms);

    // Desativar o sinal PWM (duty cycle 0)
    pwm_set_gpio_level(pin, 0);

    // Pausa entre os beeps
    sleep_ms(100); // Pausa de 100ms
}

int main() {
    // Configuração do GPIO para o botão como entrada com pull-up
    gpio_init(BUTTONA_PIN);
    gpio_set_dir(BUTTONA_PIN, GPIO_IN);
    gpio_pull_up(BUTTONA_PIN);

    gpio_init(BUTTONB_PIN);
    gpio_set_dir(BUTTONB_PIN, GPIO_IN);
    gpio_pull_up(BUTTONB_PIN);

    // Configuração do GPIO para o buzzer como saída
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    // Inicializar o PWM no pino do buzzer
    pwm_init_buzzer(BUZZER_PIN);
    while (true) {
        // Verifica o estado do botão
        if (gpio_get(BUTTONA_PIN) == 0) {
            beep(BUZZER_PIN, 150);
        } else if (gpio_get(BUTTONB_PIN) == 0) {
            beep(BUZZER_PIN, 350);
        }
    }

    return 0;
}
