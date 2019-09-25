import qbs

CppApplication {
    condition: {
        if (!qbs.architecture.contains("mcs51"))
            return false;
        return qbs.toolchain.contains("iar")
                || qbs.toolchain.contains("keil")
                || qbs.toolchain.contains("sdcc")
    }
    name: "fx2-nes-gamepads"
    cpp.positionIndependentCode: false

    //
    // KEIL-specific properties and sources.
    //

    Properties {
        condition: qbs.toolchain.contains("keil")
        cpp.driverLinkerFlags: [
            "RAMSIZE(256)",
            "CODE(0x0100-0x0FFF)",
            "XDATA(0x1000-0x1FFF)"
        ]
    }

    //
    // Common code.
    //

    Group {
        name: "Fx2"
        files: [
            "fx2defs.h",
            "fx2hid.c",
            "fx2hid.h",
            "fx2hiddscr.c",
            "fx2hidep0.c",
            "fx2hidstream.c",
            "fx2hw.c",
            "fx2hw.h",
            "fx2irqs.h",
            "fx2jmptable.a51",
            "fx2regs.h",
            "fx2usb.c",
            "fx2usb.h",
        ]
    }

    files: [
        "main.c",
    ]
}
