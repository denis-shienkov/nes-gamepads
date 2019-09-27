#ifndef FX2_IRQS_H
#define FX2_IRQS_H

#ifdef __cplusplus
extern "C" {
#endif

// Standard interrupt numbers.
#define INT0_IRQ        0 // External interrupt 0.
#define TMR0_IRQ        1 // Timer 0 interrupt.
#define INT1_IRQ        2 // External interrupt 1.
#define TMR1_IRQ        3 // Timer 1 interrupt.
#define COM0_IRQ        4 // Serial port 0 transmit or receive interrupt.
#define TMR2_IRQ        5 // Timer 2 interrupt.
#define WKUP_IRQ        6 // Resume interrupt.
#define COM1_IRQ        7 // Serial port 1 transmit or receive interrupt.
#define USB_IRQ         8 // USB interrupt.
#define I2C_IRQ         9 // I2C bus interrupt.
#define INT4_IRQ        10 // External interrupt 4.
#define INT5_IRQ        11 // External interrupt 5.
#define INT6_IRQ        12 // External interrupt 6.

#ifdef __cplusplus
}
#endif

#endif // FX2_IRQS_H
