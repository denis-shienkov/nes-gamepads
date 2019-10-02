#ifndef FX2_HID_H
#define FX2_HID_H

#include "usb.h"

#ifdef __cplusplus
extern "C" {
#endif

enum hid_constants {
    HID_CONFIG_NUMBER = 1, // Number of valid configuration.
    HID_IFACE_NUMBER = 0, // Number of valid interface.
    HID_ALT_IFACE_NUMBER = 0, // Number of valid alternate interface.
    HID_EP_IN = 0x81 // Active end point address.
};

void hid_init(void);
void hid_reset(void);

void hid_ep0_init(void);
void hid_ep0_setup_proc(void);
BYTE *hid_ep0_desc_get(void);

#ifdef __cplusplus
}
#endif

#endif // FX2_HID_H
