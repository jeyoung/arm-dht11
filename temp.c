#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "dht11.h"
#include "temp.h"

static volatile uint32_t timer = 0;
static volatile uint32_t read_timer = 0;

void
format(uint16_t, uint16_t, char *, uint8_t);

void
send(char *, uint8_t);

/*
 * This program reads the temperature from a DHT11 sensor and sends
 * the measured value to USART1.
 *
 * It has been tested on an STM32 Nucleo F446RE.
 */
int
main(void)
{
    /* Enable GPIOA */
    RCC_AHB1ENR |= (0x01 << 0x00);

    /* Alternate function (AF) mode for PA9 and PA10 */
    GPIOA_MODER |= (0x02 << 0x12) | (0x02 << 0x14);
    /* AF7 (USART TX and RX) for PA9 and PA10 */
    GPIOA_AFRH  |= (0x07 << 0x04) | (0x07 << 0x08); 

    /* Configure PA5 as the signal to the HT11 sensor */
    GPIOA_MODER   |= (0x01 << 0x0A);
        /* Open-drain lets both MCU and DHT11 control the signal line */
    GPIOA_OTYPER  |= (0x01 << 0x05);
    GPIOA_OSPEEDR |= (0x03 << 0x05);

    /* Configure PA6 for debugging output */
    GPIOA_MODER   |= (0x01 << 0x0C);
    GPIOA_OSPEEDR |= (0x03 << 0x06);
    GPIOA_PUPDR   |= (0x01 << 0x0C);

    /* Enable USART1 */
    RCC_APB2ENR |= (0x01 << 0x04);
    /* Configure baud rate based on APB2 clock (equals to HSI 16MHz by default) */
    USART1_BRR   = 0x683;
    /* Enable TX and RX, and USART overall */
    USART1_CR1  |= (0x01 << 0x03) | (0x01 << 0x02) | (0x01 << 0x0D);

    /* Use AHB (not pre-scaled) as the SysTick clock */
    STK_CTRL    |= (0x01 << 0x02);
    /*
     * At the HSI 16MHz, this gives 3us granularity. Pick a prime number that
     * is not too big to minimise the risk of the time check coinciding with
     * the rising edge of the signal.
     */
    STK_LOAD     = 48UL;
    STK_VAL      = 0UL;
    STK_CTRL    |= (0x01 << 0x0) | (0x01 << 0x1);

    __asm("CPSIE i");

    while (1)
    {
        /* Every 2s */
        if (read_timer % 1000000 == 0)
        {
            read_timer = 0;

            uint8_t rh_integral = 0;
            uint8_t rh_decimal  = 0;
            uint8_t t_integral  = 0;
            uint8_t t_decimal   = 0;

            uint8_t result = get_readings(&rh_integral, &rh_decimal, &t_integral, &t_decimal);

            char test[15];
            sprintf(test, "%d\n", result);
            send(test, 15);

            if (result != END)
            {
                char * message = "STATE: ";

                char output[OUTPUT_LENGTH];
                format(result, 0, output, OUTPUT_LENGTH);

                for (uint8_t n=0; n<strlen(message)-1; n++)
                    output[n] = message[n];

                send(output, OUTPUT_LENGTH);
            }
            else
            {
                /* Send the readings to USART */
                char temperature[OUTPUT_LENGTH];
                format(t_integral, t_decimal, temperature, OUTPUT_LENGTH);
                send(temperature, OUTPUT_LENGTH);

                char rh[OUTPUT_LENGTH];
                format(rh_integral, rh_decimal, rh, OUTPUT_LENGTH);
                send(rh, OUTPUT_LENGTH);
            }

            char * newline = "\r\n";
            send(newline, 2);

            /* Output to PA6 for debugging */
            GPIOA_ODR ^= (0x01 << 0x06);
        }

    }

    __asm("CPSID i");

    return 0;
}

void
Systick_Handler(void)
{
    timer += 3;
    read_timer += 3;
}

uint8_t
get_signal()
{
    return (GPIOA_IDR & (0x01 << 0x05)) ? HIGH : LOW;
}

void
set_signal(uint8_t signal)
{
    GPIOA_ODR = (signal) ? (GPIOA_ODR | (0x01 << 0x05)) : (GPIOA_ODR & ~(0x01 << 0x05));
}

void
reset_timer()
{
    timer = 0;
}

uint32_t
get_timer()
{
    return timer;
}

/* Poor man's 'sprintf' follows... */
void
format(uint16_t integral, uint16_t decimal, char * buffer, uint8_t size)
{
    for (uint8_t i=0; i<size; i++)
        buffer[i] = ' ';

    uint8_t has_decimal = decimal > 0;

    int c = 0;
    while (decimal > 0 && ++c <= size)
    {
        uint8_t digit = decimal % 10;
        decimal = decimal / 10;
        buffer[size - c] = '0'+(char)digit;
    }
    if (has_decimal)
    {
        buffer[size - ++c] = '.';
    }
    while (integral > 0 && ++c <= size)
    {
        uint8_t digit = integral % 10;
        integral = integral / 10;
        buffer[size - c] = '0'+(char)digit;
    }
}

void
send(char * buffer, uint8_t size)
{
    for (int i=0; i<size; i++)
    {
        USART1_DR = buffer[i];
        while (!(USART1_SR & (0x01 << 0x06)))
            ;
    }
}
