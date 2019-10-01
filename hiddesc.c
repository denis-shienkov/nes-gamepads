#include "usb.h"

enum usb_bcd_version {
    USB_SPEC_BCD_VERSION = 0x0200,
    USB_DEVICE_BCD_VERSION = 0x1234,
    USB_HID_BCD_VERSION = 0x0111
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

enum usb_descr_length {
    // Standard length.
    USB_DESC_DEVICE_LEN = 18,
    USB_DESC_DEVICE_QUAL_LEN = 10,
    USB_DESC_CONF_LEN = 9,
    USB_DESC_OTHER_SPEED_CONF_LEN = 9,
    USB_DESC_INTERFACE_LEN = 9,
    USB_DESC_HID_LEN = 9,
    USB_DESCR_HID_REP_LEN = 56,
    USB_DESC_ENDPOINT_LEN = 7,

    // Total length.
    USB_DESC_DEVICE_TOTAL_LEN = USB_DESC_DEVICE_LEN,
    USB_DESC_DEVICE_QUAL_TOTAL_LEN = USB_DESC_DEVICE_QUAL_LEN,

    USB_DESC_CONF_TOTAL_LEN = USB_DESC_CONF_LEN
        + USB_DESC_INTERFACE_LEN
        + USB_DESC_HID_LEN + USB_DESC_ENDPOINT_LEN,

