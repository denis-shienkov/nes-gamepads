#include "hwdefs.h"
#include "pmm.h"
#include "ucs.h"
#include "usb.h"
#include "wdt_a.h"

static void hw_clocks_init(uint32_t mclk_freq)
{
    ucs_init(UCS_FLLREF, UCS_REFOCLK_SELECT, UCS_CLOCK_DIVIDER_1);
    ucs_init(UCS_ACLK, UCS_REFOCLK_SELECT, UCS_CLOCK_DIVIDER_1);
    ucs_fll_settle_init(mclk_freq / 1000, mclk_freq / 32768);

    // Use REFO for FLL and ACLK.
    UCSCTL3 = (UCSCTL3 & ~SELREF_7) | SELREF__REFOCLK;
    UCSCTL4 = (UCSCTL4 & ~SELA_7) | SELA__REFOCLK;
}

static void hw_init(void)
{
    __disable_interrupt();

    wdt_a_stop();
    pmm_voltage_init(PMM_VOLTAGE_1_85V);
    hw_clocks_init(8000000);
    usb_init();

    __enable_interrupt();
}

static void hw_loop_exec(void)
{
    for (;;) {
        usb_task();
    }
}

int main(void)
{
    hw_init();
    hw_loop_exec();
    return 0;
}
