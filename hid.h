#ifndef FX2_HID_H
#define FX2_HID_H

#include "usb.h"

#ifdef __cplusplus
extern "C" {
#endif

void hid_ep_init(void);

void hid_ep0_init(void);
void hid_ep0_setup_proc(void);
void hid_ep0_in_proc(void);
void hid_ep0_out_proc(void);

struct ep0_buf hid_ep0_desc_get(BYTE desc_type, BYTE target_index,
                                BOOL hspeed);

#ifdef __cplusplus
}
#endif

#endif // FX2_HID_H
