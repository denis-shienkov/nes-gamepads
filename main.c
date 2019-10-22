// Allocate all registers once here (only for C51 compiler).
#define DEFINE_REGS
#include "regs.h"

#include "core.h"
#include "gpio.h"
#include "usb.h"

static void hw_init(void)
{
    usb_disconnect();
    code_all_irq_disable();

    core_init();
    gpio_init();
    usb_init();

    usb_connect();
    code_all_irq_enable();
}

static void hw_loop_exec(void)
{
    while (TRUE) {
        gpio_task();
        usb_task();
    }
}

int main(void)
{
    hw_init();
    hw_loop_exec();
    return 0;
}
