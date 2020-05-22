#include <stdint.h>
#include "dht11.h"

/**
 * The datasheet for the DHT11 module can be found on the web.
 * https://www.bing.com/search?form=MOZLBR&pc=MOZI&q=dht11+datasheet
 */

void
expect(uint8_t signal, uint32_t duration_us);

uint32_t
get_timer();

void
reset_timer();

void
set_signal(uint8_t signal);

uint8_t
get_signal();

uint8_t
get_readings(uint8_t * rh_integral, uint8_t * rh_decimal, uint8_t * t_integral, uint8_t * t_decimal)
{
    uint8_t  bit_index = 0;

    uint32_t valueh = 0;
    uint8_t  valuel = 0;

    uint8_t state = BEGIN;

    bool running = TRUE;
    while (running)
    {
        switch (state)
        {
            case BEGIN:
                expect(LOW, 18000);
                state = WAITING;
                break;

            case WAITING:
                expect(HIGH, 40);
                if (get_signal() == LOW)
                    state = DHT_RESPONSE;
                else
                    state = ERROR_WAITING;
                break;

            case DHT_RESPONSE:
                expect(LOW, 80);
                if (get_signal() == HIGH)
                    state = DHT_READY;
                else
                    state = ERROR_DHT_RESPONSE;
                break;

            case DHT_READY:
                expect(HIGH, 80);
                if (get_signal() == LOW)
                    state = DHT_DATA;
                else
                    state = ERROR_DHT_RESPONSE;
                break;

            case DHT_DATA:
                expect(LOW, 50);
                if (get_signal() == HIGH)
                    state = ZERO_BIT;
                else
                    state = ERROR_DHT_DATA;
                break;

            case ZERO_BIT:
                expect(HIGH, 28);
                if (get_signal() == LOW)
                {
                    if (bit_index < 32)
                    {
                        valueh = (valueh << 1);
                    }
                    else
                    {
                        valuel = (valuel << 1);
                    }

                    if (++bit_index == 40)
                    {
                        state = CHECKSUM;
                    }
                    else
                    {
                        state = DHT_DATA;
                    }
                }
                else
                {
                    state = ONE_BIT;
                }
                break;

            case ONE_BIT:
                expect(HIGH, 42); // 70us -28us
                if (get_signal() == LOW)
                {
                    if (bit_index < 32)
                    {
                        valueh = (valueh << 1) | (0x01 << 0);
                    }
                    else
                    {
                        valuel = (valuel << 1) | (0x01 << 0);
                    }

                    if (++bit_index == 40)
                    {
                        state = CHECKSUM;
                    }
                    else
                    {
                        state = DHT_DATA;
                    }
                }
                else
                {
                    state = ERROR_DHT_DATA;
                }
                break;

            case CHECKSUM:
                *rh_integral = (uint8_t) (valueh >> 24);
                *rh_decimal  = (uint8_t) (valueh >> 16);
                *t_integral  = (uint8_t) (valueh >>  8);
                *t_decimal   = (uint8_t) (valueh >>  0);

                uint8_t checksum = *rh_integral+*rh_decimal+*t_integral+*t_decimal;
                if (checksum == valuel && checksum > 0)
                    state = DATA_COMPLETE;
                else
                    state = ERROR_CHECKSUM;
                break;

            case DATA_COMPLETE:
                state = END;
                break;

            case ERROR_WAITING:
            case ERROR_DHT_RESPONSE:
            case ERROR_DHT_DATA:
            case ERROR_CHECKSUM:
            case END:
                running = FALSE;
                break;
        }
    }

    return state;
}

void
expect(uint8_t signal, uint32_t duration_us)
{
    if (get_signal() != signal)
        set_signal(signal);
    reset_timer();
    while (get_timer() < duration_us)
        if (get_signal() != signal)
            break;
}

