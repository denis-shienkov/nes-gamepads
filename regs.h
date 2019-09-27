#ifndef FX2_REGS_H
#define FX2_REGS_H

#include "defs.h"

#ifdef __cplusplus
extern "C" {
#endif

//
// XDATA registers.
//

xdata_reg(GPIF_WAVE_DATA, 0xE400) // GPIF waveform descriptor.
xdata_reg(RES_WAVEDATA_END, 0xE480) // Reserved.

// General configuration.

xdata_reg(CPUCS, 0xE600) // Control & status.
xdata_reg(IFCONFIG, 0xE601) // Interface configuration.
xdata_reg(PINFLAGSAB, 0xE602) // FIFO FLAGA and FLAGB assignments.
xdata_reg(PINFLAGSCD, 0xE603) // FIFO FLAGC and FLAGD assignments.
xdata_reg(FIFORESET, 0xE604) // Restore FIFOS to default state.
xdata_reg(BREAKPT, 0xE605) // Breakpoint.
xdata_reg(BPADDRH, 0xE606) // Breakpoint address H.
xdata_reg(BPADDRL, 0xE607) // Breakpoint address L.
xdata_reg(UART230, 0xE608) // 230 Kbaud clock for T0,T1,T2.
xdata_reg(FIFOPINPOLAR, 0xE609) // FIFO polarities.
xdata_reg(REVID, 0xE60A) // Chip revision.
xdata_reg(REVCTL, 0xE60B) // Chip revision control.

// Endpoint configuration.

xdata_reg(EP1OUTCFG, 0xE610) // Endpoint 1-out configuration.
xdata_reg(EP1INCFG, 0xE611) // Endpoint 1-in configuration.
xdata_reg(EP2CFG, 0xE612) // Endpoint 2 configuration.
xdata_reg(EP4CFG, 0xE613) // Endpoint 4 configuration.
xdata_reg(EP6CFG, 0xE614) // Endpoint 6 configuration.
xdata_reg(EP8CFG, 0xE615) // Endpoint 8 configuration.
xdata_reg(EP2FIFOCFG, 0xE618) // Endpoint 2 FIFO configuration.
xdata_reg(EP4FIFOCFG, 0xE619) // Endpoint 4 FIFO configuration.
xdata_reg(EP6FIFOCFG, 0xE61A) // Endpoint 6 FIFO configuration.
xdata_reg(EP8FIFOCFG, 0xE61B) // Endpoint 8 FIFO configuration.
xdata_reg(EP2AUTOINLENH, 0xE620) // Endpoint 2 packet length H (in only).
xdata_reg(EP2AUTOINLENL, 0xE621) // Endpoint 2 packet length L (in only).
xdata_reg(EP4AUTOINLENH, 0xE622) // Endpoint 4 packet length H (in only).
xdata_reg(EP4AUTOINLENL, 0xE623) // Endpoint 4 packet length L (in only).
xdata_reg(EP6AUTOINLENH, 0xE624) // Endpoint 6 packet length H (in only).
xdata_reg(EP6AUTOINLENL, 0xE625) // Endpoint 6 packet length L (in only).
xdata_reg(EP8AUTOINLENH, 0xE626) // Endpoint 8 packet length H (in only).
xdata_reg(EP8AUTOINLENL, 0xE627) // Endpoint 8 packet length L (in only).
xdata_reg(EP2FIFOPFH, 0xE630) // EP2 programmable flag trigger H.
xdata_reg(EP2FIFOPFL, 0xE631) // EP2 programmable flag trigger L.
xdata_reg(EP4FIFOPFH, 0xE632) // EP4 programmable flag trigger H.
xdata_reg(EP4FIFOPFL, 0xE633) // EP4 programmable flag trigger L.
xdata_reg(EP6FIFOPFH, 0xE634) // EP6 programmable flag trigger H.
xdata_reg(EP6FIFOPFL, 0xE635) // EP6 programmable flag trigger L.
xdata_reg(EP8FIFOPFH, 0xE636) // EP8 programmable flag trigger H.
xdata_reg(EP8FIFOPFL, 0xE637) // EP8 programmable flag trigger L.
xdata_reg(EP2ISOINPKTS, 0xE640) // EP2 (if ISO) in packets per frame (1-3).
xdata_reg(EP4ISOINPKTS, 0xE641) // EP4 (if ISO) in packets per frame (1-3).
xdata_reg(EP6ISOINPKTS, 0xE642) // EP6 (if ISO) in packets per frame (1-3).
xdata_reg(EP8ISOINPKTS, 0xE643) // EP8 (if ISO) in packets per frame (1-3).
xdata_reg(INPKTEND, 0xE648) // Force in packet end.
xdata_reg(OUTPKTEND, 0xE649) // Force out packet end.

// Interrupts.

xdata_reg(EP2FIFOIE, 0xE650) // Endpoint 2 flag interrupt enable.
xdata_reg(EP2FIFOIRQ, 0xE651) // Endpoint 2 flag interrupt request.
xdata_reg(EP4FIFOIE, 0xE652) // Endpoint 4 flag interrupt enable.
xdata_reg(EP4FIFOIRQ, 0xE653) // Endpoint 4 flag interrupt request.
xdata_reg(EP6FIFOIE, 0xE654) // Endpoint 6 flag interrupt enable.
xdata_reg(EP6FIFOIRQ, 0xE655) // Endpoint 6 flag interrupt request.
xdata_reg(EP8FIFOIE, 0xE656) // Endpoint 8 flag interrupt enable.
xdata_reg(EP8FIFOIRQ, 0xE657) // Endpoint 8 flag interrupt request.
xdata_reg(IBNIE, 0xE658) // IN-BULK-NAK interrupt enable.
xdata_reg(IBNIRQ, 0xE659) // IN-BULK-NAK interrupt request.
xdata_reg(NAKIE, 0xE65A) // Endpoint ping NAK interrupt enable.
xdata_reg(NAKIRQ, 0xE65B) // Endpoint ping NAK interrupt request.
xdata_reg(USBIE, 0xE65C) // USB Int enables.
xdata_reg(USBIRQ, 0xE65D) // USB interrupt requests.
xdata_reg(EPIE, 0xE65E) // Endpoint interrupt enables.
xdata_reg(EPIRQ, 0xE65F) // Endpoint interrupt requests.
xdata_reg(GPIFIE, 0xE660) // GPIF interrupt enable.
xdata_reg(GPIFIRQ, 0xE661) // GPIF interrupt request.
xdata_reg(USBERRIE, 0xE662) // USB error interrupt enables.
xdata_reg(USBERRIRQ, 0xE663) // USB error interrupt requests.
xdata_reg(ERRCNTLIM, 0xE664) // USB error counter and limit.
xdata_reg(CLRERRCNT, 0xE665) // Clear error counter EC[3..0].
xdata_reg(INT2IVEC, 0xE666) // Interupt 2 (USB) autovector.
xdata_reg(INT4IVEC, 0xE667) // Interupt 4 (FIFOS & GPIF) autovector.
xdata_reg(INTSETUP, 0xE668) // interrupt 2 & 4 setup.

// Input/Output.

xdata_reg(PORTACFG, 0xE670) // I/O PORTA alternate configuration.
xdata_reg(PORTCCFG, 0xE671) // I/O PORTC alternate configuration.
xdata_reg(PORTECFG, 0xE672) // I/O PORTE alternate configuration.
xdata_reg(I2CS, 0xE678) // Bus control & status.
xdata_reg(I2DAT, 0xE679) // Bus data.
xdata_reg(I2CTL, 0xE67A) // Bus control.
xdata_reg(XAUTODAT1, 0xE67B) // Autoptr1 movx access.
xdata_reg(XAUTODAT2, 0xE67C) // Autoptr2 movx access.

// USB Control.

xdata_reg(USBCS, 0xE680) // USB control & status.
xdata_reg(SUSPEND, 0xE681) // Put chip into suspend.
xdata_reg(WAKEUPCS, 0xE682) // Wakeup source and polarity.
xdata_reg(TOGCTL, 0xE683) // Toggle control.
xdata_reg(USBFRAMEH, 0xE684) // USB frame count H.
xdata_reg(USBFRAMEL, 0xE685) // USB frame count L.
xdata_reg(MICROFRAME, 0xE686) // Microframe count, 0-7.
xdata_reg(FNADDR, 0xE687) // USB function address.

// Endpoints.

xdata_reg(EP0BCH, 0xE68A) // Endpoint 0 byte count H.
xdata_reg(EP0BCL, 0xE68B) // Endpoint 0 byte count L.
xdata_reg(EP1OUTBC, 0xE68D) // Endpoint 1 out byte count.
xdata_reg(EP1INBC, 0xE68F) // Endpoint 1 in byte count.
xdata_reg(EP2BCH, 0xE690) // Endpoint 2 byte count H.
xdata_reg(EP2BCL, 0xE691) // Endpoint 2 byte count L.
xdata_reg(EP4BCH, 0xE694) // Endpoint 4 byte count H.
xdata_reg(EP4BCL, 0xE695) // Endpoint 4 byte count L.
xdata_reg(EP6BCH, 0xE698) // Endpoint 6 byte count H.
xdata_reg(EP6BCL, 0xE699) // Endpoint 6 byte count L.
xdata_reg(EP8BCH, 0xE69C) // Endpoint 8 byte count H.
xdata_reg(EP8BCL, 0xE69D) // Endpoint 8 byte count L.
xdata_reg(EP0CS, 0xE6A0) // Endpoint control and status.
xdata_reg(EP1OUTCS, 0xE6A1) // Endpoint 1 out control and status.
xdata_reg(EP1INCS, 0xE6A2) // Endpoint 1 in control and status.
xdata_reg(EP2CS, 0xE6A3) // Endpoint 2 control and status.
xdata_reg(EP4CS, 0xE6A4) // Endpoint 4 control and status.
xdata_reg(EP6CS, 0xE6A5) // Endpoint 6 control and status.
xdata_reg(EP8CS, 0xE6A6) // Endpoint 8 control and status.
xdata_reg(EP2FIFOFLGS, 0xE6A7) // Endpoint 2 flags.
xdata_reg(EP4FIFOFLGS, 0xE6A8) // Endpoint 4 flags.
xdata_reg(EP6FIFOFLGS, 0xE6A9) // Endpoint 6 flags.
xdata_reg(EP8FIFOFLGS, 0xE6AA) // Endpoint 8 flags.
xdata_reg(EP2FIFOBCH, 0xE6AB) // EP2 FIFO total byte count H.
xdata_reg(EP2FIFOBCL, 0xE6AC) // EP2 FIFO total byte count L.
xdata_reg(EP4FIFOBCH, 0xE6AD) // EP4 FIFO total byte count H.
xdata_reg(EP4FIFOBCL, 0xE6AE) // EP4 FIFO total byte count L.
xdata_reg(EP6FIFOBCH, 0xE6AF) // EP6 FIFO total byte count H.
xdata_reg(EP6FIFOBCL, 0xE6B0) // EP6 FIFO total byte count L.
xdata_reg(EP8FIFOBCH, 0xE6B1) // EP8 FIFO total byte count H.
xdata_reg(EP8FIFOBCL, 0xE6B2) // EP8 FIFO total byte count L.
xdata_reg(SUDPTRH, 0xE6B3) // Setup data pointer high address byte.
xdata_reg(SUDPTRL, 0xE6B4) // Setup data pointer low address byte.
xdata_reg(SUDPTRCTL, 0xE6B5) // Setup data pointer auto mode.
xdata_reg(SETUPDAT[8], 0xE6B8) // 8 bytes of setup data.

// GPIF.

xdata_reg(GPIFWFSELECT, 0xE6C0) // Waveform selector.
xdata_reg(GPIFIDLECS, 0xE6C1) // GPIF done, GPIF idle drive mode.
xdata_reg(GPIFIDLECTL, 0xE6C2) // Inactive bus, ctl states.
xdata_reg(GPIFCTLCFG, 0xE6C3) // CTL out pin drive.
xdata_reg(GPIFADRH, 0xE6C4) // GPIF address H.
xdata_reg(GPIFADRL, 0xE6C5) // GPIF address L.

xdata_reg(GPIFTCB3, 0xE6CE) // GPIF transaction count byte 3.
xdata_reg(GPIFTCB2, 0xE6CF) // GPIF transaction count byte 2.
xdata_reg(GPIFTCB1, 0xE6D0) // GPIF transaction count byte 1.
xdata_reg(GPIFTCB0, 0xE6D1) // GPIF transaction count byte 0.

xdata_reg(EP2GPIFFLGSEL, 0xE6D2) // EP2 GPIF flag select.
xdata_reg(EP2GPIFPFSTOP, 0xE6D3) // Stop GPIF EP2 transaction on prog flag.
xdata_reg(EP2GPIFTRIG, 0xE6D4) // EP2 FIFO trigger.
xdata_reg(EP4GPIFFLGSEL, 0xE6DA) // EP4 GPIF flag select.
xdata_reg(EP4GPIFPFSTOP, 0xE6DB) // Stop GPIF EP4 transaction on prog flag.
xdata_reg(EP4GPIFTRIG, 0xE6DC) // EP4 FIFO trigger.
xdata_reg(EP6GPIFFLGSEL, 0xE6E2) // EP6 GPIF Flag select.
xdata_reg(EP6GPIFPFSTOP, 0xE6E3) // Stop GPIF EP6 transaction on prog flag.
xdata_reg(EP6GPIFTRIG, 0xE6E4) // EP6 FIFO trigger.
xdata_reg(EP8GPIFFLGSEL, 0xE6EA) // EP8 GPIF flag select.
xdata_reg(EP8GPIFPFSTOP, 0xE6EB) // Stop GPIF EP8 transaction on prog flag.
xdata_reg(EP8GPIFTRIG, 0xE6EC) // EP8 FIFO trigger.
xdata_reg(XGPIFSGLDATH, 0xE6F0) // GPIF data H (16-bit mode only).
xdata_reg(XGPIFSGLDATLX, 0xE6F1) // Read/write GPIF data L & trigger transac.
xdata_reg(XGPIFSGLDATLNOX, 0xE6F2) // Read GPIF data L, no transac trigger.
xdata_reg(GPIFREADYCFG, 0xE6F3) // Internal RDY,Sync/Async, RDY5CFG.
xdata_reg(GPIFREADYSTAT, 0xE6F4) // RDY pin states.
xdata_reg(GPIFABORT, 0xE6F5) // Abort GPIF cycles.

// UDMA.

xdata_reg(FLOWSTATE, 0xE6C6) // Defines GPIF flow state.
xdata_reg(FLOWLOGIC, 0xE6C7) // Defines flow/hold decision criteria.
xdata_reg(FLOWEQ0CTL, 0xE6C8) // CTL states during active flow state.
xdata_reg(FLOWEQ1CTL, 0xE6C9) // CTL states during hold flow state.
xdata_reg(FLOWHOLDOFF, 0xE6CA) // Holdoff configuration.
xdata_reg(FLOWSTB, 0xE6CB) // CTL/RDY signal to use as master data strobe.
xdata_reg(FLOWSTBEDGE, 0xE6CC) // Defines active master strobe edge.
xdata_reg(FLOWSTBHPERIOD, 0xE6CD) // Half period of output master strobe.
xdata_reg(GPIFHOLDAMOUNT, 0xE60C) // Data delay shift.
xdata_reg(UDMACRCH, 0xE67D) // CRC upper byte.
xdata_reg(UDMACRCL, 0xE67E) // CRC lower byte.
xdata_reg(UDMACRCQUAL, 0xE67F) // UDMA in only, host terminated use only.

// Endpoint buffers.
#define MAX_EP0_SIZE 64
#define MAX_EP1_SIZE 64
#define MAX_EP2468_SIZE 1024

xdata_reg(EP0BUF[MAX_EP0_SIZE], 0xE740) // EP0 buffer (in or out).
xdata_reg(EP1OUTBUF[MAX_EP1_SIZE], 0xE780) // EP1 buffer (out only).
xdata_reg(EP1INBUF[MAX_EP1_SIZE], 0xE7C0) // EP1 buffer (in only).
xdata_reg(EP2FIFOBUF[MAX_EP2468_SIZE], 0xF000) // 512/1024-byte EP2 buffer (in or out).
xdata_reg(EP4FIFOBUF[MAX_EP2468_SIZE], 0xF400) // 512 byte EP4 buffer (in or out).
xdata_reg(EP6FIFOBUF[MAX_EP2468_SIZE], 0xF800) // 512/1024-byte EP6 buffer (in or out).
xdata_reg(EP8FIFOBUF[MAX_EP2468_SIZE], 0xFC00) // 512 byte EP8 buffer (in or out).

// Error correction code (ECC) registers (FX2LP/FX1 only).

xdata_reg(ECCCFG, 0xE628) // ECC configuration.
xdata_reg(ECCRESET, 0xE629) // ECC reset.
xdata_reg(ECC1B0, 0xE62A) // ECC1 byte 0.
xdata_reg(ECC1B1, 0xE62B) // ECC1 byte 1.
xdata_reg(ECC1B2, 0xE62C) // ECC1 byte 2.
xdata_reg(ECC2B0, 0xE62D) // ECC2 byte 0.
xdata_reg(ECC2B1, 0xE62E) // ECC2 byte 1.
xdata_reg(ECC2B2, 0xE62F) // ECC2 byte 2.

// Feature registers(FX2LP/FX1 only).

xdata_reg(GPCR2, 0xE50D) // Chip features.

//
// SFR registers.
//

special_function_reg(IOA, 0x80) // Port A.
special_function_reg_bit(PA0, 0x80, 0)
special_function_reg_bit(PA1, 0x80, 1)
special_function_reg_bit(PA2, 0x80, 2)
special_function_reg_bit(PA3, 0x80, 3)
special_function_reg_bit(PA4, 0x80, 4)
special_function_reg_bit(PA5, 0x80, 5)
special_function_reg_bit(PA6, 0x80, 6)
special_function_reg_bit(PA7, 0x80, 7)

special_function_reg(SP, 0x81) // Stack pointer.
special_function_reg(DPL, 0x82) // Data pointer 0 L.
special_function_reg(DPH, 0x83) // Data pointer 0 H.
special_function_reg(DPL1, 0x84) // Data pointer 1 L.
special_function_reg(DPH1, 0x85) // Data pointer 1 L.
special_function_reg(DPS, 0x86) // Data pointer 0/1 select.
special_function_reg(PCON, 0x87) // Power control.

special_function_reg(TCON, 0x88) // Timer/counter control.
special_function_reg_bit(IT0, 0x88, 0)
special_function_reg_bit(IE0, 0x88, 1)
special_function_reg_bit(IT1, 0x88, 2)
special_function_reg_bit(IE1, 0x88, 3)
special_function_reg_bit(TR0, 0x88, 4)
special_function_reg_bit(TF0, 0x88, 5)
special_function_reg_bit(TR1, 0x88, 6)
special_function_reg_bit(TF1, 0x88, 7)

special_function_reg(TMOD, 0x89) // Timer/counter mode control.
special_function_reg(TL0, 0x8A) // Timer 0 reload L.
special_function_reg(TL1, 0x8B) // Timer 1 reload L.
special_function_reg(TH0, 0x8C) // Timer 0 reload H.
special_function_reg(TH1, 0x8D) // Timer 1 reload H.
special_function_reg(CKCON, 0x8E) // Clock control.

special_function_reg(IOB, 0x90) // Port B.
special_function_reg_bit(PB0, 0x90, 0)
special_function_reg_bit(PB1, 0x90, 1)
special_function_reg_bit(PB2, 0x90, 2)
special_function_reg_bit(PB3, 0x90, 3)
special_function_reg_bit(PB4, 0x90, 4)
special_function_reg_bit(PB5, 0x90, 5)
special_function_reg_bit(PB6, 0x90, 6)
special_function_reg_bit(PB7, 0x90, 7)

special_function_reg(EXIF, 0x91) // External interrupt flag.
special_function_reg(MPAGE, 0x92) // Upper address page of movx.

special_function_reg(SCON0, 0x98) // Serial port 0 control.
special_function_reg_bit(RI, 0x98, 0)
special_function_reg_bit(TI, 0x98, 1)
special_function_reg_bit(RB8, 0x98, 2)
special_function_reg_bit(TB8, 0x98, 3)
special_function_reg_bit(REN, 0x98, 4)
special_function_reg_bit(SM2, 0x98, 5)
special_function_reg_bit(SM1, 0x98, 6)
special_function_reg_bit(SM0, 0x98, 7)

special_function_reg(SBUF0, 0x99) // Serial port 0 data buffer.

special_function_reg(AUTOPTRH1, 0x9A) // Auto-pointer 1 address H.
special_function_reg(AUTOPTRL1, 0x9B) // Auto-pointer 1 address L.
special_function_reg(AUTOPTRH2, 0x9D) // Auto-pointer 2 address H.
special_function_reg(AUTOPTRL2, 0x9E) // Auto-pointer 2 address L.

special_function_reg(IOC, 0xA0) // Port C.
special_function_reg_bit(PC0, 0xA0, 0)
special_function_reg_bit(PC1, 0xA0, 1)
special_function_reg_bit(PC2, 0xA0, 2)
special_function_reg_bit(PC3, 0xA0, 3)
special_function_reg_bit(PC4, 0xA0, 4)
special_function_reg_bit(PC5, 0xA0, 5)
special_function_reg_bit(PC6, 0xA0, 6)
special_function_reg_bit(PC7, 0xA0, 7)

special_function_reg(INT2CLR, 0xA1) // Interrupt 2 clear.
special_function_reg(INT4CLR, 0xA2) // Interrupt 4 clear.

special_function_reg(IE, 0xA8) // Interrupt enable.
special_function_reg_bit(EX0, 0xA8, 0)
special_function_reg_bit(ET0, 0xA8, 1)
special_function_reg_bit(EX1, 0xA8, 2)
special_function_reg_bit(ET1, 0xA8, 3)
special_function_reg_bit(ES0, 0xA8, 4)
special_function_reg_bit(ET2, 0xA8, 5)
special_function_reg_bit(ES1, 0xA8, 6)
special_function_reg_bit(EA, 0xA8, 7)

special_function_reg(EP2468STAT, 0xAA) // Endpoint 2,4,6,8 status flags.
special_function_reg(EP24FIFOFLGS, 0xAB) // Endpoint 2,4 slave FIFO status flags.
special_function_reg(EP68FIFOFLGS, 0xAC) // Endpoint 6,8 slave FIFO status flags.
special_function_reg(AUTOPTRSETUP, 0xAF) // Auto-pointer 1,2 setup.

special_function_reg(IOD, 0xB0) // Port D.
special_function_reg_bit(PD0, 0xB0, 0)
special_function_reg_bit(PD1, 0xB0, 1)
special_function_reg_bit(PD2, 0xB0, 2)
special_function_reg_bit(PD3, 0xB0, 3)
special_function_reg_bit(PD4, 0xB0, 4)
special_function_reg_bit(PD5, 0xB0, 5)
special_function_reg_bit(PD6, 0xB0, 6)
special_function_reg_bit(PD7, 0xB0, 7)

special_function_reg(IOE, 0xB1) // Port E.

special_function_reg(OEA, 0xB2) // Port A out enable.
special_function_reg(OEB, 0xB3) // Port B out enable.
special_function_reg(OEC, 0xB4) // Port C out enable.
special_function_reg(OED, 0xB5) // Port D out enable.
special_function_reg(OEE, 0xB6) // Port E out enable.

special_function_reg(IP, 0xB8) // Interrupt prority.
special_function_reg_bit(PX0, 0xB8, 0)
special_function_reg_bit(PT0, 0xB8, 1)
special_function_reg_bit(PX1, 0xB8, 2)
special_function_reg_bit(PT1, 0xB8, 3)
special_function_reg_bit(PS0, 0xB8, 4)
special_function_reg_bit(PT2, 0xB8, 5)
special_function_reg_bit(PS1, 0xB8, 6)

special_function_reg(EP01STAT, 0xBA) // Endpoint 0,1 status.
special_function_reg(GPIFTRIG, 0xBB) // Endpoint 2,4,6,8 GPIF slave FIFO trigger.

special_function_reg(GPIFSGLDATH, 0xBD) // GPIF data H.
special_function_reg(GPIFSGLDATLX, 0xBE) // GPIF data L with trigger.
special_function_reg(GPIFSGLDATLNOX, 0xBF) // GPIF data L without trigger.

special_function_reg(SCON1, 0xC0) // Serial port 1 control.
special_function_reg_bit(RI1, 0xC0, 0)
special_function_reg_bit(TI1, 0xC0, 1)
special_function_reg_bit(RB81, 0xC0, 2)
special_function_reg_bit(TB81, 0xC0, 3)
special_function_reg_bit(REN1, 0xC0, 4)
special_function_reg_bit(SM21, 0xC0, 5)
special_function_reg_bit(SM11, 0xC0, 6)
special_function_reg_bit(SM01, 0xC0, 7)

special_function_reg(SBUF1, 0xC1) // Serial port 1 data buffer.

special_function_reg(T2CON, 0xC8) // Timer/counter 2 control.
special_function_reg_bit(CP_RL2, 0xC8, 0)
special_function_reg_bit(C_T2, 0xC8, 1)
special_function_reg_bit(TR2, 0xC8, 2)
special_function_reg_bit(EXEN2, 0xC8, 3)
special_function_reg_bit(TCLK, 0xC8, 4)
special_function_reg_bit(RCLK, 0xC8, 5)
special_function_reg_bit(EXF2, 0xC8, 6)
special_function_reg_bit(TF2, 0xC8, 7)

special_function_reg(RCAP2L, 0xCA) // Capture for timer 2 auto-reload up-counter L.
special_function_reg(RCAP2H, 0xCB) // Capture for timer 2 auto-reload up-counter H.
special_function_reg(TL2, 0xCC) // Timer 2 reload L.
special_function_reg(TH2, 0xCD) // Timer 2 reload H.

special_function_reg(PSW, 0xD0) // Program status word.
special_function_reg_bit(P, 0xD0, 0)
special_function_reg_bit(FL, 0xD0, 1)
special_function_reg_bit(OV, 0xD0, 2)
special_function_reg_bit(RS0, 0xD0, 3)
special_function_reg_bit(RS1, 0xD0, 4)
special_function_reg_bit(F0, 0xD0, 5)
special_function_reg_bit(AC, 0xD0, 6)
special_function_reg_bit(CY, 0xD0, 7)

special_function_reg(EICON, 0xD8) // External interrupt control.
special_function_reg_bit(INT6, 0xD8, 3)
special_function_reg_bit(RESI, 0xD8, 4)
special_function_reg_bit(ERESI, 0xD8, 5)
special_function_reg_bit(SMOD1, 0xD8, 7)

special_function_reg(ACC, 0xE0) // Accumulator.

special_function_reg(EIE, 0xE8) // External interrupt enable.
special_function_reg_bit(EUSB, 0xE8, 0)
special_function_reg_bit(EI2C, 0xE8, 1)
special_function_reg_bit(EIEX4, 0xE8, 2)
special_function_reg_bit(EIEX5, 0xE8, 3)
special_function_reg_bit(EIEX6, 0xE8, 4)

special_function_reg(B, 0xF0) // B

special_function_reg(EIP, 0xF8) // External interrupt priority control.
special_function_reg_bit(PUSB, 0xF8, 0)
special_function_reg_bit(PI2C, 0xF8, 1)
special_function_reg_bit(EIPX4, 0xF8, 2)
special_function_reg_bit(EIPX5, 0xF8, 3)
special_function_reg_bit(EIPX6, 0xF8, 4)

//
// Register bit masks.
//

// CPU control & status register (CPUCS).
enum cpucs_bits {
    MSK_CPUCS_PRTCSTB = MSK_BIT5,
    MSK_CPUCS_CLKSPD = MSK_BIT4 | MSK_BIT3,
    MSK_CPUCS_CLKSPD1 = MSK_BIT4,
    MSK_CPUCS_CLKSPD0 = MSK_BIT3,
    MSK_CPUCS_CLKINV = MSK_BIT2,
    MSK_CPUCS_CLKOE = MSK_BIT1,
    MSK_CPUCS_8051RES = MSK_BIT0
};

// Port A (PORTACFG).
enum portacfg_bits {
    MSK_PORTACFG_FLAGD = MSK_BIT7,
    MSK_PORTACFG_INT1 = MSK_BIT1,
    MSK_PORTACFG_INT0 = MSK_BIT0
};

// Port C (PORTCCFG).
enum portccfg_bits {
    MSK_PORTCCFG_GPIFA7 = MSK_BIT7,
    MSK_PORTCCFG_GPIFA6 = MSK_BIT6,
    MSK_PORTCCFG_GPIFA5 = MSK_BIT5,
    MSK_PORTCCFG_GPIFA4 = MSK_BIT4,
    MSK_PORTCCFG_GPIFA3 = MSK_BIT3,
    MSK_PORTCCFG_GPIFA2 = MSK_BIT2,
    MSK_PORTCCFG_GPIFA1 = MSK_BIT1,
    MSK_PORTCCFG_GPIFA0 = MSK_BIT0
};

// Port E (PORTECFG).
enum portecfg_bits {
    MSK_PORTECFG_GPIFA8 = MSK_BIT7,
    MSK_PORTECFG_T2EX = MSK_BIT6,
    MSK_PORTECFG_INT6 = MSK_BIT5,
    MSK_PORTECFG_RXD1OUT = MSK_BIT4,
    MSK_PORTECFG_RXD0OUT = MSK_BIT3,
    MSK_PORTECFG_T2OUT = MSK_BIT2,
    MSK_PORTECFG_T1OUT = MSK_BIT1,
    MSK_PORTECFG_T0OUT = MSK_BIT0
};

// I2C control & status register (I2CS).
enum i2cs_bits {
    MSK_I2CS_START = MSK_BIT7,
    MSK_I2CS_STOP = MSK_BIT6,
    MSK_I2CS_LASTRD = MSK_BIT5,
    MSK_I2CS_ID = MSK_BIT4 | MSK_BIT3,
    MSK_I2CS_BERR = MSK_BIT2,
    MSK_I2CS_ACK = MSK_BIT1,
    MSK_I2CS_DONE = MSK_BIT0
};

// I2C control register (I2CTL).
enum i2ctl_bits {
    MSK_I2CTL_STOPIE = MSK_BIT1,
    MSK_I2CTL_400KHZ = MSK_BIT0
};

// Interrupt 2 (USB) autovector register (INT2IVEC).
enum int2ivec_bits {
    MSK_INT2IVEC_IV4 = MSK_BIT6,
    MSK_INT2IVEC_IV3 = MSK_BIT5,
    MSK_INT2IVEC_IV2 = MSK_BIT4,
    MSK_INT2IVEC_IV1 = MSK_BIT3,
    MSK_INT2IVEC_IV0 = MSK_BIT2
};

// USB interrupt request & enable registers (USBIE/USBIRQ).
enum usbieirq_bits {
    MSK_USBIEIRQ_EP0ACK = MSK_BIT6,
    MSK_USBIEIRQ_HSGRANT = MSK_BIT5,
    MSK_USBIEIRQ_URES = MSK_BIT4,
    MSK_USBIEIRQ_SUSP = MSK_BIT3,
    MSK_USBIEIRQ_SUTOK = MSK_BIT2,
    MSK_USBIEIRQ_SOF = MSK_BIT1,
    MSK_USBIEIRQ_SUDAV = MSK_BIT0
};

// End point interrupt request & enable registers (EPIE/EPIRQ).
enum epieirq_bits {
    MSK_EPIEIRQ_EP0IN  = MSK_BIT0,
    MSK_EPIEIRQ_EP0OUT = MSK_BIT1,
    MSK_EPIEIRQ_EP1IN  = MSK_BIT2,
    MSK_EPIEIRQ_EP1OUT = MSK_BIT3
};

// Breakpoint register (BREAKPT).
enum breakpt_bits {
    MSK_BREAKPT_BREAK = MSK_BIT3,
    MSK_BREAKPT_BPPULSE = MSK_BIT2,
    MSK_BREAKPT_BPEN = MSK_BIT1
};

// Interrupt 2 & 4 setup (INTSETUP).
enum intsetup_bits {
    MSK_INTSETUP_AV2EN = MSK_BIT3,
    MSK_INTSETUP_INT4SRC = MSK_BIT1,
    MSK_INTSETUP_AV4EN = MSK_BIT0
};

// USB control & status register (USBCS).
enum usbcs_bits {
    MSK_USBCS_HSM = MSK_BIT7,
    MSK_USBCS_DISCON = MSK_BIT3,
    MSK_USBCS_NOSYNSOF = MSK_BIT2,
    MSK_USBCS_RENUM = MSK_BIT1,
    MSK_USBCS_SIGRESUME = MSK_BIT0
};

// Wakeup control and status register (WAKEUPCS).
enum wakeupcs_bits {
    MSK_WAKEUPCS_WU2 = MSK_BIT7,
    MSK_WAKEUPCS_WU = MSK_BIT6,
    MSK_WAKEUPCS_WU2POL = MSK_BIT5,
    MSK_WAKEUPCS_WUPOL = MSK_BIT4,
    MSK_WAKEUPCS_DPEN = MSK_BIT2,
    MSK_WAKEUPCS_WU2EN = MSK_BIT1,
    MSK_WAKEUPCS_WUEN = MSK_BIT0
};

// End point 0 control & status register (EP0CS).
enum ep0cs_bits {
    MSK_EP0CS_HSNAK = MSK_BIT7
};

// End point 0-1 control & status registers
// (EP0CS/EP1OUTCS/EP1INCS).
enum ep01cs_bits {
    MSK_EP01CS_EPBUSY = MSK_BIT1,
    MSK_EP01CS_EPSTALL = MSK_BIT0
};

// End point 2-8 Control & status registers
// (EP2CS/EP4CS/EP6CS/EP8CS).
enum ep2468cs_bits {
    MSK_EP2468CS_NPAK = MSK_BIT6 | MSK_BIT5 | MSK_BIT4,
    MSK_EP2468CS_EPFULL = MSK_BIT3,
    MSK_EP2468CS_EPEMPTY = MSK_BIT2
};

// End point status SFR bits (EP2468STAT).
enum ep2468stat_bits {
    MSK_EP2468STAT_EP8FULL = MSK_BIT7,
    MSK_EP2468STAT_EP8EMPTY = MSK_BIT6,
    MSK_EP2468STAT_EP6FULL = MSK_BIT5,
    MSK_EP2468STAT_EP6EMPTY = MSK_BIT4,
    MSK_EP2468STAT_EP4FULL = MSK_BIT3,
    MSK_EP2468STAT_EP4EMPTY = MSK_BIT2,
    MSK_EP2468STAT_EP2FULL = MSK_BIT1,
    MSK_EP2468STAT_EP2EMPTY = MSK_BIT0
};

// End point 0,1 status bits (EP01STAT).
enum ep01stat_bits {
    MSK_EP01STAT_EP1INBSY = MSK_BIT2,
    MSK_EP01STAT_EP1OUTBSY = MSK_BIT1,
    MSK_EP01STAT_EP0BSY = MSK_BIT0
};

// Setup data pointer auto mode (SUDPTRCTL).
enum sudptrctl_bits {
    MSK_SUDPTRCTL_SDPAUTO = MSK_BIT0
};

// End point data toggle control (TOGCTL).
enum togctl_bits {
    MSK_TOGCTL_QUERYTOGGLE = MSK_BIT7,
    MSK_TOGCTL_SETTOGGLE = MSK_BIT6,
    MSK_TOGCTL_RESETTOGGLE = MSK_BIT5,
    MSK_TOGCTL_TOGCTLEPMASK = MSK_BIT3 | MSK_BIT2 | MSK_BIT1 | MSK_BIT0
};

// In bulk NAK enable and request bits (IBNIE/IBNIRQ).
enum ibnieirq_bits {
    MSK_IBNIEIRQ_EP8IBN = MSK_BIT5,
    MSK_IBNIEIRQ_EP6IBN = MSK_BIT4,
    MSK_IBNIEIRQ_EP4IBN = MSK_BIT3,
    MSK_IBNIEIRQ_EP2IBN = MSK_BIT2,
    MSK_IBNIEIRQ_EP1IBN = MSK_BIT1,
    MSK_IBNIEIRQ_EP0IBN = MSK_BIT0
};

// Ping NAK enable and request bits (NAKIE/NAKIRQ).
enum nakieirq_bits {
    MSK_NAKIEIRQ_EP8PING = MSK_BIT7,
    MSK_NAKIEIRQ_EP6PING = MSK_BIT6,
    MSK_NAKIEIRQ_EP4PING = MSK_BIT5,
    MSK_NAKIEIRQ_EP2PING = MSK_BIT4,
    MSK_NAKIEIRQ_EP1PING = MSK_BIT3,
    MSK_NAKIEIRQ_EP0PING = MSK_BIT2,
    MSK_NAKIEIRQ_IBN = MSK_BIT0
};

// Interface configuration bits (IFCONFIG).
enum ifconfig_bits {
    MSK_IFCONFIG_IFCLKSRC = MSK_BIT7,
    MSK_IFCONFIG_3048MHZ = MSK_BIT6,
    MSK_IFCONFIG_IFCLKOE = MSK_BIT5,
    MSK_IFCONFIG_IFCLKPOL = MSK_BIT4,
    MSK_IFCONFIG_ASYNC = MSK_BIT3,
    MSK_IFCONFIG_GSTATE = MSK_BIT2,
    MSK_IFCONFIG_IFCFG1 = MSK_BIT1,
    MSK_IFCONFIG_IFCFG0 = MSK_BIT0,
    MSK_IFCONFIG_IFCFGMASK = MSK_IFCONFIG_IFCFG0 | MSK_IFCONFIG_IFCFG1,
    MSK_IFCONFIG_IFGPIF = MSK_IFCONFIG_IFCFG1
};

// End point 2,4,6,8 FIFO configuration bits
// (EP2FIFOCFG,EP4FIFOCFG,EP6FIFOCFG,EP8FIFOCFG).
enum ep2468fifocfg_bits {
    MSK_EP2468FIFOCFG_INFM = MSK_BIT6,
    MSK_EP2468FIFOCFG_OEP = MSK_BIT5,
    MSK_EP2468FIFOCFG_AUTOOUT = MSK_BIT4,
    MSK_EP2468FIFOCFG_AUTOIN = MSK_BIT3,
    MSK_EP2468FIFOCFG_ZEROLENIN = MSK_BIT2,
    MSK_EP2468FIFOCFG_WORDWIDE = MSK_BIT0
};

// Chip revision control bits (REVCTL).
enum revctl_bits {
    MSK_REVCTL_NOAUTOARM = MSK_BIT1,
    MSK_REVCTL_SKIPCOMMIT = MSK_BIT0
};

// Fifo reset bits (FIFORESET).
enum fiforeset_bits {
    MSK_FIFORESET_NAKALL = MSK_BIT7,
    MSK_FIFORESET_EP3 = MSK_BIT3,
    MSK_FIFORESET_EP2 = MSK_BIT2,
    MSK_FIFORESET_EP1 = MSK_BIT1,
    MSK_FIFORESET_EP0 = MSK_BIT0
};

// Chip feature register (GPCR2).
enum gpcr2_bits {
    MSK_GPCR2_FULLSPEEDONLY = MSK_BIT4
};

// Clock control register (CKCON).
// Note: a RevE errata states that stretch must=0
// to set OUTxBC.
enum ckcon_bits {
    MSK_CKCON_STRETCH = 0x07,
    // Set stretch to 0 in frameworks.
    MSK_CKCON_FW_STRETCH_VALUE = 0x0
};

// External interrupt flags (EXIF).
enum exif_bits {
    MSK_EXIF_IE5 = MSK_BIT7,
    MSK_EXIF_IE4 = MSK_BIT6,
    MSK_EXIF_I2CINT = MSK_BIT5,
    MSK_EXIF_USBNT = MSK_BIT4
};

// External interrupt control (EICON).
enum eicon_bits {
    MSK_EICON_SMOD1 = MSK_BIT7,
    MSK_EICON_ERESI = MSK_BIT5,
    MSK_EICON_RESI = MSK_BIT4,
    MSK_EICON_INT6 = MSK_BIT3
};

// Power control (PCON).
enum pcon_bits {
    MSK_PCON_SMOD0 = MSK_BIT7,
    MSK_PCON_IDLE = MSK_BIT0
};

// Autopointer 1 & 2 setup (AUTOPTRSETUP).
enum autoptrsetup_bits {
    MSK_AUTOPTRSETUP_APTR2INC = MSK_BIT2,
    MSK_AUTOPTRSETUP_APTR1INC = MSK_BIT1,
    MSK_AUTOPTRSETUP_APTREN = MSK_BIT0
};

#ifdef __cplusplus
}
#endif

#endif // FX2_REGS_H
