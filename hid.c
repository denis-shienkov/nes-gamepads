#include "hid.h"
#include "core.h"
#include "usb.h"

void hid_init(void)
{
    // Disable end point 1 output.
    EP1OUTCFG = bmEP_DISABLE;
    sync_delay();
    // Enable end point 1 input in interrupt mode.
    EP1INCFG = bmEP_ENABLE | bmEP_INT;
    sync_delay();
    // Disable end point 2.
    EP2CFG = bmEP_DISABLE;
    sync_delay();
    // Disable end point 4.
    EP4CFG = bmEP_DISABLE;
    sync_delay();
    // Disable end point 6.
    EP6CFG = bmEP_DISABLE;
    sync_delay();
    // Disable end point 8.
    EP8CFG = bmEP_DISABLE;
    sync_delay();

    // Reset all FIFOs.
    FIFORESET = bmNAKALL; // NAK all host transfers.
    sync_delay();
    FIFORESET = 0x00;
    sync_delay();

    // Enable dual autopointer(s).
    AUTOPTRSETUP |= bmAPTREN;
}
