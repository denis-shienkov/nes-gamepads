#ifndef FX2_HID_H
#define FX2_HID_H

#ifdef __cplusplus
extern "C" {
#endif

void hid_init(void);
void hid_ep0setup_proc(void);
void hid_stream_proc(void);

#ifdef __cplusplus
}
#endif

#endif // FX2_HID_H
