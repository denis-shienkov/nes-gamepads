#include "hid.h"
#include "core.h"
#include "usb.h"

#include <string.h>

enum ep0_state {
    EP0_IDLE = 0,
    EP0_ALLOW_STATUS_PHASE, // If all data received during setup out.
    EP0_INDICATE_DATA, // If receive setup in.
    EP0_RECEIVING_DATA, // If receive setup out.
    EP0_INDICATE_STALL // Error in setup packet.
};

struct ep0_setup {
    BYTE type;
    BYTE request;
    BYTE hvalue;
    BYTE lvalue;
    BYTE hindex;
    BYTE lindex;
    WORD length;
};

union ep0_xfer {
    BYTE cvalue;
    WORD wvalue;
    BYTE array[MAX_EP0_SIZE * 2];
};

struct ep0 {
    BOOL hspeed; // High speed.
    BOOL rwuen; // Remote wakeup enable.
    BYTE cfg;
    enum ep0_state state;
    struct ep0_buf buf;
    struct ep0_setup setup;
};

static XDATA struct ep0 g_ep0;
static XDATA union ep0_xfer g_xfer;

static void usb_ep0_indicate_data(void)
{
    // Check if fifo space is available.
    if (EP01STAT & bmEP0BSY) {
        return;
    } else {
        BYTE bytes = MAX_EP0_SIZE;
        if (g_ep0.buf.len <= bytes) {
            // All data fits to next packet.
            bytes = g_ep0.buf.len;
            g_ep0.state = EP0_IDLE;
        }

        if (bytes > 0) {
            // Copy data to end point 0 buffer, update state.
            memcpy(EP0BUF, g_ep0.buf.dat, bytes);
            g_ep0.buf.dat += bytes;
            g_ep0.buf.len -= bytes;
        }

        // Update end point 0 byte counter.
        sync_delay();
        EP0BCH = 0;
        sync_delay();
        // Initiate transfer to host.
        EP0BCL = bytes;
        sync_delay();
    }
}

static void usb_ep0_receive_data(void)
{
    BYTE bytes = 0;

    sync_delay();
    bytes = EP0BCL;
    sync_delay();

    if (bytes < MAX_EP0_SIZE) {
        // Current out transfer is finished, allow status phase.
        g_ep0.state = EP0_ALLOW_STATUS_PHASE;
    }

    if (bytes > 0) {
        // Buffer length is set to number of bytes that are expected
        // and decremented for every out transfer; check if we expect
        // this much data.
        if (g_ep0.buf.len < bytes) {
            // More data than expected, stall.
            g_ep0.state = EP0_INDICATE_STALL;
            // Reset.
            g_ep0.buf.len = 0;
            bytes = g_ep0.buf.len;
        } else {
            // Move data from fifo to intermediate buffer.
            memcpy(g_ep0.buf.dat, &EP0BUF, bytes);
            g_ep0.buf.len -= bytes;
            g_ep0.buf.dat += bytes;
            if (g_ep0.buf.len == 0) {
                // All data received, allow status phase.
                g_ep0.state = EP0_ALLOW_STATUS_PHASE;
            }
        }
    }

    // Arm end point 0 fifo for next out transfer.
    sync_delay();
    EP0BCL = 0;
    sync_delay();
}

void ep0_get_status_proc(void)
{
    if (g_ep0.setup.length != 2 ) {
        g_ep0.state = EP0_INDICATE_STALL;
        return;
    }

    // In case of success one word is returned.
    g_ep0.buf.len = 2;
    g_xfer.wvalue = 0;

    switch (g_ep0.setup.type & bmSETUP_RECIPIENT) {
    case bmSETUP_DEVICE: // Return device status.
        ///g_xfer.cvalue = (gConfDescriptorHS.cfg.attrib >> 6) & 0x1;
        ///if (g_ep0.rwuen != 0) {
        g_xfer.cvalue |= USB_STATUS_REMOTE_WAKEUP;
        ///}
        break;

    case bmSETUP_IFACE: // Reserved, return 0.
        g_xfer.wvalue = 0;
        break;

    case bmSETUP_EP: // Return end point status.
        switch (g_ep0.setup.lindex) {
        /*
        case EP_IN_COMMAND:
            gEp0TransferBuffer.cValue = (gUsb.Ep1In.State == PS_IndicateStall) ? 0x01 : 0x0;
            break;
        case EP_OUT_COMMAND:
            gEp0TransferBuffer.cValue = (gUsb.Ep1Out.State == PS_IndicateStall) ? 0x1 : 0x0;
            break;
        case EP_IN_STREAM:
            gEp0TransferBuffer.cValue = (gUsb.Ep2.State == PS_IndicateStall) ? 0x1 : 0x0;
            break;
        case EP_OUT_STREAM:
            gEp0TransferBuffer.cValue = (gUsb.Ep6.State == PS_IndicateStall) ? 0x1 : 0x0;
            break;
        */
        default: // Invalid end point.
            g_ep0.buf.len = 0;
            g_ep0.state = EP0_INDICATE_STALL;
            break;
        }
        break;

    default: // Invalid recipient.
        g_ep0.buf.len = 0;
        g_ep0.state = EP0_INDICATE_STALL;
        break;
    }
}

