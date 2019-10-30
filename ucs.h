#ifndef MSP430_UCS_H
#define MSP430_UCS_H

#ifdef __cplusplus
extern "C" {
#endif

enum ucs_signal {
    UCS_ACLK = 0x01,
    UCS_MCLK = 0x02,
    UCS_SMCLK = 0x04,
    UCS_FLLREF = 0x08
};

enum ucs_source {
    UCS_XT1CLK_SELECT,
    UCS_VLOCLK_SELECT,
    UCS_REFOCLK_SELECT,
    UCS_DCOCLK_SELECT,
    UCS_DCOCLKDIV_SELECT,
    UCS_XT2CLK_SELECT
};

enum ucs_divider {
    UCS_CLOCK_DIVIDER_1,
    UCS_CLOCK_DIVIDER_2,
    UCS_CLOCK_DIVIDER_4,
    UCS_CLOCK_DIVIDER_8,
    UCS_CLOCK_DIVIDER_12,
    UCS_CLOCK_DIVIDER_16,
    UCS_CLOCK_DIVIDER_32
};

enum ucs_fault_flag {
    UCS_XT2OFFG,
    UCS_XT1HFOFFG,
    UCS_XT1LFOFFG,
    UCS_DCOFFG
};

void ucs_clocks_init(void);

void ucs_init(enum ucs_signal signal,
              enum ucs_source source,
              enum ucs_divider divider);

bool ucs_xt2_blocking_turn_on(uint16_t drive, uint16_t timeout);

void ucs_xt2_turn_off(void);
void ucs_fll_settle_init(uint16_t fsystem, uint16_t ratio);

#ifdef __cplusplus
}
#endif

#endif // MSP430_UCS_H
