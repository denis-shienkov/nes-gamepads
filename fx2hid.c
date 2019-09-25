#include "fx2hid.h"
#include "fx2hw.h"
#include "fx2usb.h"

#define USBD_LANGID_STRING     1033
#define USBD_MANUFACTURER_STRING     "STMicroelectronics"
#define USBD_PRODUCT_STRING_FS     "NES GamePads"
#define USBD_SERIALNUMBER_STRING_FS     "010203040506"

enum usb_descriptor_length {
    USB_DEVICE_DSCR_LENGTH = 0x12,
    USB_DEVQUAL_DSCR_LEN = 0x0A,
};

enum usb_bcd_version {
    USB_SPEC_BCD_VERSION = 0x0200,
    USB_DEVICE_BCD_VERSION = 0x1234
};

enum usb_ids {
    USB_DEVICE_VID = 0xFFFF,
    USB_DEVICE_PID = 0xFFFF
};

enum usb_configuration_number {
    USB_MAX_NUM_CONFIGURATION = 1
};

enum usb_descriptor_string_index {
    USB_DSCR_LANGID_STRING_INDEX = 0,
    USB_DSCR_MFG_STRING_INDEX,
    USB_DSCR_PRODUCT_STRING_INDEX,
    USB_DSCR_SERIAL_STRING_INDEX
};

static const BYTE code g_device_dscr[USB_DEVICE_DSCR_LENGTH] = {
    USB_DEVICE_DSCR_LENGTH, // Descriptor length.
    USB_DSCR_TYPE_DEVICE, // Decriptor type.
    usb_word_lsb_get(USB_SPEC_BCD_VERSION), // USB BCD version, lo.
    usb_word_msb_get(USB_SPEC_BCD_VERSION), // USB BCD version, hi.
    0x00, // Device class.
    0x00, // Device sub-class.
    0x00, // Device protocol.
    MAX_EP0_SIZE, // Maximum packet size (ep0 size).
    usb_word_lsb_get(USB_DEVICE_VID), // Vendor ID, lo.
    usb_word_msb_get(USB_DEVICE_VID), // Vendor ID, hi.
    usb_word_lsb_get(USB_DEVICE_PID), // Product ID, lo.
    usb_word_msb_get(USB_DEVICE_PID), // Product ID, hi.
    usb_word_lsb_get(USB_DEVICE_BCD_VERSION), // Device BCD version, lo.
    usb_word_msb_get(USB_DEVICE_BCD_VERSION), // Device BCD version, hi.
    USB_DSCR_MFG_STRING_INDEX,
    USB_DSCR_PRODUCT_STRING_INDEX,
    USB_DSCR_SERIAL_STRING_INDEX,
    USB_MAX_NUM_CONFIGURATION
};

static const BYTE code g_device_qual_dscr[USB_DEVQUAL_DSCR_LEN] = {
    USB_DEVQUAL_DSCR_LEN, // Descriptor length.
    USB_DSCR_TYPE_DEVQUAL, // Decriptor type.
    usb_word_lsb_get(USB_SPEC_BCD_VERSION), // USB BCD version, lo.
    usb_word_msb_get(USB_SPEC_BCD_VERSION), // USB BCD version, hi.
    0x00, // Device class.
    0x00, // Device sub-class.
    0x00, // Device protocol.
    MAX_EP0_SIZE, // Maximum packet size (ep0 size).
    USB_MAX_NUM_CONFIGURATION,
    0x00 // Reserved
};

static const BYTE code g_config_dscr[1] = {
    0
};

static const BYTE code g_other_config_dscr[1] = {
    0
};

static BYTE xdata *dscr_pointer_get(BYTE dscr_code)
{
    switch (dscr_code) {
    case USB_SETUP_GD_DEVICE:
        return g_device_dscr;
    case USB_SETUP_GD_DEVICE_QUALIFIER:
        return usb_is_hispeed_supported()
                ? g_device_qual_dscr : NULL;
    case USB_SETUP_GD_CONFIGURATION:
        return g_config_dscr;
    case USB_SETUP_GD_OTHER_SPEED_CONFIGURATION:
        return g_other_config_dscr;
    case USB_SETUP_GD_STRING:
        //        if(dscr_ptr = (void *)EZUSB_GetStringDscr(SETUPDAT[2])) {
        //            SUDPTRH = usb_word_msb_get(dscr_ptr);
        //            SUDPTRL = usb_word_lsb_get(dscr_ptr);
        //        } else {
        //            usb_ep0_stall();
        //        }
        return NULL; // Implement me!
    default:
        return NULL;
    }
}

static void ep0setup_get_dscr_proc(void)
{
    const BYTE xdata *dscr_ptr = dscr_pointer_get(usb_setup_wvalueh_get());
    if (dscr_ptr) {
        SUDPTRH = usb_word_msb_get(dscr_ptr);
        SUDPTRL = usb_word_lsb_get(dscr_ptr);
    } else {
         usb_ep0_stall();
    }
}

static void ep0setup_get_status_proc(void)
{
    const BYTE req_dir = usb_setup_request_direction_get();
    if (req_dir == USB_SETUP_RD_DEVICE_TO_HOST) {
        const BYTE req_recip = usb_setup_request_recipient_get();
        switch (req_recip) {
        case USB_SETUP_RR_DEVICE: {
            const BOOL rwuen = usb_remote_wakeup_get();
            const BOOL selfpwr = usb_self_pwr_get();
            EP0BUF[0] = ((BYTE)rwuen << 1) | (BYTE)selfpwr;
            EP0BUF[1] = 0;
            EP0BCH = 0;
            EP0BCL = 2;
        }
            return;
        case USB_SETUP_RR_IFACE: // Reserved, return 0.
            EP0BUF[0] = 0;
            EP0BUF[1] = 0;
            EP0BCH = 0;
            EP0BCL = 2;
            return;
        case USB_SETUP_RR_EP: // Return endpoint status (unused?).
            EP0BUF[0] = 0;
            EP0BUF[1] = 0;
            EP0BCH = 0;
            EP0BCL = 2;
            return;
        default:
            break;
        }
    }

    usb_ep0_stall();
}

static void ep0setup_standard_proc(void)
{
    const BYTE req_code = usb_setup_request_get();
    switch (req_code) {
    case USB_SETUP_RC_GET_DESCRIPTOR:
        ep0setup_get_dscr_proc();
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
        ep0setup_get_status_proc();
        return;
    default:
        break;
    }

    usb_ep0_stall();
}

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

void hid_ep0setup_proc(void)
{
    const BYTE req_type = usb_setup_request_type_get();
    switch (req_type) {
    case USB_SETUP_RT_STANDARD:
        ep0setup_standard_proc();
        break;
    case USB_SETUP_RT_CLASS:
    case USB_SETUP_RT_VENDOR:
    default:
        usb_ep0_stall();
        break;
    }

    // Acknowledge handshake phase of device request.
    EP0CS |= MSK_EP0CS_HSNAK;
}

void hid_stream_proc(void)
{
}
