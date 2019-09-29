#include "usb.h"

enum usb_bcd_version {
    USB_SPEC_BCD_VERSION = 0x0200,
    USB_DEVICE_BCD_VERSION = 0x1234
};

enum usb_ids {
    USB_DEVICE_VID = 0xFFFF,
    USB_DEVICE_PID = 0xFFFF
};

enum usb_lang_id {
    USB_LANG_ID = 0x0409
};

enum usb_descriptor_string_index {
    USB_DSCR_LANGID_STRING_INDEX = 0,
    USB_DSCR_MFG_STRING_INDEX,
    USB_DSCR_PRODUCT_STRING_INDEX,
    USB_DSCR_SERIAL_STRING_INDEX
};

static const BYTE CODE g_device_dscr[] = {
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

static const BYTE CODE g_device_qual_dscr[] = {
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

static const BYTE CODE g_config_dscr[] = {
    0
};

static const BYTE CODE g_other_config_dscr[] = {
    0
};

static const BYTE CODE g_lang_id_dscr[] = {
    0x04, // Descriptor length.
    USB_DSCR_TYPE_STRING, // Decriptor type.
    usb_word_lsb_get(USB_LANG_ID), // Language id, lo.
    usb_word_msb_get(USB_LANG_ID) // Language id, hi.
};

static const BYTE CODE g_manuf_str_dscr[] = {
    0x0E, // Descriptor length.
    USB_DSCR_TYPE_STRING, // Decriptor type.
    'Q', 'B', 'S', ' ', 'e', 'x', 'a', 'm', 'p', 'l', 'e',
    0x00
};

static const BYTE CODE g_product_str_dscr[] = {
    0x0F, // Descriptor length.
    USB_DSCR_TYPE_STRING, // Decriptor type.
    'N', 'E', 'S', ' ', 'G', 'a', 'm', 'e', 'P', 'a', 'd', 's',
    0x00
};

static const BYTE CODE g_serialno_str_dscr[] = {
    0x0F, // Descriptor length.
    USB_DSCR_TYPE_STRING, // Decriptor type.
    '0' ,'1', '0', '2' , '0', '3', '0', '4', '0', '5', '0', '6',
    0x00
};

BYTE *hid_descriptor_ptr_get(void)
{
    switch (usb_setup_wvalueh_get()) {
    case USB_SETUP_GD_DEVICE:
        return (BYTE *)g_device_dscr;
    case USB_SETUP_GD_DEVICE_QUALIFIER:
        return (BYTE *)(usb_is_high_speed()
                ? g_device_qual_dscr : NULL);
    case USB_SETUP_GD_CONFIGURATION:
        return (BYTE *)g_config_dscr;
    case USB_SETUP_GD_OTHER_SPEED_CONFIGURATION:
        return (BYTE *)g_other_config_dscr;
    case USB_SETUP_GD_STRING:
        switch (usb_setup_wvaluel_get()) {
        case USB_DSCR_LANGID_STRING_INDEX:
            return (BYTE *)g_lang_id_dscr;
        case USB_DSCR_MFG_STRING_INDEX:
            return (BYTE *)g_manuf_str_dscr;
        case USB_DSCR_PRODUCT_STRING_INDEX:
            return (BYTE *)g_product_str_dscr;
        case USB_DSCR_SERIAL_STRING_INDEX:
            return (BYTE *)g_serialno_str_dscr;
        default:
            break;
        }
    default:
        break;
    }
    return NULL;
}
