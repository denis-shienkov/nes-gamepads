#ifndef FX2_HW_H
#define FX2_HW_H

#include "defs.h"

#ifdef __cplusplus
extern "C" {
#endif

// Allowed range: 5000 - 48000.
#ifndef CORE_IFREQ
#  define CORE_IFREQ 48000 // IFCLK frequency in kHz.
#endif

// Allowed values: 48000, 24000, or 12000.
#ifndef CORE_CFREQ
#  define CORE_CFREQ 48000 // CLKOUT frequency in kHz.
#endif

#if (CORE_IFREQ < 5000)
#  error "CORE_IFREQ too small! Valid range: 5000 - 48000."
#endif

#if (CORE_IFREQ > 48000)
#  error "CORE_IFREQ too large! Valid range: 5000 - 48000."
#endif

#if (CORE_CFREQ != 48000)
#  if (CORE_CFREQ != 24000)
#    if (CORE_CFREQ != 12000)
#      error "CORE_CFREQ invalid! Valid values: 48000, 24000, 12000."
#    endif
#  endif
#endif

// Calculate synchronization delay.
#define CORE_SCYCL (3 * (CORE_CFREQ) + 5 * (CORE_IFREQ) - 1) / (2 * (CORE_IFREQ))

#if (CORE_SCYCL == 1)
#  define sync_delay() {\
    NOP__(); }
#endif

#if (CORE_SCYCL == 2)
#  define sync_delay() {\
    NOP__(); \
    NOP__(); }
#endif

#if (CORE_SCYCL == 3)
#  define sync_delay() {\
    NOP__(); \
    NOP__(); \
    NOP__(); }
#endif

#if (CORE_SCYCL == 4)
#  define sync_delay() {\
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); }
#endif

#if (CORE_SCYCL == 5)
#  define sync_delay() {\
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); }
#endif

#if (CORE_SCYCL == 6)
#  define sync_delay() {\
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); }
#endif

#if (CORE_SCYCL == 7)
#  define sync_delay() {\
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); }
#endif

#if (CORE_SCYCL == 8)
#  define sync_delay() {\
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); }
#endif

#if (CORE_SCYCL == 9)
#  define sync_delay() {\
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); }
#endif

#if (CORE_SCYCL == 10)
#  define sync_delay() {\
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); }
#endif

#if (CORE_SCYCL == 11)
#  define sync_delay() {\
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); }
#endif

#if (CORE_SCYCL == 12)
#  define sync_delay() {\
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); }
#endif

#if (CORE_SCYCL == 13)
#  define sync_delay() {\
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); }
#endif

#if (CORE_SCYCL == 14)
#  define sync_delay() {\
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); }
#endif

#if (CORE_SCYCL == 15)
#  define sync_delay() {\
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); }
#endif

#if (CORE_SCYCL == 16)
#  define sync_delay() {\
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); \
    NOP__(); }
#endif

void core_init(void);
void core_delay(WORD msec);

#ifdef __cplusplus
}
#endif

#endif // FX2_HW_H