void ep0_clear_feature_proc(void)
{
    if (g_ep0.setup.length != 0) {
        g_ep0.state = EP0_INDICATE_STALL;
        return;
    }

    switch (g_ep0.setup.type & bmSETUP_RECIPIENT) {

    case bmSETUP_DEVICE: // Clear feature device.
        if (g_ep0.setup.lvalue != USB_FEATURE_REMOTE_WAKEUP ) {
            g_ep0.state = EP0_INDICATE_STALL;
        } else {
            g_ep0.rwuen = FALSE;
        }
        break;

    case bmSETUP_EP: // Clear feature end point.
        if (g_ep0.setup.lvalue != USB_FEATURE_STALL) {
            g_ep0.state = EP0_INDICATE_STALL;
            break;
        }

        switch (g_ep0.setup.lindex) {
        /*
        case EP_IN_COMMAND:
            EP1IN_RESET;
            EP1INCS &= (~bmEPSTALL);
            gUsb.Ep1In.State = PS_Idle;
            break;
        case EP_OUT_COMMAND:
            EP1OUT_RESET;
            EP1OUTCS &= (~bmEPSTALL);
            gUsb.Ep1Out.State = PS_Idle;
            break;
        case EP_IN_STREAM:
            EP_FIFO_RESET(gUsb.Ep2);
            CLR_TOGGLE_BIT(gUsb.Ep2);
            EP2CS &= (~bmEPSTALL);
            EP2CFG |= EPCFG_ENABLE;
            gUsb.Ep2.State = PS_Idle;
            break;
        case EP_OUT_STREAM:
            EP_FIFO_RESET(gUsb.Ep6);
            // clear OUT endpoint buffers
            OUTPKTEND = SKIP_OUT_PACKET | 6;
            SYNCDELAY;
            OUTPKTEND = SKIP_OUT_PACKET | 6;
            SYNCDELAY;
            CLR_TOGGLE_BIT(gUsb.Ep6);
            EP6CS &= (~bmEPSTALL);
            EP6CFG |= EPCFG_ENABLE;
            gUsb.Ep6.State = PS_Idle;
            break;
        */
        default: // Invalid end point.
            g_ep0.state = EP0_INDICATE_STALL;
            break;
        }
        break;

    default: // Invalid recipient.
        g_ep0.state = EP0_INDICATE_STALL;
        break;
    }
}

void ep0_set_feature_proc(void)
{
    if (g_ep0.setup.length != 0) {
        g_ep0.state = EP0_INDICATE_STALL;
        return;
    }

    switch (g_ep0.setup.type & bmSETUP_RECIPIENT) {

    case bmSETUP_DEVICE: // Set feature device.
        switch (g_ep0.setup.lvalue){
        case USB_FEATURE_REMOTE_WAKEUP:
            // Device does not support remote wakeup.
            g_ep0.state = EP0_INDICATE_STALL;
            break;
        case USB_FEATRUE_TEST_MODE:
            // FX2 handles this request.
            break;
        default:
            g_ep0.state = EP0_INDICATE_STALL;
            break;
        }
        break;

    case bmSETUP_EP: // Set feature end point.
        if (g_ep0.setup.lvalue != USB_FEATURE_STALL ){
            g_ep0.state = EP0_INDICATE_STALL;
            break;
        }

        switch (g_ep0.setup.lindex) {
        /*
        case EP_IN_COMMAND:
            EP1INCS |= bmEPSTALL;
            CLR_TOGGLE_BIT(gUsb.Ep1In);
            gUsb.Ep1In.State = PS_IndicateStall;
            break;
        case EP_OUT_COMMAND:
            EP1OUTCS |= bmEPSTALL;
            CLR_TOGGLE_BIT(gUsb.Ep1Out);
            gUsb.Ep1Out.State = PS_IndicateStall;
            break;
        case EP_IN_STREAM:
            EP2CS |= bmEPSTALL;
            EP2CFG &= ~EPCFG_ENABLE;
            CLR_TOGGLE_BIT(gUsb.Ep2);
            gUsb.Ep2.State = PS_IndicateStall;
            break;
        case EP_OUT_STREAM:
            EP6CFG &= ~EPCFG_ENABLE;
            EP6CS |= bmEPSTALL;
            CLR_TOGGLE_BIT(gUsb.Ep6);
            gUsb.Ep6.State = PS_IndicateStall;
            break;
        */
        default: // Invalid end point.
            g_ep0.state = EP0_INDICATE_STALL;
            break;
        }
        break;

    default: // Invalid recipient.
        g_ep0.state = EP0_INDICATE_STALL;
        break;
    }
}

