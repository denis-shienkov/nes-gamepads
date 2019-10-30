#ifndef MSP430_HW_DEFS_H
#define MSP430_HW_DEFS_H

#include <msp430.h>
#include <msp430f5xx_6xxgeneric.h>

#if defined(__ICC430__)
# define _PPTOSTR_(x) #x
# define _PPARAM_(address) _PPTOSTR_(vector=address)
# define INTERRUPT(isr_name, vector) \
    _Pragma(_PPARAM_(vector)) __interrupt void isr_name(void)
#elif defined(__GNUC__)
# define INTERRUPT(isr_name, vector) \
    void __attribute__ ((interrupt(vector))) isr_name(void)
#else
# error "Unsupported toolchain"
#endif

#include <stdbool.h>
#include <stdint.h>

#define HWREG8(x) \
    (*((volatile uint8_t *)((uint16_t)x)))

#define HWREG16(x) \
    (*((volatile uint16_t *)((uint16_t)x)))

#define HWREG32(x) \
    (*((volatile uint32_t *)((uint16_t)x)))

#endif // MSP430_HW_DEFS_H
