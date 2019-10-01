#ifndef FX2_HID_H
#define FX2_HID_H

#include "usb.h"

#ifdef __cplusplus
extern "C" {
#endif

void hid_ep_init(void);

void hid_ep0_init(void);
void hid_ep0_setup_proc(void);
BYTE *hid_ep0_desc_get(void);

#ifdef __cplusplus
}
#endif

#endif // FX2_HID_H
