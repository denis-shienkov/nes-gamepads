#include "fx2usb.h"

//#define USBD_LANGID_STRING     1033
//#define USBD_MANUFACTURER_STRING     "STMicroelectronics"
//#define USBD_PRODUCT_STRING_FS     "NES GamePads"
//#define USBD_SERIALNUMBER_STRING_FS     "010203040506"

enum usb_bcd_version {
    USB_SPEC_BCD_VERSION = 0x0200,
    USB_DEVICE_BCD_VERSION = 0x1234
};

enum usb_ids {
    USB_DEVICE_VID = 0xFFFF,
    USB_DEVICE_PID = 0xFFFF
};

enum usb_descriptor_string_index {
    USB_DSCR_LANGID_STRING_INDEX = 0,
    USB_DSCR_MFG_STRING_INDEX,
    USB_DSCR_PRODUCT_STRING_INDEX,
    USB_DSCR_SERIAL_STRING_INDEX
};

static const BYTE code g_device_dscr[] = {
    0x12, // Descriptor length.
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
    0x01 // Configurations number.
};

static const BYTE code g_device_qual_dscr[] = {
    0x0A, // Descriptor length.
    USB_DSCR_TYPE_DEVQUAL, // Decriptor type.
    usb_word_lsb_get(USB_SPEC_BCD_VERSION), // USB BCD version, lo.
    usb_word_msb_get(USB_SPEC_BCD_VERSION), // USB BCD version, hi.
    0x00, // Device class.
    0x00, // Device sub-class.
    0x00, // Device protocol.
    MAX_EP0_SIZE, // Maximum packet size (ep0 size).
    0x01, // Configurations number.
    0x00 // Reserved
};

static const BYTE code g_config_dscr[] = {
    0
};

static const BYTE code g_other_config_dscr[] = {
    0
};

BYTE *hid_descriptor_ptr_get(void)
{
    switch (usb_setup_wvalueh_get()) {
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
        break;
    }
    return NULL;
}
