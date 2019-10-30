#include "hwdefs.h"
#include "wdt_a.h"

#define WDT_CONTROL_ADDRESS (WDT_A_BASE + OFS_WDTCTL)

void wdt_a_stop(void)
{
    const uint8_t st = (HWREG16(WDT_CONTROL_ADDRESS) & 0x00FF) | WDTHOLD;
    HWREG16(WDT_CONTROL_ADDRESS) = WDTPW + st;
}
