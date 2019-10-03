#include "core.h"
#include "gpio.h"
#include "hid.h"
#include "regs.h"

static WORD g_counter = 0;
static BYTE g_value = 0;

// We use this empirical value to make
// a GPIO polling every ~10 msec (rough).
// It is a simplest way, because instead
// we need to use a timers with interrupts
// callbacks.
enum { POLLING_COUNTER = 580 };

void gpio_init(void)
{
    // Set interface to ports.
    IFCONFIG = (IFCONFIG & (~bmIFCFG)) | bmIFPORTS;
    sync_delay();
}

void gpio_task(void)
{
    if (g_counter < POLLING_COUNTER) {
        ++g_counter;
    } else {
        g_counter = 0;

        if (g_value == 0)
            g_value = 1;

        hid_ep1_report_update(0, g_value);
        hid_ep1_report_update(1, g_value);

        g_value *= 2;
    }
}
