#include "pico/stdlib.h"
#include "buzzer_functions.c"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include <stdio.h>  // Necessário para printf
#include <stdlib.h> // Necessário para funções da stdlib

int main()
{
    stdio_init_all(); // Inicializa a comunicação serial
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
    printf("APERTE O BOTAO A PARA MUDAR A FREQUENCIA E O BOTAO B PARA PAUSAR\n");

    while (true)
    {
        beep(BUZZER_PIN);
    }
    return 0;
}
