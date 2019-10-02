#include "hid.h"
#include "core.h"
#include "usb.h"

static BOOL g_rwuen = FALSE;
static BOOL g_selfpwr = FALSE;

static void ep0_ep1in_reset(void)
{
    EP1INCS &= ~bmEPBUSY;
    sync_delay();
    usp_ep_reset_toggle(HID_EP_IN);
    sync_delay();
}

// Get status handle.

static BYTE XDATA *ep_address_get(BYTE ep)
{
    const BYTE ep_num = ep & ~bmSETUP_DIR;
    switch (ep_num) {
    case 0:
        return &EP0CS;
    case 1:
        return ep & bmSETUP_DIR ? &EP1INCS : &EP1OUTCS;
    default:
        break;
    }
    return NULL;
}

static BOOL ep0_dev_status_get(void)
{
    EP0BUF[0] = (g_rwuen << 1) | g_selfpwr;
    EP0BUF[1] = 0;
    EP0BCH = 0;
    EP0BCL = 2;
    return TRUE;
}

static BOOL ep0_iface_status_get(void)
{
    EP0BUF[0] = 0;
    EP0BUF[1] = 0;
    EP0BCH = 0;
    EP0BCL = 2;
    return TRUE;
}

static BOOL ep0_ep_status_get(void)
{
    const BYTE XDATA *pep = ep_address_get(SETUPDAT[4]);
    if (pep) {
        EP0BUF[0] = *pep & bmEPSTALL ? 1 : 0;
        EP0BUF[1] = 0;
        EP0BCH = 0;
        EP0BCL = 2;
        return TRUE;
    }

    return FALSE;
}

static BOOL ep0_get_status_proc(void)
{
    if ((SETUPDAT[0] & bmSETUP_TO_HOST) == 0)
        return FALSE;

    switch (SETUPDAT[0] & bmSETUP_RECIPIENT) {
    case bmSETUP_DEVICE:
        return ep0_dev_status_get();
    case bmSETUP_IFACE:
        return ep0_iface_status_get();
    case bmSETUP_EP:
        return ep0_ep_status_get();
    default:
        break;
    }

    return FALSE;
}

// Clear feature handle.

static BOOL ep0_dev_feature_clear(void)
{
    if (SETUPDAT[2] == 1) {
        g_rwuen = FALSE;
        return TRUE;
    }

    return FALSE;
}

static BOOL ep0_ep_feature_clear(void)
{
    if (SETUPDAT[2] == 0) {
        BYTE XDATA *pep = ep_address_get(SETUPDAT[4]);
        if (!pep)
            return FALSE;
        *pep &= ~bmEPSTALL;
        return TRUE;
    }

    return FALSE;
}

static BOOL ep0_clear_feature_proc(void)
{
    switch (SETUPDAT[0] & bmSETUP_RECIPIENT) {
    case bmSETUP_DEVICE:
        return ep0_dev_feature_clear();
    case bmSETUP_EP:
        return ep0_ep_feature_clear();
    default:
        break;
    }

    return FALSE;
}

// Set feature handle.

static BOOL ep0_dev_feature_set(void)
{
    switch (SETUPDAT[2]) {
    case USB_FEATURE_REMOTE_WAKEUP:
        g_rwuen = TRUE;
        return TRUE;
    case USB_FEATRUE_TEST_MODE:
        // This is "test mode", just return the handshake.
        return TRUE;
    default:
        break;
    }

    return FALSE;
}

static BOOL ep0_ep_feature_set(void)
{
    if (SETUPDAT[2] == 0) {
        BYTE XDATA *pep = ep_address_get(SETUPDAT[4]);
        if (!pep)
            return FALSE;
        *pep |= bmEPSTALL;
        usp_ep_reset_toggle(SETUPDAT[4]);
        return TRUE;
    }

    return FALSE;
}

static BOOL ep0_set_feature_proc(void)
{
    switch (SETUPDAT[0] & bmSETUP_RECIPIENT) {
    case bmSETUP_DEVICE:
        return ep0_dev_feature_set();
    case bmSETUP_EP:
        return ep0_ep_feature_set();
    default:
        break;
    }

    return FALSE;
}

// Get descriptor handle.

static BOOL ep0_get_descriptor_proc(void)
{
    BYTE *pdesc = hid_ep0_desc_get();
    if (pdesc) {
        SUDPTRH = usb_word_msb_get(pdesc);
        SUDPTRL = usb_word_lsb_get(pdesc);
        return TRUE;
    }

    return FALSE;
}

// Get configuration handle.

static BOOL ep0_get_config_proc(void)
{
    // We only support configuration 1.
    EP0BUF[0] = HID_CONFIG_NUMBER;
    EP0BCH = 0;
    EP0BCL = 1;
    return TRUE;
}

// Set configuration handle.

static BOOL ep0_set_config_proc(void)
{
    // We only support configuration 1.
    if (SETUPDAT[2] != HID_CONFIG_NUMBER)
        return FALSE;

    return TRUE;
}

// Get interface handle.

static BOOL ep0_get_iface_proc(void)
{
    if (SETUPDAT[4] != HID_IFACE_NUMBER)
        return FALSE;

    EP0BUF[0] = HID_ALT_IFACE_NUMBER;
    EP0BCH = 0;
    EP0BCL = 1;
    return TRUE;
}

// Set interface handle.

static BOOL ep0_set_iface_proc(void)
{
    if (SETUPDAT[4] != HID_IFACE_NUMBER)
        return FALSE;

    if (SETUPDAT[2] != HID_ALT_IFACE_NUMBER)
        return FALSE;

    ep0_ep1in_reset();
    return TRUE;
}

static BOOL ep0_std_proc(void)
{
    switch (SETUPDAT[1]) {
    case USB_SETUP_GET_STATUS:
        return ep0_get_status_proc();
    case USB_SETUP_CLEAR_FEATURE:
        return ep0_clear_feature_proc();
    case USB_SETUP_SET_FEATURE:
        return ep0_set_feature_proc();
    case USB_SETUP_SET_ADDRESS:
        // Handles automatically by FX2.
        return TRUE;
    case USB_SETUP_GET_DESCRIPTOR:
        return ep0_get_descriptor_proc();
    case USB_SETUP_GET_CONFIGURATION:
        return ep0_get_config_proc();
    case USB_SETUP_SET_CONFIGURATION:
        return ep0_set_config_proc();
    case USB_SETUP_GET_INTERFACE:
        return ep0_get_iface_proc();
    case USB_SETUP_SET_INTERFACE:
        return ep0_set_iface_proc();
    default:
        break;
    }

    return FALSE;
}

static BOOL ep0_setup(void)
{
    switch (SETUPDAT[0] & bmSETUP_TYPE) {
    case bmSETUP_STANDARD:
        return ep0_std_proc();
    default:
        break;
    }

    return FALSE;
}

void hid_ep0_setup_proc(void)
{
    if (!ep0_setup())
        usb_ep0_stall();

    usb_ep0_hsnack();
}
