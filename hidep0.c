#include "hid.h"
#include "core.h"
#include "usb.h"

static void ep0_get_dscr_proc(void)
{
    XDATA__ const BYTE *dscr_ptr = (XDATA__ BYTE *)hid_descriptor_ptr_get();
    if (dscr_ptr) {
        SUDPTRH = usb_word_msb_get(dscr_ptr);
        SUDPTRL = usb_word_lsb_get(dscr_ptr);
    } else {
         usb_ep0_stall();
    }
}

static void send_status(BYTE status)
{
    EP0BUF[0] = status;
    EP0BUF[1] = 0;
    EP0BCH = 0;
    EP0BCL = 2;
}

static void ep0_get_status_proc(void)
{
    switch (usb_setup_request_direction_get()) {

    case USB_SETUP_RD_DEVICE_TO_HOST: {
        switch (usb_setup_request_recipient_get()) {
        case USB_SETUP_RR_DEVICE: {
            const BOOL rwuen = usb_remote_wakeup_get();
            const BOOL selfpwr = usb_self_pwr_get();
            send_status(((BYTE)rwuen << 1) | (BYTE)selfpwr);
        }
            return;
        case USB_SETUP_RR_IFACE: // Reserved, return 0.
            send_status(0);
            return;
        case USB_SETUP_RR_EP: // Return endpoint status (unused?).
            send_status(0);
            return;
        default:
            break;
        }
    }
        break;

    default:
        break;
    }

    usb_ep0_stall();
}

static void ep0_standard_proc(void)
{
    switch (usb_setup_request_get()) {
    case USB_SETUP_RC_GET_DESCRIPTOR:
        ep0_get_dscr_proc();
        return;
    case USB_SETUP_RC_GET_INTERFACE:
        //          DR_GetInterface();
        break;
    case USB_SETUP_RC_SET_INTERFACE:
        //          DR_SetInterface();
        break;
    case USB_SETUP_RC_SET_CONFIGURATION:
        //          DR_SetConfiguration();
        break;
    case USB_SETUP_RC_GET_CONFIGURATION:
        //          DR_GetConfiguration();
        break;
    case USB_SETUP_RC_GET_STATUS:
        ep0_get_status_proc();
        return;
    default:
        break;
    }

    usb_ep0_stall();
}

void hid_ep0_proc(void)
{
    switch (usb_setup_request_type_get()) {
    case USB_SETUP_RT_STANDARD:
        ep0_standard_proc();
        break;
    case USB_SETUP_RT_CLASS:
    case USB_SETUP_RT_VENDOR:
    default:
        usb_ep0_stall();
        return;
    }

    // Acknowledge handshake phase of device request.
    EP0CS |= MSK_EP0CS_HSNAK;
}
