#include "hwdefs.h"

#include "ucs.h"

#ifdef __GNUC__
#define __delay_cycles(x) \
    ({ \
    volatile unsigned int j; \
    for(j = 0; j < x; j++) \
{ \
    __no_operation(); \
    } \
    })

#endif

static uint16_t ucs_source_mask(enum ucs_source source)
{
    switch (source) {
    case UCS_XT1CLK_SELECT:
        return SELM__XT1CLK;
    case UCS_VLOCLK_SELECT:
        return SELM__VLOCLK;
    case UCS_REFOCLK_SELECT:
        return SELM__REFOCLK;
    case UCS_DCOCLK_SELECT:
        return SELM__DCOCLK;
    case UCS_DCOCLKDIV_SELECT:
        return SELM__DCOCLKDIV;
    case UCS_XT2CLK_SELECT:
        return SELM__XT2CLK;
    default:
        break;
    }
    return SELM__XT1CLK;
}

static uint16_t ucs_divider_mask(enum ucs_divider divider)
{
    switch (divider) {
    case UCS_CLOCK_DIVIDER_1:
        return  DIVM__1;
    case UCS_CLOCK_DIVIDER_2:
        return  DIVM__2;
    case UCS_CLOCK_DIVIDER_4:
        return  DIVM__4;
    case UCS_CLOCK_DIVIDER_8:
        return  DIVM__8;
    case UCS_CLOCK_DIVIDER_12:
        return DIVM__32;
    case UCS_CLOCK_DIVIDER_16:
        return DIVM__16;
    case UCS_CLOCK_DIVIDER_32:
        return DIVM__32;
    default:
        break;
    }
    return DIVM__1;
}

static void ucs_fll_init(uint16_t fsystem, uint16_t ratio)
{
    const uint16_t sr_reg_backup = __get_SR_register() & SCG0;

    uint16_t mode = 0;
    uint16_t d = ratio;
    if (fsystem > 16000) {
        d >>= 1;
        mode = 1;
    } else {
        fsystem <<= 1;
    }

    uint16_t dco_div_bits = FLLD__2;
    while (d > 512) {
        dco_div_bits = dco_div_bits + FLLD0;
        d >>= 1;
    }

    // Disable FLL.
    __bis_SR_register(SCG0);
    // Set DCO to lowest tap.
    HWREG8(UCS_BASE + OFS_UCSCTL0_H) = 0;
    // Reset FN bits.
    HWREG16(UCS_BASE + OFS_UCSCTL2) &= ~(0x03FF);
    HWREG16(UCS_BASE + OFS_UCSCTL2) = dco_div_bits | (d - 1);

    if (fsystem <= 630) { // fsystem < 0.63MHz
        HWREG8(UCS_BASE + OFS_UCSCTL1) = DCORSEL_0;
    } else if (fsystem < 1250) { // 0.63MHz < fsystem < 1.25MHz
        HWREG8(UCS_BASE + OFS_UCSCTL1) = DCORSEL_1;
    } else if (fsystem < 2500) { // 1.25MHz < fsystem < 2.5MHz
        HWREG8(UCS_BASE + OFS_UCSCTL1) = DCORSEL_2;
    } else if (fsystem < 5000) { // 2.5MHz < fsystem < 5MHz
        HWREG8(UCS_BASE + OFS_UCSCTL1) = DCORSEL_3;
    } else if (fsystem < 10000) { // 5MHz < fsystem < 10MHz
        HWREG8(UCS_BASE + OFS_UCSCTL1) = DCORSEL_4;
    } else if (fsystem < 20000) { // 10MHz < fsystem < 20MHz
        HWREG8(UCS_BASE + OFS_UCSCTL1) = DCORSEL_5;
    } else if (fsystem < 40000) { // 20MHz < fsystem < 40MHz
        HWREG8(UCS_BASE + OFS_UCSCTL1) = DCORSEL_6;
    } else {
        HWREG8(UCS_BASE + OFS_UCSCTL1) = DCORSEL_7;
    }

    // Re-enable FLL.
    __bic_SR_register(SCG0);

    while (HWREG8(UCS_BASE + OFS_UCSCTL7_L) & DCOFFG) {
        // Clear OSC fault flags.
        HWREG8(UCS_BASE + OFS_UCSCTL7_L) &= ~(DCOFFG);
        // Clear OFIFG fault flag.
        HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
    }

    // Restore previous SCG0.
    __bis_SR_register(sr_reg_backup);

    if (mode == 1) {
        // Select DCOCLK because fsystem > 16000.
        HWREG16(UCS_BASE + OFS_UCSCTL4) &= ~(SELM_7 + SELS_7);
        HWREG16(UCS_BASE + OFS_UCSCTL4) |= SELM__DCOCLK + SELS__DCOCLK;
    } else {
        // Select DCODIVCLK.
        HWREG16(UCS_BASE + OFS_UCSCTL4) &= ~(SELM_7 + SELS_7);
        HWREG16(UCS_BASE + OFS_UCSCTL4) |= SELM__DCOCLKDIV + SELS__DCOCLKDIV;
    }
}

