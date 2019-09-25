#include "fx2hid.h"
#include "fx2hw.h"
#include "fx2usb.h"

void hid_init(void)
{
    // Disable end point 1 output.
    usb_ep_disable(EP1OUTCFG);
    sync_delay();

    // Enable end point 1 as input interrupt mode.
    usb_ep_enable(EP1INCFG);
    sync_delay();
    usb_ep_type_set(EP1INCFG, EP_TYPE_INTERRUPT);
    sync_delay();

    // Enable end point 2 as input interrupt mode
    // with 512 bytes size and quad buffering.
    usb_ep_enable(EP2CFG);
    sync_delay();
    usb_ep_dir_set(EP2CFG, EP_DIR_IN);
    sync_delay();
    usb_ep_type_set(EP2CFG, EP_TYPE_INTERRUPT);
    sync_delay();
    usb_ep_size_set(EP2CFG, EP_SIZE_512);
    sync_delay();
    usb_ep_buf_set(EP2CFG, EP_BUF_QUAD);
    sync_delay();

    // Enable end point 6 as output bulk mode
    // with 512 bytes size and double buffering.
    usb_ep_enable(EP6CFG);
    sync_delay();
    usb_ep_dir_set(EP6CFG, EP_DIR_OUT);
    sync_delay();
    usb_ep_type_set(EP6CFG, EP_TYPE_BULK);
    sync_delay();
    usb_ep_size_set(EP6CFG, EP_SIZE_512);
    sync_delay();
    usb_ep_buf_set(EP6CFG, EP_BUF_DOUBLE);
    sync_delay();

    // Enable end point 8 as input bulk mode
    // with 512 bytes size and double buffering.
    usb_ep_enable(EP8CFG);
    sync_delay();
    usb_ep_dir_set(EP8CFG, EP_DIR_IN);
    sync_delay();
    usb_ep_type_set(EP8CFG, EP_TYPE_BULK);
    sync_delay();
    usb_ep_size_set(EP8CFG, EP_SIZE_512);
    sync_delay();
    usb_ep_buf_set(EP8CFG, EP_BUF_DOUBLE);
    sync_delay();

    // Arm EP6OUT by writing byte count w/skip.
    EP6BCL = 0x80;
    sync_delay();
    EP6BCL = 0x80;
    sync_delay();

    // Reset all FIFOs.
    FIFORESET = MSK_FIFORESET_NAKALL; // NAK all host transfers.
    sync_delay();
    FIFORESET = 0x00;
    sync_delay();

    // Enable dual autopointer feature.
    AUTOPTRSETUP |= MSK_AUTOPTRSETUP_APTREN;
}
