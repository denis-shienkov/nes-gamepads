#ifndef MSP430_PMM_H
#define MSP430_PMM_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

enum ppm_voltage {
    PMM_VOLTAGE_1_35V,
    PMM_VOLTAGE_1_55V,
    PMM_VOLTAGE_1_75V,
    PMM_VOLTAGE_1_85V
};

bool pmm_voltage_init(enum ppm_voltage voltage);

#ifdef __cplusplus
}
#endif

#endif // MSP430_PMM_H
