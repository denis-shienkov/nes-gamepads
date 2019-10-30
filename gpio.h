#ifndef MSP430_GPIO_H
#define MSP430_GPIO_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum gpio_port {
    GPIO_PORT_P1 = 1,
    GPIO_PORT_P2 = 2,
    GPIO_PORT_P3 = 3,
    GPIO_PORT_P4 = 4,
    GPIO_PORT_P5 = 5,
    GPIO_PORT_P6 = 6,
    GPIO_PORT_P7 = 7,
    GPIO_PORT_P8 = 8,
    GPIO_PORT_PJ = 13,
};

enum gpio_pin {
    GPIO_PIN0 = 0x0001,
    GPIO_PIN1 = 0x0002,
    GPIO_PIN2 = 0x0004,
    GPIO_PIN3 = 0x0008,
    GPIO_PIN4 = 0x0010,
    GPIO_PIN5 = 0x0020,
    GPIO_PIN6 = 0x0040,
    GPIO_PIN7 = 0x0080,
    GPIO_PIN8 = 0x0100,
    GPIO_PIN9 = 0x0200,
    GPIO_PIN10 = 0x0400,
    GPIO_PIN11 = 0x0800,
    GPIO_PIN12 = 0x1000,
    GPIO_PIN13 = 0x2000,
    GPIO_PIN14 = 0x4000,
    GPIO_PIN15 = 0x8000,
};

enum gpio_pin_status {
    GPIO_INPUT_PIN_HIGH = 0x01,
    GPIO_INPUT_PIN_LOW = 0x00
};

void gpio_pins_set_as_out(enum gpio_port port, uint16_t pins);
void gpio_pins_set_as_in(enum gpio_port port, uint16_t pins);
void gpio_pins_set_as_pf_out(enum gpio_port port, uint16_t pins);
void gpio_pins_set_as_pf_in(enum gpio_port port, uint16_t pins);
void gpio_pins_set_high(enum gpio_port port, uint16_t pins);
void gpio_pins_set_low(enum gpio_port port, uint16_t pins);
void gpio_pins_toggle(enum gpio_port port, uint16_t pins);

enum gpio_pin_status gpio_pin_get(enum gpio_port port, uint16_t pins);

#ifdef __cplusplus
}
#endif

#endif // MSP430_GPIO_H
