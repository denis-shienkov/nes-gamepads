#include "hid.h"
#include "core.h"
#include "usb.h"

void hid_ep_init(void)
{
    // Disable end point 1 output.
    EP1OUTCFG = (EP1OUTCFG & ~bmEP_VALID) | bmEP_DISABLE;
    sync_delay();
    // Enable end point 1 input in interrupt mode.
    EP1INCFG = bmEP_ENABLE | bmEP_INT;
    sync_delay();
    // Disable end point 2.
    EP2CFG = (EP2CFG & ~bmEP_VALID) | bmEP_DISABLE;
    sync_delay();
    // Disable end point 4.
    EP4CFG = (EP4CFG & ~bmEP_VALID) | bmEP_DISABLE;
    sync_delay();
    // Disable end point 6.
    EP6CFG = (EP6CFG & ~bmEP_VALID) | bmEP_DISABLE;
    sync_delay();
    // Disable end point 8.
    EP8CFG = (EP8CFG & ~bmEP_VALID) | bmEP_DISABLE;
    sync_delay();

    // Reset all FIFOs.
    FIFORESET = bmNAKALL; // NAK all host transfers.
    sync_delay();
    FIFORESET = 0x00;
    sync_delay();
}
