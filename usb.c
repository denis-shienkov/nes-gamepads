#include "core.h"
#include "hid.h"
#include "usb.h"

void usb_init(void)
{
    // Disable all USB interrupts.
    USBIE = 0;
    sync_delay();
    // Disable all end point interrupts.
    EPIE = 0;
    sync_delay();
    // Disable all end point ping-nak interrupts.
    NAKIE = 0;
    sync_delay();
    // Disable all USB error interrupts.
    USBERRIE = 0;
    sync_delay();
    // Disable USB && GPIF autovectoring.
    INTSETUP = 0;
    sync_delay();
    // Clear USB interrupt requests.
    USBIRQ = bmSUDAV | bmSOF | bmSUTOK | bmSUSP
            | bmURES | bmHSGRANT | bmEP0ACK;
    sync_delay();
    // Clear end point interrupt requests.
    EPIRQ = bmEP0IN | bmEP0OUT | bmEP1IN | bmEP1OUT
            | bmEP2 | bmEP4 | bmEP6 | bmEP8;
    sync_delay();
    // Set USB interrupt to high priority.
    PUSB = 1;
    sync_delay();
    // Enable USB interrupts.
    EUSB = 1;
    sync_delay();
    // As we use SOFs to detect disconnect we have
    // to disable SOF synthesizing.
    USBCS |= bmNOSYNSOF;
    sync_delay();

    hid_init();

    // Disable FX2-internal enumeration support.
    USBCS |= bmRENUM;
    sync_delay();
}

void usb_task(void)
{
    if (USBIRQ & bmSUDAV) {
        USBIRQ = bmSUDAV;
        hid_ep0_setup_task();
    }

    if (USBIRQ & bmEP0ACK) {
        USBIRQ = bmEP0ACK;
    }

    if (USBIRQ & bmURES) {
        USBIRQ = bmURES;
    }

    if (USBIRQ & bmSUSP) {
        USBIRQ = bmSUSP;
    }

    hid_ep1_task();
}
