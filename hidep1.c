#include "gpio.h"
#include "hid.h"
#include "hwdefs.h"
#include "usb.h"

// We use this empirical value to make a GPIO polling
// every ~10 msec (rough). It is a simplest way, because
// instead we need to use a timers with interrupts callbacks.
enum { POLLING_COUNTER = 888 };

// Pins on the port 6.
enum gpio_pins {
    GPIO_CLK_PIN = BIT0,
    GPIO_DATA1_PIN = BIT1,
    GPIO_DATA2_PIN = BIT2,
    GPIO_LATCH_PIN = BIT3,
};

struct usb_ep {
    uint8_t EPCNF; // Endpoint configuration.
    uint8_t EPBBAX; // Endpoint X buffer base address.
    uint8_t EPBCTX; // Endpoint X Buffer byte count.
    uint8_t SPARE0; // No used.
    uint8_t SPARE1; // No used.
    uint8_t EPBBAY; // Endpoint Y buffer Base address.
    uint8_t EPBCTY; // Endpoint Y buffer byte count.
    uint8_t EPSIZXY; // Endpoint XY buffer size.
};

#define EP1_IN_X_BUFFER_ADDRESS (0x1C80)

#pragma location = USBIEPCNF_1_
__no_init struct usb_ep __data16 g_ep1_in;

#pragma location = EP1_IN_X_BUFFER_ADDRESS
__no_init uint8_t __data16 g_ep1_in_xbuf[EP_MAX_PACKET_SIZE];

static struct {
    const uint8_t data_pin;
    const uint8_t id;
    uint8_t buttons;
    bool ready;
} g_reports[HID_REPORTS_COUNT] = {
{GPIO_DATA1_PIN, HID_REPORT_ID_GAMEPAD1, 0, false},
{GPIO_DATA2_PIN, HID_REPORT_ID_GAMEPAD2, 0, false}
};

static uint16_t g_poll_counter = 0;

// Pulse width around ~10 usec.
static void ep1_latch_pulse(void)
{
    gpio_pins_set_high(GPIO_PORT_P6, GPIO_LATCH_PIN);
    gpio_pins_set_low(GPIO_PORT_P6, GPIO_LATCH_PIN);
}

// Pulse width around ~10 usec.
static void ep1_clk_pulse(void)
{
    gpio_pins_set_high(GPIO_PORT_P6, GPIO_CLK_PIN);
    gpio_pins_set_low(GPIO_PORT_P6, GPIO_CLK_PIN);
}

static void ep1_reports_clean(void)
{
    for (uint8_t index = 0; index < HID_REPORTS_COUNT; ++index) {
        g_reports[index].buttons = 0;
        g_reports[index].ready = false;
    }
}

static void ep1_reports_update(void)
{
    for (uint8_t index = 0; index < HID_REPORTS_COUNT; ++index)
        g_reports[index].ready = true;
}

static void ep1_gamepads_poll(void)
{
    ep1_reports_clean();

    ep1_latch_pulse();

    for (uint8_t pos = 0; pos < HID_REPORT_BITS_COUNT; ++pos) {
        // TODO: Add some nops here?

        for (uint8_t index = 0; index < HID_REPORTS_COUNT; ++index) {
            const uint8_t pin = g_reports[index].data_pin;
            const enum gpio_pin_status st = gpio_pin_get(GPIO_PORT_P6, pin);
            // Low state means that a button is pressed.
            const bool v = (st == GPIO_INPUT_PIN_LOW);
            g_reports[index].buttons |= (v << pos);
        }

        ep1_clk_pulse();
    }

    ep1_reports_update();
}

static void ep1_report_send(uint8_t report_index)
{
    if (!g_reports[report_index].ready)
        return;

    if ((g_ep1_in.EPBCTX & NAK) == 0)
        return;

    g_ep1_in_xbuf[0] = g_reports[report_index].id;
    g_ep1_in_xbuf[1] = g_reports[report_index].buttons;
    g_ep1_in.EPBCTX = 2;

    g_reports[report_index].ready = false;
}

static uint8_t ep_buffer_offset_calculate(uint16_t base_address)
{
    return ((base_address - USBSTABUFF_) >> 3) & 0x00FF;
}

void hid_ep1_init(void)
{
    g_ep1_in.EPCNF = UBME | USBIIE;
    g_ep1_in.EPBBAX = ep_buffer_offset_calculate(EP1_IN_X_BUFFER_ADDRESS);
    g_ep1_in.EPBCTX = NAK;
    g_ep1_in.EPSIZXY = EP_MAX_PACKET_SIZE;

    gpio_pins_set_as_out(GPIO_PORT_P6, GPIO_CLK_PIN | GPIO_LATCH_PIN);
    gpio_pins_set_as_in(GPIO_PORT_P6, GPIO_DATA1_PIN | GPIO_DATA2_PIN);
}

void hid_ep1_task(void)
{
    if (!hid_ep0_is_enumerated())
        return;

    for (uint8_t index = 0; index < HID_REPORTS_COUNT; ++index)
        ep1_report_send(index);

    if (g_poll_counter <= POLLING_COUNTER) {
        ++g_poll_counter;
    } else {
        g_poll_counter = 0;
        ep1_gamepads_poll();
    }
}

void hid_ep1_in_stall(void)
{
    g_ep1_in.EPCNF |= STALL;
}

void hid_ep1_in_unstall(void)
{
    g_ep1_in.EPCNF &= ~(STALL | TOGGLE);
}

bool hid_ep1_in_is_stalled(void)
{
    return (g_ep1_in.EPCNF & STALL);
}
