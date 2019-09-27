// Allocate all registers once here (only for C51 compiler).
#define DEFINE_REGS
#include "regs.h"

#include "core.h"
#include "irqs.h"
#include "usb.h"

static void loop_exec(void)
{
    while (TRUE) {
        usb_task();
    }
}

int main(void)
{
    core_init();
    usb_init();
    loop_exec();
    return 0;
}

INTERRUPT(usb_resume_isr, WKUP_IRQ)
{
    usb_rsmirq_clear();
}