void ucs_init(enum ucs_signal signal,
              enum ucs_source source,
              enum ucs_divider divider)
{
    uint16_t source_msk = ucs_source_mask(source);
    uint16_t divider_msk = ucs_divider_mask(divider);

    switch (signal) {
    case UCS_ACLK:
        HWREG16(UCS_BASE + OFS_UCSCTL4) &= ~SELA_7;
        source_msk |= source_msk << 8;
        HWREG16(UCS_BASE + OFS_UCSCTL4) |= source_msk;
        HWREG16(UCS_BASE + OFS_UCSCTL5) &= ~DIVA_7;
        divider_msk = divider_msk << 8;
        HWREG16(UCS_BASE + OFS_UCSCTL5) |= divider_msk;
        break;
    case UCS_SMCLK:
        HWREG16(UCS_BASE + OFS_UCSCTL4) &= ~SELS_7;
        source_msk = source_msk << 4;
        HWREG16(UCS_BASE + OFS_UCSCTL4) |= source_msk;
        HWREG16(UCS_BASE + OFS_UCSCTL5) &= ~DIVS_7;
        divider_msk = divider_msk << 4;
        HWREG16(UCS_BASE + OFS_UCSCTL5) |= divider_msk;
        break;
    case UCS_MCLK:
        HWREG16(UCS_BASE + OFS_UCSCTL4) &= ~SELM_7;
        HWREG16(UCS_BASE + OFS_UCSCTL4) |= source_msk;
        HWREG16(UCS_BASE + OFS_UCSCTL5) &= ~DIVM_7;
        HWREG16(UCS_BASE + OFS_UCSCTL5) |= divider_msk;
        break;
    case UCS_FLLREF:
        HWREG8(UCS_BASE + OFS_UCSCTL3) &= ~SELREF_7;
        source_msk = source_msk << 4;
        HWREG8(UCS_BASE + OFS_UCSCTL3) |= source_msk;
        HWREG8(UCS_BASE + OFS_UCSCTL3) &= ~FLLREFDIV_7;

        switch(divider) {
        case UCS_CLOCK_DIVIDER_12:
            HWREG8(UCS_BASE + OFS_UCSCTL3) |= FLLREFDIV__12;
            break;
        case UCS_CLOCK_DIVIDER_16:
            HWREG8(UCS_BASE + OFS_UCSCTL3) |= FLLREFDIV__16;
            break;
        default:
            HWREG8(UCS_BASE + OFS_UCSCTL3) |= divider_msk;
            break;
        }
        break;
    default:
        break;
    }
}

bool ucs_xt2_blocking_turn_on(uint16_t drive, uint16_t timeout)
{
    // Check if drive value is expected one.
    if ((HWREG16(UCS_BASE + OFS_UCSCTL6) & XT2DRIVE_3) != drive) {
        // Clear XT2 drive field.
        HWREG16(UCS_BASE + OFS_UCSCTL6) &= ~XT2DRIVE_3;
        HWREG16(UCS_BASE + OFS_UCSCTL6) |= drive;
    }

    HWREG16(UCS_BASE + OFS_UCSCTL6) &= ~XT2BYPASS;
    // Switch on XT2 oscillator.
    HWREG16(UCS_BASE + OFS_UCSCTL6) &= ~XT2OFF;

    do {
        // Clear OSC fault Flags.
        HWREG8(UCS_BASE + OFS_UCSCTL7) &= ~XT2OFFG;
        // Clear OFIFG fault flag.
        HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
    } while ((HWREG8(UCS_BASE + OFS_UCSCTL7) & XT2OFFG) && --timeout);

    return timeout > 0;
}

void ucs_xt2_turn_off(void)
{
    HWREG16(UCS_BASE + OFS_UCSCTL6) |= XT2OFF;
}

void ucs_fll_settle_init(uint16_t fsystem, uint16_t ratio)
{
    volatile uint16_t x = ratio * 32;
    ucs_fll_init(fsystem, ratio);
    while (x--) {
        __delay_cycles(30);
    }
}
