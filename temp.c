#include <stdint.h>
#include "dht11.h"
#include "temp.h"

static volatile uint32_t timer = 0;

void
format(uint16_t integral, uint16_t decimal, char * buffer, uint8_t size);

int
main(void)
{
    // Enable GPIOA
    RCC_AHB1ENR |= (0x01 << 0x00);

    // Alternate function (AF) mode for PA9 and PA10
    GPIOA_MODER |= (0x02 << 0x12) | (0x02 << 0x14);
    // AF7 (USART TX and RX) for PA9 and PA10
    GPIOA_AFRH  |= (0x07 << 0x04) | (0x07 << 0x08); 

    // Configure PA5 as the signal to the HT11 sensor
    GPIOA_MODER   |= (0x01 << 0x0A);
        // Open-drain lets both MCU and DHT11 control the signal line
    GPIOA_OTYPER  |= (0x01 << 0x05);
    GPIOA_OSPEEDR |= (0x03 << 0x05);

    // Configure PA6 for debugging output
    GPIOA_MODER   |= (0x01 << 0x0C);
    GPIOA_OTYPER  |= (0x01 << 0x06);
    GPIOA_OSPEEDR |= (0x03 << 0x06);
    GPIOA_PUPDR   |= (0x01 << 0x06);

    // Enable USART1
    RCC_APB2ENR |= (0x01 << 0x04);
    // Configure baud rate based on APB2 clock (equals to HSI 16MHz by default)
    USART1_BRR   = 0x683;
    // Enable TX and RX, and USART overall
    USART1_CR1  |= (0x01 << 0x03) | (0x01 << 0x02) | (0x01 << 0x0D);

    // Use AHB (not pre-scaled) as the SysTick clock
    STK_CTRL    |= (0x01 << 0x02);
    // At the HSI 16MHz, this gives 9us granularity. Pick a prime number that
    // is not too big to minimise the risk of the time check coinciding with
    // the rising edge of the signal.
    STK_LOAD     = 144UL;
    STK_VAL      = 0UL;
    STK_CTRL    |= (0x01 << 0x0) | (0x01 << 0x1);

    __asm("CPSIE i");

    while (1)
    {
        // Wait for an input on USART
        if (USART1_SR & (0x01 << 0x05))
        {
            volatile char unused = USART1_DR;

            uint8_t rh_integral = 0;
            uint8_t rh_decimal  = 0;
            uint8_t t_integral  = 0;
            uint8_t t_decimal   = 0;

            uint8_t result = get_readings(&rh_integral, &rh_decimal, &t_integral, &t_decimal);
            // TODO: Read result to determine outcome

            // Send the readings to USART
            char temperature[OUTPUT_LENGTH];
            format(t_integral, t_decimal, temperature, OUTPUT_LENGTH);
            for (int i=0; i<OUTPUT_LENGTH; i++)
            {
                USART1_DR = temperature[i];
                while (!(USART1_SR & (0x01 << 0x06)))
                    ;
            }

            char rh[OUTPUT_LENGTH];
            format(rh_integral, rh_decimal, rh, OUTPUT_LENGTH);
            for (int i=0; i<OUTPUT_LENGTH; i++)
            {
                USART1_DR = rh[i];
                while (!(USART1_SR & (0x01 << 0x06)))
                    ;
            }

            // ... followed by a TAB character
            USART1_DR = '\t';
            while (!(USART1_SR & (0x01 << 0x06)))
                ;
        }
    }

    __asm("CPSID i");

    return 0;
}

void
Systick_Handler(void)
{
    timer += 9; // This must match the clock precision
}

uint8_t
get_signal()
{
    // Output to PA6 for debugging
    GPIOA_ODR ^= (0x01 << 0x06);
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

// Poor man's 'sprintf' follows...
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
