#ifndef FX2_USB_H
#define FX2_USB_H

#include "regs.h"

#ifdef __cplusplus
extern "C" {
#endif

// Setup request direction.
enum usb_setup_req_direction {
    USB_SETUP_RD_HOST_TO_DEVICE = 0x00, // From host to sevice direction.
    USB_SETUP_RD_DEVICE_TO_HOST = 0x01 // From device to host direction.
};

// Setup request type.
enum usb_setup_req_type {
    USB_SETUP_RT_STANDARD = 0x00, // Standard request.
    USB_SETUP_RT_CLASS = 0x01, // Class request.
    USB_SETUP_RT_VENDOR = 0x02, // Vendor request.
    USB_SETUP_RT_RESERVED = 0x03 // Reserved or illegal request.
};

// Setup request recipient.
enum usb_setup_req_recipient {
    USB_SETUP_RR_DEVICE = 0x00, // Device recipient.
    USB_SETUP_RR_IFACE = 0x01, // Interface recipient.
    USB_SETUP_RR_EP = 0x02, // End point recipient.
    USB_SETUP_RR_OTHER = 0x03 // Other recipient.
};

// Setup request code.
enum usb_setup_req_code {
    USB_SETUP_RC_GET_STATUS = 0x00, // Get status code.
    USB_SETUP_RC_CLEAR_FEATURE = 0x01, // Clear feature code.
    USB_SETUP_RC_RESERVED1 = 0x02, // Reserved code.
    USB_SETUP_RC_SET_FEATURE = 0x03, // Set feature code.
    USB_SETUP_RC_RESERVED2 = 0x04, // Reserved code.
    USB_SETUP_RC_SET_ADDRESS = 0x05, // Set address code.
    USB_SETUP_RC_GET_DESCRIPTOR = 0x06, // Get descriptor code.
    USB_SETUP_RC_SET_DESCRIPTOR = 0x07, // Set descriptor code.
    USB_SETUP_RC_GET_CONFIGURATION = 0x08, // Get configuration code.
    USB_SETUP_RC_SET_CONFIGURATION = 0x09, // Set configuration code.
    USB_SETUP_RC_GET_INTERFACE = 0x0A, // Get interface code.
    USB_SETUP_RC_SET_INTERFACE = 0x0B, // Set interface code.
    USB_SETUP_RC_SYNC_FRAME = 0x0C, // Sync frame code.
    USB_SETUP_RC_ANCHOR_LOAD = 0xA0 // Anchor load code.
};

// Get descriptor codes.
enum usb_setup_get_descriptor_code {
    USB_SETUP_GD_DEVICE = 0x01, // Get device descriptor.
    USB_SETUP_GD_CONFIGURATION = 0x02, // Get configuration descriptor.
    USB_SETUP_GD_STRING = 0x03, // Get string descriptor.
    USB_SETUP_GD_INTERFACE = 0x04, // Get interface descriptor.
    USB_SETUP_GD_ENDPOINT = 0x05, // Get endpoint descriptor.
    USB_SETUP_GD_DEVICE_QUALIFIER = 0x06, // Get device qualifier descriptor.
    USB_SETUP_GD_OTHER_SPEED_CONFIGURATION = 0x07, // Get other configuration descriptor.
    USB_SETUP_GD_INTERFACE_POWER = 0x08, // Get interface power descriptor.
    USB_SETUP_GD_HID = 0x21, // Get HID descriptor.
    USB_SETUP_GD_REPORT = 0x22 // Get report descriptor.
};

//#define FT_DEVICE          0x00  // Feature: Device
//#define FT_ENDPOINT        0x02  // Feature: End Point

// Descriptor type.
enum usb_descriptor_type {
    USB_DSCR_TYPE_DEVICE = 0x01, // Standard device descriptor.
    USB_DSCR_TYPE_CONFIG = 0x02, // Standard configuration descriptor.
    USB_DSCR_TYPE_STRING = 0x03, // String descriptor.
    USB_DSCR_TYPE_INTERFACE = 0x04, // Standard interface descriptor.
    USB_DSCR_TYPE_ENDPOINT = 0x05, // Standard endpoint descriptor.
    USB_DSCR_TYPE_DEVQUAL = 0x06, // Device qualifier descriptor.
    USB_DSCR_TYPE_OTHERSPEED = 0x07, // Other speed configuration descriptor.
    USB_DSCR_TYPE_IFACEPOWER = 0x08,
    USB_DSCR_TYPE_OTG = 0x09,
    USB_DSCR_TYPE_DEBUG = 0x0A,
    USB_DSCR_TYPE_IFACEASSOC = 0x0B // Interface Association descriptor.
};

// End point configuration (EP1INCFG/EP1OUTCFG/EP2/EP4/EP6/EP8).
enum epcfg_bits {
    MSK_EPCFG_VALID = MSK_BIT7,
    MSK_EPCFG_DIR = MSK_BIT6, // Only for EP2-EP8!
    MSK_EPCFG_TYPE = MSK_BIT5 | MSK_BIT4,
    MSK_EPCFG_SIZE = MSK_BIT3, // Only for EP2-EP8!
    MSK_EPCFG_BUF = MSK_BIT1 | MSK_BIT0 // Only for EP2-EP8!
};

// Only for EP2-EP8!
enum ep_direction {
    EP_DIR_OUT = 0,
    EP_DIR_IN = 1
};

enum ep_type {
    EP_TYPE_INVALID = 0,
    EP_TYPE_ISOCHRONOUS = 1, // Only for EP2-EP8!
    EP_TYPE_BULK = 2, // Default value.
    EP_TYPE_INTERRUPT = 3
};

// Only for EP2-EP8!
enum ep_size {
    EP_SIZE_512 = 0,
    EP_SIZE_1024 = 1 // Except EP4/EP8.
};

// Only for EP2-EP8!
enum ep_buf {
    EP_BUF_QUAD = 0,
    EP_BUF_INVALID = 1,
    EP_BUF_DOUBLE = 2, // Default value.
    EP_BUF_TRIPLE = 3
};

// USB irq control macros.
#define usb_irq_enable() (EUSB = 1)
#define usb_irq_disable() (EUSB = 0)
#define usb_irq_clear() (EXIF &= ~bmUSBNT)

// USB power control macros.
#define usb_rsmirq_enable() (EICON |= bmERESI)
#define usb_rsmirq_disable() (EICON &= ~bmERESI)
#define usb_rsmirq_clear() (EICON &= ~bmRESI)

#define usb_is_ext_wakeup() \
    (((WAKEUPCS & bmWU2) && (WAKEUPCS & bmWU2EN)) \
    || ((WAKEUPCS & bmWU) && (WAKEUPCS & bmWUEN)))

#define usb_ep0_stall() \
    EP0CS |= bmEPSTALL

#define usb_ep_enable(ep) \
    ep |= MSK_EPCFG_VALID

#define usb_ep_disable(ep) \
    ep &= ~MSK_EPCFG_VALID

#define usb_ep_dir_set(ep, dir) \
    ep = ((ep & ~MSK_EPCFG_DIR) | (dir << 6))

#define usb_ep_type_set(ep, type) \
    ep = ((ep & ~MSK_EPCFG_TYPE) | (type << 4))

#define usb_ep_size_set(ep, size) \
    ep = ((ep & ~MSK_EPCFG_DIR) | (size << 3))

#define usb_ep_buf_set(ep, buf) \
    ep = ((ep & ~MSK_EPCFG_BUF) | (buf << 0))

#define usb_word_msb_get(word) \
    (BYTE)(((WORD)(word) >> 8) & 0xFF)
#define usb_word_lsb_get(word) \
    (BYTE)((WORD)(word) & 0xFF)

#define usb_word_swap(x) \
    ((((WORD)((x) & 0x00FF)) << 8) | \
    (((WORD)((x) & 0xFF00)) >> 8))

#define usb_dword_swap(x) \
    ((((DWORD)((x) & 0x000000FFul)) << 24) | \
    (((DWORD)((x) & 0x0000FF00ul)) << 8) | \
    (((DWORD)((x) & 0x00FF0000ul)) >> 8) | \
    (((DWORD)((x) & 0xFF000000ul)) >> 24))

// Macros to parse the FX2 SETUPDAT registers.
#define usb_setup_type_get() (SETUPDAT[0]) // bmRequestType.
#define usb_setup_request_direction_get() ((SETUPDAT[0] >> 0x07) & 0x01)
#define usb_setup_request_type_get() ((SETUPDAT[0] >> 0x05) & 0x03)
#define usb_setup_request_recipient_get() (SETUPDAT[0] & 0x1F)
#define usb_setup_request_get() (SETUPDAT[1]) // bRequest.
#define usb_setup_wvaluel_get() (SETUPDAT[2]) // wValueL.
#define usb_setup_wvalueh_get() (SETUPDAT[3]) // wValueH.
#define usb_setup_windexl_get() (SETUPDAT[4]) // wIndexL.
#define usb_setup_windexh_get() (SETUPDAT[5]) // wIndexH.
#define usb_setup_value_get() (usb_word_swap(*(WORD*)&SETUPDAT[2])) // wValue.
#define usb_setup_index_get() (usb_word_swap(*(WORD*)&SETUPDAT[4])) // wIndex.
#define usb_setup_data_length_get() (usb_word_swap(*(WORD*)&SETUPDAT[6])) // wLength.

void usb_init(void);
void usb_task(void);
//void usb_remote_wakeup_set(BOOL set);
BOOL usb_remote_wakeup_get(void);
BOOL usb_self_pwr_get(void);
BOOL usb_is_hispeed_supported(void);

#ifdef __cplusplus
}
#endif

#endif // FX2_USB_H
