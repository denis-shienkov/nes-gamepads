#include "core.h"
#include "gpio.h"
#include "hid.h"
#include "regs.h"

static WORD g_counter = 0;

// We use this empirical value to make a GPIO polling
// every ~10 msec (rough). It is a simplest way, because
// instead we need to use a timers with interrupts callbacks.
enum { POLLING_COUNTER = 580 };

// Pins on the port A.
enum gpio_pins {
    GPIO_CLK_PIN = bmBIT0,
    GPIO_DATA1_PIN = bmBIT2,
    GPIO_DATA2_PIN = bmBIT4,
    GPIO_LATCH_PIN = bmBIT6,
};

static struct {
    const BYTE pin;
    BYTE buttons;
} g_reports[HID_REPORTS_COUNT] = {
    GPIO_DATA1_PIN, 0,
    GPIO_DATA2_PIN, 0
};

// Pulse width around ~1 usec.
static void gpio_latch_pulse(void)
{
    IOA |= GPIO_LATCH_PIN;
    sync_delay();
    sync_delay();
    sync_delay();
    IOA &= ~GPIO_LATCH_PIN;
    sync_delay();
}

// Pulse width around ~1 usec.
static void gpio_clk_pulse(void)
{
    IOA |= GPIO_CLK_PIN;
    sync_delay();
    sync_delay();
    sync_delay();
    IOA &= ~GPIO_CLK_PIN;
    sync_delay();
}

static void gpio_reports_clean(void)
{
    BYTE index = 0;
    for (index = 0; index < HID_REPORTS_COUNT; ++index)
        g_reports[index].buttons = 0;
}

static void gpio_reports_send(void)
{
    BYTE index = 0;
    for (index = 0; index < HID_REPORTS_COUNT; ++index)
        hid_ep1_report_update(index, g_reports[index].buttons);
}

static void gpio_poll(void)
{
    BYTE pos = 0;

    // Cleanup reports.
    gpio_reports_clean();

    // Send latch pulse.
    gpio_latch_pulse();

    for (pos = 0; pos < HID_REPORT_BITS_COUNT; ++pos) {
        // TODO: Add some nops here?

        BYTE index = 0;
        for (index = 0; index < HID_REPORTS_COUNT; ++index) {
            // Low state means that a button is pressed.
            const BOOL v = (IOA & g_reports[index].pin) ? 0 : 1;
            g_reports[index].buttons |= (v << pos);
        }

        // Send clock pulse.
        gpio_clk_pulse();
    }

    gpio_reports_send();
}

void gpio_init(void)
{
    // Set interface to ports.
    IFCONFIG = (IFCONFIG & (~bmIFCFG)) | bmIFPORTS;
    sync_delay();

    // Initialize the CLK and LATCH pins as output.
    OEA = GPIO_CLK_PIN | GPIO_LATCH_PIN;
    sync_delay();
}

void gpio_task(void)
{
    if (g_counter < POLLING_COUNTER) {
        ++g_counter;
    } else {
        g_counter = 0;
        gpio_poll();
    }
}
