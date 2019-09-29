#include "core.h"
#include "hid.h"
#include "usb.h"

static volatile BOOL g_gotsud = FALSE;
static volatile BOOL g_sleep = FALSE;

static BOOL g_rwuen = TRUE;
static BOOL g_selfpwr = FALSE;

static void usb_disconnect(BOOL renumerate)
{
    if (renumerate) {
        // If renumerate (i.e. 8051 will handle SETUP commands)
        // disconnect from USB and set the renumerate bit.
        USBCS |= (bmDISCON | bmRENUM);
    } else {
        // Just disconnect from USB.
        USBCS |= bmDISCON;
    }

    core_delay(1500);

    // Clear any pending USB interrupt requests.
    // They're for our old life.
    USBIRQ = 0xff;
    EPIRQ = 0xff;

    usb_irq_clear();

    USBCS &= ~bmDISCON; // Reconnect USB.
}

static void usb_resume(void)
{
    if (usb_is_ext_wakeup()) {
        USBCS |= bmSIGRESUME;
        core_delay(20);
        USBCS &= ~bmSIGRESUME;
    }
}

static void usb_suspend(void)
{
    // Clear the wake source bits.
    WAKEUPCS = (WAKEUPCS | bmWU | bmWU2);
    // Write any value.
    SUSPEND = 0xAA;
    // Switch CPU to idle.
    PCON = bmIDLE;
    sync_delay();
    sync_delay();
}

void usb_init(void)
{
    hid_init();

    usb_irq_enable(); // Enable USB interrupt (INT2).
    usb_rsmirq_enable(); // Enable USB wake-up interrupt.

    // Enable int 2 & 4 autovectoring.
    INTSETUP |= (bmAV2EN | bmAV4EN);
    // Enable selected USB interrupts.
    USBIE |= (bmSUDAV | bmSOF | bmSUTOK
              | bmSUSP | bmURES | bmHSGRANT);

    EA = 1; // Enable 8051 interrupts.
    PUSB = 1; // Set USB interrupt to high priority.

    // Renumerate if necessary.
    if (!(bmRENUM & USBCS)) {
        usb_disconnect(TRUE);
    }

    // Unconditionally re-connect. If we loaded from eeprom we are
    // disconnected and need to connect. If we just renumerated this
    // is not necessary but doesn't hurt anything.
    USBCS &= ~bmDISCON;
    // Set stretch to 0 (after renumeration).
    CKCON = ((CKCON & (~bmSTRETCH)) | bmFW_STRETCH_VALUE);
}

void usb_task(void)
{
    if (g_gotsud) { // Wait for sudav.
        hid_ep0_proc();
        g_gotsud = FALSE;
    }

    if (g_sleep) {
        // Clear the "go to sleep" flag.
        // Do it here to prevent any race condition between
        // wakeup and the next sleep.
        g_sleep = FALSE;
        do {
            // Switch CPU to idle mode.
            usb_suspend();
        } while (!g_rwuen && usb_is_ext_wakeup());

        // 8051 activity will resume here due to USB bus or Wakeup# pin activity.
        // If source is the Wakeup# pin, signal the host to Resume.
        usb_resume();
    }

    // Process data end points.
    hid_stream_proc();
}

//void usb_remote_wakeup_set(BOOL set)
//{
//    g_rwuen = set;
//}

BOOL usb_remote_wakeup_get(void)
{
    return g_rwuen;
}

BOOL usb_self_pwr_get(void)
{
    return g_selfpwr;
}

BOOL usb_is_hispeed_supported(void)
{
   if (GPCR2 & bmFULLSPEEDONLY)
      return FALSE;
   return TRUE;
}

// USB autovector interrupts.

void usb_sudav_isr(void)
{
    g_gotsud = TRUE;
    usb_irq_clear();
    USBIRQ = bmSUDAV;
}

void usb_sof_isr(void)
{
    usb_irq_clear();
    USBIRQ = bmSOF;
}

void usb_sutok_isr(void)
{
    usb_irq_clear();
    USBIRQ = bmSUTOK;
}

void usb_susp_isr(void)
{
    g_sleep = TRUE;
    usb_irq_clear();
    USBIRQ = bmSUSP;
}

void usb_ures_isr(void)
{
    usb_irq_clear();
    USBIRQ = bmURES;
}

void usb_hispeed_isr(void)
{
    usb_irq_clear();
    USBIRQ = bmHSGRANT;
}

void usb_stub_isr(void)
{
}
