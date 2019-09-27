#pragma noiv // Do not generate interrupt vectors.

#include "hid.h"
#include "core.h"
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
        USBCS |= (MSK_USBCS_DISCON | MSK_USBCS_RENUM);
    } else {
        // Just disconnect from USB.
        USBCS |= MSK_USBCS_DISCON;
    }

    core_delay(1500);

    // Clear any pending USB interrupt requests.
    // They're for our old life.
    USBIRQ = 0xff;
    EPIRQ = 0xff;

    usb_irq_clear();

    USBCS &= ~MSK_USBCS_DISCON; // Reconnect USB.
}

static void usb_resume(void)
{
    if (usb_is_ext_wakeup()) {
        USBCS |= MSK_USBCS_SIGRESUME;
        core_delay(20);
        USBCS &= ~MSK_USBCS_SIGRESUME;
    }
}

static void usb_suspend(void)
{
    // Clear the wake source bits.
    WAKEUPCS = (WAKEUPCS | MSK_WAKEUPCS_WU | MSK_WAKEUPCS_WU2);
    // Write any value.
    SUSPEND = 0xAA;
    // Switch CPU to idle.
    PCON = MSK_PCON_IDLE;
    sync_delay();
    sync_delay();
}

void usb_init(void)
{
    hid_init();

    usb_irq_enable(); // Enable USB interrupt (INT2).
    usb_rsmirq_enable(); // Enable USB wake-up interrupt.

    // Enable int 2 & 4 autovectoring.
    INTSETUP |= (MSK_INTSETUP_AV2EN | MSK_INTSETUP_AV4EN);
    // Enable selected USB interrupts.
    USBIE |= (MSK_USBIEIRQ_SUDAV | MSK_USBIEIRQ_SOF | MSK_USBIEIRQ_SUTOK
              | MSK_USBIEIRQ_SUSP | MSK_USBIEIRQ_URES | MSK_USBIEIRQ_HSGRANT);

    EA = 1; // Enable 8051 interrupts.
    PUSB = 1; // Set USB interrupt to high priority.

    // Renumerate if necessary.
    if (!(MSK_USBCS_RENUM & USBCS)) {
        usb_disconnect(TRUE);
    }

    // Unconditionally re-connect. If we loaded from eeprom we are
    // disconnected and need to connect. If we just renumerated this
    // is not necessary but doesn't hurt anything.
    USBCS &= ~MSK_USBCS_DISCON;
    // Set stretch to 0 (after renumeration).
    CKCON = ((CKCON & (~MSK_CKCON_STRETCH)) | MSK_CKCON_FW_STRETCH_VALUE);
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
   if (GPCR2 & MSK_GPCR2_FULLSPEEDONLY)
      return FALSE;
   return TRUE;
}

// USB autovector interrupts.

void usb_sudav_isr(void) INTERRUPT__ 0
{
    g_gotsud = TRUE;
    usb_irq_clear();
    USBIRQ = MSK_USBIEIRQ_SUDAV;
}

void usb_sof_isr(void) INTERRUPT__ 0
{
    usb_irq_clear();
    USBIRQ = MSK_USBIEIRQ_SOF;
}

void usb_sutok_isr(void) INTERRUPT__ 0
{
    usb_irq_clear();
    USBIRQ = MSK_USBIEIRQ_SUTOK;
}

void usb_susp_isr(void) INTERRUPT__ 0
{
    g_sleep = TRUE;
    usb_irq_clear();
    USBIRQ = MSK_USBIEIRQ_SUSP;
}

void usb_ures_isr(void) INTERRUPT__ 0
{
    usb_irq_clear();
    USBIRQ = MSK_USBIEIRQ_URES;
}

void usb_hispeed_isr(void) INTERRUPT__ 0
{
    usb_irq_clear();
    USBIRQ = MSK_USBIEIRQ_HSGRANT;
}

void usb_stub_isr(void) INTERRUPT__ 0
{
}
