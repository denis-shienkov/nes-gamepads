#ifndef FX2_DEFS_H
#define FX2_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

enum bit_mask {
    MSK_BIT0 = 0x01,
    MSK_BIT1 = 0x02,
    MSK_BIT2 = 0x04,
    MSK_BIT3 = 0x08,
    MSK_BIT4 = 0x10,
    MSK_BIT5 = 0x20,
    MSK_BIT6 = 0x40,
    MSK_BIT7 = 0x80
};

enum boolean {
    FALSE = 0,
    TRUE
};

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef bit BOOL;

#ifndef NULL
#define NULL (void *)0
#endif

#ifdef ALLOCATE_EXTERN
#define EXTERN__
#define AT__ _at_
#else
#define EXTERN__ extern
#define AT__ ;/ ## /
#endif

#if defined(__ICC8051__)
// TODO:
#elif defined (__C51__)
#include "intrins.h"
# define xdata_reg(reg_name, reg_addr) \
    EXTERN__ xdata volatile BYTE reg_name AT__ reg_addr;
# define special_function_reg(reg_name, reg_addr) \
    sfr reg_name = reg_addr;
# define special_function_reg_bit(bit_name, reg_addr, bit_num) \
    sbit bit_name = reg_addr + bit_num;
#elif defined (__SDCC_mcs51)
// TODO:
#else
#error "Unsupported toolchain"
#endif

#ifdef __cplusplus
}
#endif

#endif // FX2_DEFS_H
