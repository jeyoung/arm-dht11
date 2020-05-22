#include <stdint.h>

#define BEGIN                        10
#define START                        20
#define WAITING                      30
#define ERROR_WAITING                40
#define DHT_RESPONSE                 50
#define ERROR_DHT_RESPONSE           60
#define DHT_READY                    70
#define ERROR_DHT_READY              80
#define DHT_DATA                     90
#define ERROR_DHT_DATA              100
#define ZERO_BIT                    110
#define ONE_BIT                     120
#define CHECKSUM                    130
#define ERROR_CHECKSUM              140
#define DATA_COMPLETE               150
#define END                         160

#define LOW                          0
#define HIGH                         1

#define bool                        uint8_t
#define FALSE                       0
#define TRUE                        1

void
expect(uint8_t signal, uint32_t duration_us);

uint32_t
get_timer();

void
reset_timer();

void
set_signal(uint8_t);

uint8_t
get_signal();

uint8_t 
get_readings(uint8_t*, uint8_t*, uint8_t*, uint8_t*);
