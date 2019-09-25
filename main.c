// Allocate all registers once here.
#define ALLOCATE_EXTERN
#include "fx2regs.h"

#include "fx2hw.h"
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
