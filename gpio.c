#include "hwdefs.h"
#include "gpio.h"

#include <assert.h>

enum { INVALID_ADDRESS = 0xFFFF };

static uint16_t gpio_port_address_get(enum gpio_port port)
{
    switch (port) {
    case GPIO_PORT_P1:
        return P1_BASE;
    case GPIO_PORT_P2:
        return P2_BASE;
    case GPIO_PORT_P3:
        return P3_BASE;
    case GPIO_PORT_P4:
        return P4_BASE;
    case GPIO_PORT_P5:
        return P5_BASE;
    case GPIO_PORT_P6:
        return P6_BASE;
    case GPIO_PORT_P7:
        return P7_BASE;
    case GPIO_PORT_P8:
        return P8_BASE;
    case GPIO_PORT_PJ:
        return PJ_BASE;
    default:
        break;
    }
    return INVALID_ADDRESS;
}

static uint16_t gpio_pins_adjust(enum gpio_port port, uint16_t pins)
{
    if ((port & 1) ^ 1)
        pins <<= 8;
    return pins;
}

void gpio_pins_set_as_out(enum gpio_port port, uint16_t pins)
{
    const uint16_t base_address = gpio_port_address_get(port);
    if (base_address == INVALID_ADDRESS)
        return;
    pins = gpio_pins_adjust(port, pins);
    HWREG16(base_address + OFS_PASEL) &= ~pins;
    HWREG16(base_address + OFS_PADIR) |= pins;
}

void gpio_pins_set_as_in(enum gpio_port port, uint16_t pins)
{
    const uint16_t base_address = gpio_port_address_get(port);
    if (base_address == INVALID_ADDRESS)
        return;
    pins = gpio_pins_adjust(port, pins);
    HWREG16(base_address + OFS_PASEL) &= ~pins;
    HWREG16(base_address + OFS_PADIR) &= ~pins;
    HWREG16(base_address + OFS_PAREN) &= ~pins;
}

void gpio_pins_set_as_pf_out(enum gpio_port port, uint16_t pins)
{
    const uint16_t base_address = gpio_port_address_get(port);
    if (base_address == INVALID_ADDRESS)
        return;
    pins = gpio_pins_adjust(port, pins);
    HWREG16(base_address + OFS_PADIR) |= pins;
    HWREG16(base_address + OFS_PASEL) |= pins;
}

void gpio_pins_set_as_pf_in(enum gpio_port port, uint16_t pins)
{
    const uint16_t base_address = gpio_port_address_get(port);
    if (base_address == INVALID_ADDRESS)
        return;
    pins = gpio_pins_adjust(port, pins);
    HWREG16(base_address + OFS_PADIR) &= ~pins;
    HWREG16(base_address + OFS_PASEL) |= pins;
}

void gpio_pins_set_high(enum gpio_port port,
                        uint16_t pins)
{
    const uint16_t base_address = gpio_port_address_get(port);
    if (base_address == INVALID_ADDRESS)
        return;
    pins = gpio_pins_adjust(port, pins);
    HWREG16(base_address + OFS_PAOUT) |= pins;
}

void gpio_pins_set_low(enum gpio_port port, uint16_t pins)
{
    const uint16_t base_address = gpio_port_address_get(port);
    if (base_address == INVALID_ADDRESS)
        return;
    pins = gpio_pins_adjust(port, pins);
    HWREG16(base_address + OFS_PAOUT) &= ~pins;
}

void gpio_pins_toggle(enum gpio_port port, uint16_t pins)
{
    const uint16_t base_address = gpio_port_address_get(port);
    if (base_address == INVALID_ADDRESS)
        return;
    pins = gpio_pins_adjust(port, pins);
    HWREG16(base_address + OFS_PAOUT) ^= pins;
}

enum gpio_pin_status gpio_pin_get(enum gpio_port port, uint16_t pins)
{
    const uint16_t base_address = gpio_port_address_get(port);
    if (base_address == INVALID_ADDRESS)
        return GPIO_INPUT_PIN_LOW;
    pins = gpio_pins_adjust(port, pins);
    const uint16_t value = HWREG16(base_address + OFS_PAIN) & pins;
    return (value > 0) ? GPIO_INPUT_PIN_HIGH : GPIO_INPUT_PIN_LOW;
}
