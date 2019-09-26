#include "fx2hw.h"
#include "fx2regs.h"

enum cpu_freq_clk {
    CPU_CLK_12M = 0,
    CPU_CLK_24M,
    CPU_CLK_48M
};

#define cpu_freq_clk_get() \
    ((CPUCS & MSK_CPUCS_CLKSPD) >> 3)

#define cpu_freq_clk_set(freq_clk) \
    CPUCS = (CPUCS & ~MSK_CPUCS_CLKSPD) | (freq_clk << 3)

void hw_init(void)
{
    // Set the CPU clock to 48MHz.
    cpu_freq_clk_set(CPU_CLK_48M);
    sync_delay();
    // Set the slave FIFO interface to 48MHz.
    IFCONFIG |= MSK_IFCONFIG_3048MHZ;
    sync_delay();
}

void hw_delay(WORD msecs)
{
    const WORD clk = cpu_freq_clk_get();
    const WORD loop_count = (clk == CPU_CLK_12M)
            ? 177 : (clk == CPU_CLK_24M)
              ? 353 : 706;

    do {
        volatile WORD count = loop_count;
        do {
        } while (--count);
    } while (--msecs);
}