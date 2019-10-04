#include "hid.h"

struct hid_report {
    const BYTE id;
    BYTE buttons;
    BYTE ready;
};

static struct hid_report g_reports[HID_REPORTS_COUNT] = {
    {HID_REPORT_ID_GAMEPAD1, 0, FALSE},
    {HID_REPORT_ID_GAMEPAD2, 0, FALSE}
};

static void ep1_report_send(BYTE index)
{
    if (!g_reports[index].ready)
        return;

    if (EP1INCS & bmEPBUSY)
        return;

    EP1INBUF[0] = g_reports[index].id;
    EP1INBUF[1] = g_reports[index].buttons;
    EP1INBC = 2;
    g_reports[index].ready = FALSE;
}

void hid_ep1_task(void)
{
    BYTE index = 0;
    for (index = 0; index < HID_REPORTS_COUNT; ++index)
        ep1_report_send(index);
}

void hid_ep1_report_update(BYTE index, BYTE buttons)
{
    g_reports[index].buttons = buttons;
    g_reports[index].ready = TRUE;
}
