#ifndef FX2_DEFS_H
#define FX2_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

enum bit_mask {
    bmBIT0 = 0x01,
    bmBIT1 = 0x02,
    bmBIT2 = 0x04,
    bmBIT3 = 0x08,
    bmBIT4 = 0x10,
    bmBIT5 = 0x20,
    bmBIT6 = 0x40,
    bmBIT7 = 0x80
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

#include <intrinsics.h>

# define NOP() __no_operation()

# define XDATA __xdata
# define CODE __code
# define AT __at

# define SFR __sfr
# define SBIT __bit

# define XDATA_REG(reg_name, reg_addr) \
    XDATA __no_init volatile BYTE reg_name @ reg_addr;

# define SPEC_FUN_REG(reg_name, reg_addr) \
    SFR __no_init volatile BYTE reg_name @ reg_addr;

# define SPEC_FUN_REG_BIT(bit_name, reg_addr, bit_num) \
    SBIT __no_init volatile _Bool bit_name @ (reg_addr+bit_num);

# define _PPTOSTR_(x) #x
# define _PPARAM_(address) _PPTOSTR_(vector=address * 8 + 3)
# define INTERRUPT(isr_name, vector) \
    _Pragma(_PPARAM_(vector)) __interrupt void isr_name(void)

#elif defined (__C51__)

# include <intrins.h>

# define NOP() _nop_()

# define XDATA xdata
# define CODE code
# define AT _at_

# define SFR sfr
# define SBIT sbit

# if defined(DEFINE_REGS)
#  define XDATA_REG(reg_name, reg_addr) \
    XDATA volatile BYTE reg_name AT reg_addr;
# else
#  define XDATA_REG(reg_name, reg_addr) \
    extern XDATA volatile BYTE reg_name;
# endif

# define SPEC_FUN_REG(reg_name, reg_addr) \
    SFR reg_name = reg_addr;

# define SPEC_FUN_REG_BIT(bit_name, reg_addr, bit_num) \
    sbit bit_name = reg_addr + bit_num;

# define INTERRUPT(isr_name, num) \
    void isr_name (void) interrupt num

#elif defined (__SDCC_mcs51)

# define NOP() __asm nop __endasm

# define XDATA __xdata
# define CODE __code
# define AT __at

# define SFR __sfr
# define SBIT __sbit

# define XDATA_REG(reg_name, reg_addr) \
    XDATA AT reg_addr volatile BYTE reg_name;

# define SPEC_FUN_REG(reg_name, reg_addr) \
    SFR AT reg_addr reg_name;

# define SPEC_FUN_REG_BIT(bit_name, reg_addr, bit_num) \
    SBIT AT reg_addr + bit_num bit_name;

# define INTERRUPT(isr_name, num) \
    void isr_name (void) __interrupt num

#else

#error "Unsupported toolchain"

#endif

#ifdef __cplusplus
}
#endif

#endif // FX2_DEFS_H
