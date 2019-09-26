// Allocate all registers once here (only for C51 compiler).
#define DEFINE_REGS
#include "fx2regs.h"

#include "fx2hw.h"
#include "fx2irqs.h"
#include "fx2usb.h"

static void loop_exec(void)
{
    while (TRUE) {
        usb_task();
    }
}

int main(void)
{
    hw_init();
    usb_init();
    loop_exec();
    return 0;
}

void usb_resume_isr(void) INTERRUPT__ WKUP_IRQ
{
    usb_rsmirq_clear();
}
