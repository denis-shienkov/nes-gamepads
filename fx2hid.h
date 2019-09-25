#ifndef FX2_HID_H
#define FX2_HID_H

#include "fx2defs.h"

#ifdef __cplusplus
extern "C" {
#endif

void hid_init(void);
void hid_ep0_proc(void);
void hid_stream_proc(void);

BYTE *hid_descriptor_ptr_get(void);

#ifdef __cplusplus
}
#endif

#endif // FX2_HID_H
