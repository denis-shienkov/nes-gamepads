.module fx2jmptable

.globl  _usb_int2_autovector
.globl  _gpif_int4_autovector
.globl  _jmp_table
.globl  _usb_sudav_isr
.globl  _usb_sutok_isr
.globl  _usb_sof_isr
.globl  _usb_ures_isr
.globl  _usb_susp_isr
.globl  _usb_hispeed_isr
.globl  _usb_stub_isr

;; USB interrupt vector (USBINT).
.area   INT2AV (ABS,OVR)
.org    0x43
_usb_int2_autovector = #. + 2
    ljmp _jmp_table ; Autovector will replace byte 45.

;; GPIG/FIFOs/INT4 pin interrupt vector (IE4).
.area   INT4AV (ABS,OVR)
.org    0x53
_gpif_int4_autovector = #. + 2
    ljmp _jmp_table ; Autovector will replace byte 55.

;; USB && FIFO/GPIF jump table.

.area _jmp_table (CODE)

_jmp_table:

;; int2 jump table
    ljmp    _usb_sudav_isr    ; (00) Setup data available.
    .db 0
    ljmp    _usb_sof_isr      ; (04) Start of frame.
    .db 0
    ljmp    _usb_sutok_isr    ; (08) Setup data loading.
    .db 0
    ljmp    _usb_susp_isr     ; (0C) Global suspend.
    .db 0
    ljmp    _usb_ures_isr     ; (10) USB reset.
    .db 0
    ljmp    _usb_hispeed_isr  ; (14) Entered high speed.
    .db 0
    ljmp    _usb_stub_isr     ; (18) EP0 ack.
    .db 0
    ljmp    _usb_stub_isr     ; (1C) Reserved.
    .db 0
    ljmp    _usb_stub_isr     ; (20) EP0 in.
    .db 0
    ljmp    _usb_stub_isr     ; (24) EP0 out.
    .db 0
    ljmp    _usb_stub_isr     ; (28) EP1 in.
    .db 0
    ljmp    _usb_stub_isr     ; (2C) EP1 out.
    .db 0
    ljmp    _usb_stub_isr     ; (30) EP2 in/out.
    .db 0
    ljmp    _usb_stub_isr     ; (34) EP4 in/out.
    .db 0
    ljmp    _usb_stub_isr     ; (38) EP6 in/out.
    .db 0
    ljmp    _usb_stub_isr     ; (3C) EP8 in/out.
    .db 0
    ljmp    _usb_stub_isr     ; (40) IBN in bulk nack.
    .db 0
    ljmp    _usb_stub_isr     ; (44) Reserved.
    .db 0
    ljmp    _usb_stub_isr     ; (48) EP0 ping nack.
    .db 0
    ljmp    _usb_stub_isr     ; (4C) EP1 ping nack.
    .db 0
    ljmp    _usb_stub_isr     ; (50) EP2 ping nack.
    .db 0
    ljmp    _usb_stub_isr     ; (54) EP4 ping nack.
    .db 0
    ljmp    _usb_stub_isr     ; (58) EP6 ping nack.
    .db 0
    ljmp    _usb_stub_isr     ; (5C) EP8 ping nack.
    .db 0
    ljmp    _usb_stub_isr     ; (60) Error limit.
    .db 0
    ljmp    _usb_stub_isr     ; (64) Reserved.
    .db 0
    ljmp    _usb_stub_isr     ; (68) Reserved.
    .db 0
    ljmp    _usb_stub_isr     ; (6C) Reserved.
    .db 0
    ljmp    _usb_stub_isr     ; (70) EP2 ISO pid sequence error.
    .db 0
    ljmp    _usb_stub_isr     ; (74) EP4 ISO pid sequence error.
    .db 0
    ljmp    _usb_stub_isr     ; (78) EP6 ISO pid sequence error.
    .db 0
    ljmp    _usb_stub_isr     ; (7C) EP8 ISO pid sequence error.
    .db 0

;; int4 jump table
    ljmp    _usb_stub_isr     ; (80) EP2 programmable flag.
    .db 0
    ljmp    _usb_stub_isr     ; (84) EP4 programmable flag.
    .db 0
    ljmp    _usb_stub_isr     ; (88) EP6 programmable flag.
    .db 0
    ljmp    _usb_stub_isr     ; (8C) EP8 programmable flag.
    .db 0
    ljmp    _usb_stub_isr     ; (90) EP2 empty flag.
    .db 0
    ljmp    _usb_stub_isr     ; (94) EP4 empty flag.
    .db 0
    ljmp    _usb_stub_isr     ; (98) EP6 empty flag.
    .db 0
    ljmp    _usb_stub_isr     ; (9C) EP8 empty flag.
    .db 0
    ljmp    _usb_stub_isr     ; (A0) EP2 full flag.
    .db 0
    ljmp    _usb_stub_isr     ; (A4) EP4 full flag.
    .db 0
    ljmp    _usb_stub_isr     ; (A8) EP6 full flag.
    .db 0
    ljmp    _usb_stub_isr     ; (AC) EP8 full flag.
    .db 0
    ljmp    _usb_stub_isr     ; (B0) GPIF operation complete.
    .db 0
    ljmp    _usb_stub_isr     ; (B4) GPIF waveform.
    .db 0