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
    USB_DESC_LANGID_STRING_INDEX = 0,
    USB_DESC_MFG_STRING_INDEX,
    USB_DESC_PRODUCT_STRING_INDEX,
    USB_DESC_SERIAL_STRING_INDEX
};

static const BYTE CODE g_device_desc[] = {
    0x12, // Descriptor length.
    USB_DESC_DEVICE, // Decriptor type.
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
    USB_DESC_MFG_STRING_INDEX,
    USB_DESC_PRODUCT_STRING_INDEX,
    USB_DESC_SERIAL_STRING_INDEX,
    0x01 // Configurations number.
};

static const BYTE CODE g_device_qual_desc[] = {
    0x0A, // Descriptor length.
    USB_DESC_DEVICE_QUALIFIER, // Decriptor type.
    usb_word_lsb_get(USB_SPEC_BCD_VERSION), // USB BCD version, lo.
    usb_word_msb_get(USB_SPEC_BCD_VERSION), // USB BCD version, hi.
    0x00, // Device class.
    0x00, // Device sub-class.
    0x00, // Device protocol.
    MAX_EP0_SIZE, // Maximum packet size (ep0 size).
    0x01, // Configurations number.
    0x00 // Reserved
};

static const BYTE CODE g_config_desc[] = {
    0
};

static const BYTE CODE g_other_config_desc[] = {
    0
};

static const BYTE CODE g_lang_id_desc[] = {
    0x04, // Descriptor length.
    USB_DESC_STRING, // Decriptor type.
    usb_word_lsb_get(USB_LANG_ID), // Language id, lo.
    usb_word_msb_get(USB_LANG_ID) // Language id, hi.
};

static const BYTE CODE g_manuf_str_desc[] = {
    0x0E, // Descriptor length.
    USB_DESC_STRING, // Decriptor type.
    'Q', 'B', 'S', ' ', 'e', 'x', 'a', 'm', 'p', 'l', 'e',
    0x00
};

static const BYTE CODE g_product_str_desc[] = {
    0x0F, // Descriptor length.
    USB_DESC_STRING, // Decriptor type.
    'N', 'E', 'S', ' ', 'G', 'a', 'm', 'e', 'P', 'a', 'd', 's',
    0x00
};

static const BYTE CODE g_serialno_str_desc[] = {
    0x0F, // Descriptor length.
    USB_DESC_STRING, // Decriptor type.
    '0' ,'1', '0', '2' , '0', '3', '0', '4', '0', '5', '0', '6',
    0x00
};

struct ep0_buf hid_ep0_desc_get(BYTE desc_type, BYTE target_index, BOOL hspeed)
{
    struct ep0_buf buf = {0};

    switch (desc_type) {

    case USB_DESC_DEVICE:
        buf.dat = g_device_desc;
        buf.len = sizeof(g_device_desc);
        break;

    case USB_DESC_CONFIGURATION:
        switch (target_index) {
        case 0: // Only one configuration.
            if (hspeed) {
                buf.dat = g_config_desc;
                buf.len = sizeof(g_config_desc);
            } else {
                buf.dat = g_other_config_desc;
                buf.len = sizeof(g_other_config_desc);
            }
            break;
        default: // Invalid configuration.
            break;
        }
        break;

    case USB_DESC_STRING:
        switch (target_index) {
        case USB_DESC_LANGID_STRING_INDEX:
            buf.dat = g_lang_id_desc;
            buf.len = sizeof(g_lang_id_desc);
            break;
        case USB_DESC_MFG_STRING_INDEX:
            buf.dat = g_manuf_str_desc;
            buf.len = sizeof(g_manuf_str_desc);
            break;
        case USB_DESC_PRODUCT_STRING_INDEX:
            buf.dat = g_product_str_desc;
            buf.len = sizeof(g_product_str_desc);
            break;
        case USB_DESC_SERIAL_STRING_INDEX:
            buf.dat = g_serialno_str_desc;
            buf.len = sizeof(g_serialno_str_desc);
            break;
        default: // Invalid string descriptor index.
            break;
        }
        break;

    case USB_DESC_DEVICE_QUALIFIER:
        buf.dat = g_device_qual_desc;
        buf.len = sizeof(g_device_qual_desc);
        break;

    case USB_DESC_OTHER_SPEED_CONFIGURATION:
        if (hspeed) {
            buf.dat = g_other_config_desc;
            buf.len = sizeof(g_other_config_desc);
        } else {
            buf.dat = g_config_desc;
            buf.len = sizeof(g_config_desc);
        }
        break;

    default: // Invalid descriptor type.
        break;
    }

    return buf;
}