    USB_DESC_OTHER_SPEED_CONF_TOTAL_LEN = USB_DESC_OTHER_SPEED_CONF_LEN
        + USB_DESC_INTERFACE_LEN,
};

enum usb_descr_attributes {
    USB_DESC_ATTRIBUTES = 0xC0, // Attributes (b7 - buspwr, b6 - selfpwr, b5 - rwu).
    USB_DESC_POWER_CONSUMPTION = 50 // 100 mA (div 2).
};

static const BYTE CODE
g_hid_report_desc[USB_DESCR_HID_REP_LEN] = {
    // Pad #1 configuration.
    0x05, 0x01, // Usage page (Generic Desktop).
    0x09, 0x05, // Usage (Game Pad).
    0xa1, 0x01, // Collection (Application).
    0xa1, 0x00, //   Collection (Physical).
    0x85, 0x01, //     Report id (1).
    0x05, 0x09, //     Usage page (Button).
    0x19, 0x01, //     Usage minimum (Button 1).
    0x29, 0x08, //     Usage maximum (Button 8).
    0x15, 0x00, //     Logical minimum (0).
    0x25, 0x01, //     Logical maximum (1).
    0x95, 0x08, //     Report count (8).
    0x75, 0x01, //     Report size (1).
    0x81, 0x02, //     Input (Data,Var,Abs).
    0xc0,       //   End collection.
    0xc0,       // End collection.
    // Pad #2 configuration.
    0x05, 0x01, // Usage page (Generic Desktop).
    0x09, 0x05, // Usage (Game Pad).
    0xa1, 0x01, // Collection (Application).
    0xa1, 0x00, //   Collection (Physical).
    0x85, 0x02, //     Report id (2).
    0x05, 0x09, //     Usage page (Button).
    0x19, 0x01, //     Usage minimum (Button 1).
    0x29, 0x08, //     Usage maximum (Button 8).
    0x15, 0x00, //     Logical minimum (0).
    0x25, 0x01, //     Logical maximum (1).
    0x95, 0x08, //     Report count (8).
    0x75, 0x01, //     Report size (1).
    0x81, 0x02, //     Input (Data,Var,Abs).
    0xc0,       //   End collection
    0xC0        // End collection.
};

static const BYTE CODE
g_device_desc[USB_DESC_DEVICE_TOTAL_LEN] = {
    USB_DESC_DEVICE_LEN, // Descriptor length.
    USB_DESC_DEVICE, // Descriptor type.
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

static const BYTE CODE
g_device_qual_desc[USB_DESC_DEVICE_QUAL_TOTAL_LEN] = {
    USB_DESC_DEVICE_QUAL_LEN, // Descriptor length.
    USB_DESC_DEVICE_QUAL, // Descriptor type.
    usb_word_lsb_get(USB_SPEC_BCD_VERSION), // USB BCD version, lo.
    usb_word_msb_get(USB_SPEC_BCD_VERSION), // USB BCD version, hi.
    0x00, // Device class.
    0x00, // Device sub-class.
    0x00, // Device protocol.
    MAX_EP0_SIZE, // Maximum packet size (ep0 size).
    0x01, // Configurations number.
    0x00 // Reserved
};

static const BYTE CODE
g_config_desc[USB_DESC_CONF_TOTAL_LEN] = {
    USB_DESC_CONF_LEN, // Descriptor length.
    USB_DESC_CONF, // Descriptor type.
    usb_word_lsb_get(USB_DESC_CONF_TOTAL_LEN), // Total length, lo.
    usb_word_msb_get(USB_DESC_CONF_TOTAL_LEN), // Total length, hi.
    0x01, // Interfaces number.
    0x01, // Configuration number.
    0x00, // Configuration string index.
    USB_DESC_ATTRIBUTES, // Attributes.
    USB_DESC_POWER_CONSUMPTION, // Power consumption.

    // Interface descriptor.
    USB_DESC_INTERFACE_LEN, // Descriptor length.
    USB_DESC_INTERFACE, // Descriptor type.
    0x00, // Zero-based index of this interfacce.
    0x00, // Alternate setting.
    0x01, // End points number (ep0 + ep1 in).
    0x03, // Class code (HID).
    0x00, // Subclass code (boot).
    0x00, // Protocol code (none).
    0x00, // Interface string descriptor index.

    // HID descriptor.
    USB_DESC_HID_LEN, // Descriptor length.
    USB_DESC_HID, // Descriptor type.
    usb_word_lsb_get(USB_HID_BCD_VERSION), // HID class BCD version, lo.
    usb_word_msb_get(USB_HID_BCD_VERSION), // HID class BCD version, hi.
    0x00, // Country code (HW country code).
    0x01, // Number of HID class descriptors to follow.
    USB_DESC_REPORT, // Repord descriptor type (HID).
    usb_word_lsb_get(USB_DESCR_HID_REP_LEN), // Report descriptor total length, lo.
    usb_word_lsb_get(USB_DESCR_HID_REP_LEN), // Report descriptor total length, hi.

    // End point descriptor.
    USB_DESC_ENDPOINT_LEN, // Descriptor length.
    USB_DESC_ENDPOINT, // Descriptor type.
    0x81, // End point address (ep1 in).
    0x03, // End point type (interrupt).
    usb_word_lsb_get(MAX_EP1_SIZE), // Maximum packet size, lo (ep1 size).
    usb_word_lsb_get(MAX_EP1_SIZE), // Maximum packet size, hi (ep1 size).
    0x01 // Polling interval (1 ms).
};

static const BYTE CODE
g_other_config_desc[USB_DESC_OTHER_SPEED_CONF_TOTAL_LEN] = {
    USB_DESC_OTHER_SPEED_CONF_LEN, // Descriptor length.
    USB_DESC_OTHER_SPEED_CONF, // Descriptor type.
    usb_word_lsb_get(USB_DESC_OTHER_SPEED_CONF_TOTAL_LEN), // Total length, lo.
    usb_word_msb_get(USB_DESC_OTHER_SPEED_CONF_TOTAL_LEN), // Total length, hi.
    0x01, // Interfaces number.
    0x01, // Configuration number.
    0x00, // Configuration string index.
    USB_DESC_ATTRIBUTES, // Attributes.
    USB_DESC_POWER_CONSUMPTION, // Power consumption.

    // Interface descriptor.
    USB_DESC_INTERFACE_LEN, // Descriptor length.
    USB_DESC_INTERFACE, // Descriptor type.
    0x00, // Zero-based index of this interfacce.
    0x00, // Alternate setting.
    0x00, // End points number (only ep0).
    0x00, // Class code.
    0x00, // Subclass code.USB_DESC_OTHER_SPEED_CONFIGURATION
    0x00, // Protocol code.
    0x00 // Interface string descriptor index.
};

static const BYTE CODE
g_lang_id_desc[] = {
    0x04, // Descriptor length.
    USB_DESC_STRING, // Descriptor type.
    usb_word_lsb_get(USB_LANG_ID), // Language id, lo.
    usb_word_msb_get(USB_LANG_ID) // Language id, hi.
};

static const BYTE CODE
g_manuf_str_desc[] = {
    0x0E, // Descriptor length.
    USB_DESC_STRING, // Descriptor type.
    'Q', 'B', 'S', ' ', 'e', 'x', 'a', 'm', 'p', 'l', 'e',
    0x00
};

static const BYTE CODE
g_product_str_desc[] = {
    0x0F, // Descriptor length.
    USB_DESC_STRING, // Descriptor type.
    'N', 'E', 'S', ' ', 'G', 'a', 'm', 'e', 'P', 'a', 'd', 's',
    0x00
};

static const BYTE CODE
g_serialno_str_desc[] = {
    0x0F, // Descriptor length.
    USB_DESC_STRING, // Descriptor type.
    '0' ,'1', '0', '2' , '0', '3', '0', '4', '0', '5', '0', '6',
    0x00
};

BYTE *hid_ep0_desc_get(void)
{
    switch (SETUPDAT[3]) {

    case USB_DESC_DEVICE:
        return g_device_desc;

    case USB_DESC_CONF:
        if (SETUPDAT[2] == 0)
            return usb_is_high_speed() ? g_config_desc
                                       : g_other_config_desc;
        break;

    case USB_DESC_STRING:
        switch (SETUPDAT[2]) {
        case USB_DESC_LANGID_STRING_INDEX:
            return g_lang_id_desc;
        case USB_DESC_MFG_STRING_INDEX:
            return g_manuf_str_desc;
        case USB_DESC_PRODUCT_STRING_INDEX:
            return g_product_str_desc;
        case USB_DESC_SERIAL_STRING_INDEX:
            return g_serialno_str_desc;
        default:
            break;
        }
        break;

    case USB_DESC_DEVICE_QUAL:
        return g_device_qual_desc;

    case USB_DESC_OTHER_SPEED_CONF:
        return usb_is_high_speed() ? g_other_config_desc
                                   : g_config_desc;

    case USB_DESC_HID:
        return &g_config_desc[USB_DESC_CONF_LEN + USB_DESC_INTERFACE_LEN];

    case USB_DESC_REPORT:
        return g_hid_report_desc;

    default:
        break;
    }

    return NULL;
}
