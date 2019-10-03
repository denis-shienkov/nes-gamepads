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

enum hid_gamepad_id {
    HID_REPORT_ID_GAMEPAD1 = 1,
    HID_REPORT_ID_GAMEPAD2 = 2
};

enum { HID_REPORTS_COUNT = 2 };

void hid_init(void);

void hid_ep0_init(void);
void hid_ep0_setup_task(void);

BYTE *hid_ep0_std_desc_get(void);
BYTE *hid_ep0_report_desc_get(WORD *length);

void hid_ep1_task(void);
void hid_ep1_report_update(BYTE index, BYTE buttons);

#ifdef __cplusplus
}
#endif

#endif // FX2_HID_H
