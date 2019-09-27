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

    Group {
        name: "Keil Autovec"
        condition: qbs.toolchain.contains("keil")
        fileTags: ["asm"]
        files: [
            "autovec_keil.a51",
        ]
    }

    //
    // SDCC-specific properties and sources.
    //

    Properties {
        condition: qbs.toolchain.contains("sdcc")
        cpp.driverLinkerFlags: [
            "--code-loc", "0x0100",
            "--xram-loc", "0x1000"
        ]
    }

    Group {
        name: "Sdcc Autovec"
        condition: qbs.toolchain.contains("sdcc")
        fileTags: ["asm"]
        files: [
            "autovec_sdcc.a51",
        ]
    }

    //
    // Common code.
    //

    files: [
        "core.c",
        "core.h",
        "defs.h",
        "hid.c",
        "hid.h",
        "hiddscr.c",
        "hidep0.c",
        "hidstream.c",
        "irqs.h",
        "main.c",
        "regs.h",
        "usb.c",
        "usb.h",
    ]
}
