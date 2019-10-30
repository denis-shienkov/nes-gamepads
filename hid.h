#ifndef MSP430_HID_H
#define MSP430_HID_H

#include <stdbool.h>
#include <stdint.h>

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

enum {
    HID_REPORTS_COUNT = 2,
    HID_REPORT_BITS_COUNT = 8
};

void hid_ep0_init(void);

// Called only in interrupt context.
void hid_ep0_setup_handler(void);
void hid_ep0_in_handler(void);

void hid_ep0_in_nak(void);
void hid_ep0_in_stall(void);
void hid_ep0_in_clear(void);
bool hid_ep0_in_is_stalled(void);

void hid_ep0_out_nak(void);
void hid_ep0_out_stall(void);
void hid_ep0_out_clear(void);

const uint8_t *hid_ep0_desc_get(uint8_t type, uint16_t *length);

uint8_t hid_ep0_setup_bm_request_type_get(void);
uint8_t hid_ep0_setup_request_get(void);
uint8_t hid_ep0_setup_lvalue_get(void);
uint8_t hid_ep0_setup_hvalue_get(void);
uint8_t hid_ep0_setup_lindex_get(void);
uint8_t hid_ep0_setup_hindex_get(void);

void hid_ep0_enumerated_set(bool enumerated);
bool hid_ep0_is_enumerated(void);

void hid_ep1_init(void);
void hid_ep1_task(void);

void hid_ep1_in_stall(void);
void hid_ep1_in_unstall(void);
bool hid_ep1_in_is_stalled(void);

#ifdef __cplusplus
}
#endif

#endif // MSP430_HID_H
