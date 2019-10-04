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
    // IAR-specific properties and sources.
    //

    Properties {
        condition: qbs.toolchain.contains("iar")
        cpp.commonCompilerFlags: ["-e"]
        cpp.staticLibraries: [
            cpp.toolchainInstallPath + "/../lib/clib/cl-pli-nsid-1e16x01"
        ]
        cpp.driverLinkerFlags: [
            "-D_IDATA_STACK_SIZE=0x40",
            "-D_PDATA_STACK_SIZE=0x80",
            "-D_XDATA_STACK_SIZE=0xEFF",
            "-D_XDATA_HEAP_SIZE=0xFF",
            "-D_EXTENDED_STACK_SIZE=0",
            "-D_EXTENDED_STACK_START=0"
        ]
    }

    Group {
        name: "Iar Linker Script"
        condition: qbs.toolchain.contains("iar")
        prefix: cpp.toolchainInstallPath + "/../config/devices/cypress/"
        fileTags: ["linkerscript"]
        files: ["lnk51ew_CY7C68013A.xcl"]
    }

    //
    // KEIL-specific properties and sources.
    //

    Properties {
        condition: qbs.toolchain.contains("keil")
        cpp.driverLinkerFlags: [
            "RAMSIZE(256)",
            "CODE(0x80)",
            "XDATA(0x1000)"
        ]
    }

    //
    // SDCC-specific properties and sources.
    //

    Properties {
        condition: qbs.toolchain.contains("sdcc")
        cpp.driverLinkerFlags: [
            "--code-loc", "0x80",
            "--xram-loc", "0x1000"
        ]
    }

    //
    // Common code.
    //

    files: [
        "core.c",
        "core.h",
        "defs.h",
        "gpio.c",
        "gpio.h",
        "hid.c",
        "hid.h",
        "hiddesc.c",
        "hidep0.c",
        "hidep1.c",
        "irqs.h",
        "main.c",
        "regs.h",
        "usb.c",
        "usb.h",
    ]
}
