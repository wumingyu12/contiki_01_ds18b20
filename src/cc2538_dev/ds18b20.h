#include "dev/gpio.h"

#define DS18B20_PORT         	GPIO_B_NUM
#define DS18B20_PIN		2	/**RF.11 - PB2 **/

#define DS18B20_PORT_BASE	GPIO_PORT_TO_BASE(DS18B20_PORT)
#define DS18B20_PIN_MASK	GPIO_PIN_MASK(DS18B20_PIN)

#define SET_IN          GPIO_SET_INPUT(DS18B20_PORT_BASE,DS18B20_PIN_MASK);clock_delay_usec(1)
#define SET_OUT         GPIO_SET_OUTPUT(DS18B20_PORT_BASE,DS18B20_PIN_MASK);clock_delay_usec(1)
#define CL_DQ           GPIO_CLR_PIN(DS18B20_PORT_BASE,DS18B20_PIN_MASK);clock_delay_usec(1)
#define SET_DQ          GPIO_SET_PIN(DS18B20_PORT_BASE,DS18B20_PIN_MASK);clock_delay_usec(1)
#define DATA_IN()       (GPIO_READ_PIN(DS18B20_PORT_BASE,DS18B20_PIN_MASK))




extern void ds18b20_read( uint8_t * );
