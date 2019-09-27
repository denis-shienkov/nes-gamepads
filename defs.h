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
typedef unsigned char BOOL;

#ifndef NULL
#define NULL (void *)0
#endif

#if defined(__ICC8051__)

// TODO:

#elif defined (__C51__)

# include "intrins.h"

# define NOP__() _nop_()
# define INTERRUPT__ interrupt

# define XDATA__ xdata
# define CODE__ code
# define AT__ _at_

# define SFR__ sfr
# define SBIT__ sbit

# if defined(DEFINE_REGS)
#  define xdata_reg(reg_name, reg_addr) \
    XDATA__ volatile BYTE reg_name AT__ reg_addr;
# else
#  define xdata_reg(reg_name, reg_addr) \
    extern XDATA__ volatile BYTE reg_name;
# endif

# define special_function_reg(reg_name, reg_addr) \
    SFR__ reg_name = reg_addr;
# define special_function_reg_bit(bit_name, reg_addr, bit_num) \
    sbit bit_name = reg_addr + bit_num;

#elif defined (__SDCC_mcs51)

# define NOP__() __asm nop __endasm
# define INTERRUPT__ __interrupt

# define XDATA__ __xdata
# define CODE__ __code
# define AT__ __at

# define SFR__ __sfr
# define SBIT__ __sbit

# define xdata_reg(reg_name, reg_addr) \
    XDATA__ AT__ reg_addr volatile BYTE reg_name;
# define special_function_reg(reg_name, reg_addr) \
    SFR__ AT__ reg_addr reg_name;
# define special_function_reg_bit(bit_name, reg_addr, bit_num) \
    SBIT__ AT__ reg_addr + bit_num bit_name;

#else

#error "Unsupported toolchain"

#endif

#ifdef __cplusplus
}
#endif

#endif // FX2_DEFS_H
