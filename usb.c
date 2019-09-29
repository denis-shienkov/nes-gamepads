#include "core.h"
#include "hid.h"
#include "usb.h"

void usb_init(void)
{
    // Disable all USB interrupts.
    USBIE = 0;
    // Disable all end point interrupts.
    EPIE = 0;
    // Disable all end point ping-nak interrupts.
    NAKIE = 0;
    // Disable all USB error interrupts.
    USBERRIE = 0;
    // Enable USB interrupt 2 autovectoring.
    INTSETUP |= bmAV2EN;
    // Clear USB interrupt requests.
    USBIRQ = bmSUDAV | bmSOF | bmSUTOK | bmSUSP | bmURES | bmHSGRANT | bmEP0ACK;
    // Clear end point interrupt requests.
    EPIRQ  = 0xff;
    // Handle only SOF interrupt directly.
    USBIE = bmSOF;
    // Set USB interrupt to high priority.
    PUSB = 1;
    // Enable USB interrupts.
    EUSB = 1;
    // As we use SOFs to detect disconnect we have
    // to disable SOF synthesizing.
    USBCS |= bmNOSYNSOF;

    hid_ep_init();

    // Set the RENUM to disable FX2-internal enumeration support.
    USBCS |= bmRENUM;
}

void usb_task(void)
{
    if ((USBIRQ & bmSUDAV) != 0) {
        USBIRQ = bmSUDAV;
        // Setup packet available.
        hid_ep0_proc();
    }

    if ((USBIRQ & bmEP0ACK) != 0) {
        // Status stage completed.
        USBIRQ = bmEP0ACK;
    }

    if ((USBIRQ & bmURES) != 0) {
        USBIRQ = bmURES;
        // TODO: Implement reset handler.
    }

    if ((USBIRQ & bmSUSP) != 0 ) {
        USBIRQ = bmSUSP;
    }

    if ((EPIRQ & bmEP0IN) != 0) {
        // Host has taken a packet from the end point.
        EPIRQ = bmEP0IN;
        // This will arm the end point.
        ///UsbEp0InHandler();
    }

    if ((EPIRQ & bmEP0OUT) != 0) {
        // Host has placed a packet to the end point.
        EPIRQ = bmEP0OUT;
        // This will arm the end point.
        ///UsbEp0OutHandler();
    }

    // Process data end points.
    hid_stream_proc();
}

void usb_sof_isr(void)
{
    // Clear interrupt request.
    EXIF &= ~bmUSBNT;
    USBIRQ = bmSOF;
}

void usb_stub_isr(void)
{

}
