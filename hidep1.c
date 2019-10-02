#include "hid.h"

#include <string.h>

static BOOL g_changed = FALSE;

enum hid_gamepad_id {
    HID_REPORT_ID_GAMEPAD1 = 1,
    HID_REPORT_ID_GAMEPAD2 = 2
};

static struct hid_report g_reports[HID_REPORTS_COUNT] = {
    HID_REPORT_ID_GAMEPAD1, 0,
    HID_REPORT_ID_GAMEPAD2, 0
};

enum { REPORTS_LENGTH = sizeof(g_reports) };

void hid_ep1_task(void)
{
    if (g_changed) {
        if (!(EP1INCS & bmEPBUSY)) {
            memcpy(EP1INBUF, g_reports, REPORTS_LENGTH);
            g_changed = FALSE;
        }
    }
}

void hid_ep1_report_update(BYTE index, BYTE buttons)
{
    g_reports[index].buttons = buttons;
    g_changed = TRUE;
}