void ep0_get_descriptor_proc(void)
{
    struct ep0_buf buf;
    buf = hid_ep0_desc_get(g_ep0.setup.hvalue,
                           g_ep0.setup.lvalue,
                           g_ep0.hspeed);
    if (!buf.dat) {
        g_ep0.state = EP0_INDICATE_STALL;
    } else {
        // Indicate number of bytes available for in transfer.
        // We should never return more bytes than requested by host.
        if (g_ep0.setup.length < buf.len ) {
            buf.len = g_ep0.setup.length;
        }

        g_ep0.buf = buf;
    }
}

void ep0_standard_proc(void)
{
    switch (g_ep0.setup.request) {
    case USB_SETUP_GET_STATUS:
        ep0_get_status_proc();
        break;
    case USB_SETUP_CLEAR_FEATURE:
        ep0_clear_feature_proc();
        break;
    case USB_SETUP_SET_FEATURE:
        ep0_set_feature_proc();
        break;
    case USB_SETUP_SET_ADDRESS:
        // Handles automatically by FX2.
        break;
    case USB_SETUP_GET_DESCRIPTOR:
        ep0_get_descriptor_proc();
        break;
    default:
        g_ep0.state = EP0_INDICATE_STALL;
        break;
    }
}

void hid_ep0_init(void)
{
    memset(&g_ep0, 0, sizeof(g_ep0));
}

void hid_ep0_setup_proc(void)
{
    g_ep0.setup.type = SETUPDAT[0];
    g_ep0.setup.request = SETUPDAT[1];
    g_ep0.setup.lvalue = SETUPDAT[2];
    g_ep0.setup.hvalue = SETUPDAT[3];
    g_ep0.setup.lindex = SETUPDAT[4];
    g_ep0.setup.hindex = SETUPDAT[5];
    g_ep0.setup.length = (usb_word_swap(*(WORD *)&SETUPDAT[6]));

    g_ep0.hspeed = usb_is_high_speed();
    g_ep0.state = EP0_IDLE;

    g_ep0.buf.dat = (BYTE *)&g_xfer;
    g_ep0.buf.len = 0;

    // Check if the current setup request includes data stage.
    if (g_ep0.setup.length > 0) {
        if ((g_ep0.setup.type & bmSETUP_TO_HOST)) {
            g_ep0.state = EP0_INDICATE_DATA;
        } else {
            g_ep0.buf.len = g_ep0.setup.length;
            g_ep0.state = EP0_RECEIVING_DATA;
        }
    }

    switch (g_ep0.setup.type & bmSETUP_TYPE) {
    case bmSETUP_STANDARD:
        ep0_standard_proc();
        break;
    case bmSETUP_CLASS:
    case bmSETUP_VENDOR:
    default:
        return;
    }

    // Further steps depend on current end point 0 state.
    switch (g_ep0.state) {
    case EP0_INDICATE_DATA:
        // There is data to be transferred to host.
        usb_ep0_indicate_data();
        break;
    case EP0_RECEIVING_DATA:
        // Current setup request has an out data stage.
        usb_ep0_out_enable();
        break;
    case EP0_INDICATE_STALL:
        // Stall end point until next setup is received.
        usb_ep0_stall();
        break;
    default:
        // Other internal states are not handled here.
        break;
    }

    // Allow status phase if request was processed successfully.
    if ((g_ep0.state == EP0_INDICATE_DATA)
            || (g_ep0.state == EP0_IDLE)) {
        usb_ep0_hsnack();
    }
}

void hid_ep0_in_proc(void)
{
    switch (g_ep0.state) {
    case EP0_INDICATE_DATA:
        usb_ep0_indicate_data();
        break;
    default:
        break;
    }
}

void hid_ep0_out_proc(void)
{
    switch (g_ep0.state) {
    case EP0_RECEIVING_DATA:
        // We are waiting for OUT data, store it.
        usb_ep0_receive_data();
        if (g_ep0.state == EP0_ALLOW_STATUS_PHASE) {
            // All out data for current setup request received
            // to buffer, process it.
            switch (g_ep0.setup.type & bmSETUP_TYPE) {
            default:
                g_ep0.state = EP0_INDICATE_STALL;
                break;
            }
        }
        break;
    default:
        // We do not expect an out packet.
        g_ep0.state = EP0_INDICATE_STALL;
        break;
    }

    // Continue depending on state of end point 0.
    switch (g_ep0.state) {
    case EP0_ALLOW_STATUS_PHASE:
        usb_ep0_hsnack();
        g_ep0.state = EP0_IDLE;
        break;
    case EP0_INDICATE_STALL:
        usb_ep0_stall();
        break;
    default:
        break;
    }
}
