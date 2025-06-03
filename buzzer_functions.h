#ifndef BUZZER_FUNCTIONS_H
#define BUZZER_FUNCTIONS_H

#include "pico/stdlib.h"

// Definições de pinos
#define BUZZER_PIN 21
#define BUTTONA_PIN 5  // Botão A conectado ao GPIO5
#define BUTTONB_PIN 6  // Botão B conectado ao GPIO6

/**
 * Inicializa o buzzer PWM na frequência atual.
 * @param pin O número do pino ao qual o buzzer está conectado.
 */
void pwm_init_buzzer(uint pin);

/**
 * Emite um som de beep no buzzer.
 * A função deve ser chamada continuamente para manter o som ativado.
 * @param pin O número do pino ao qual o buzzer está conectado.
 */
void beep(uint pin);

/**
 * Função de callback para lidar com o pressionamento de botões.
 * Alterna a frequência do buzzer ou ativa/desativa o buzzer.
 * @param gpio O pino GPIO do botão pressionado.
 * @param events Os eventos que ocorreram no botão.
 */
void button_callback(uint gpio, uint32_t events);

#endif // BUZZER_FUNCTIONS_H
