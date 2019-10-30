import qbs

CppApplication {
    condition: {
        if (!qbs.architecture.contains("msp430"))
            return false;
        return qbs.toolchain.contains("iar")
                || qbs.toolchain.contains("gcc")
    }
    name: "msp430f5529-nes-gamepads"
    cpp.cLanguageVersion: "c99"
    cpp.positionIndependentCode: false

    //
    // IAR-specific properties and sources.
    //

    Properties {
        condition: qbs.toolchain.contains("iar")

        property path dlibIncludePath: cpp.toolchainInstallPath + "/../lib/dlib/dl430xssfn.h"
        property path dlibRuntimePath: cpp.toolchainInstallPath + "/../lib/dlib/dl430xssfn.r43"

        cpp.entryPoint: "__program_start"

        cpp.defines: ["__MSP430F5529__"]

        cpp.driverFlags: [
            "-e",
            "--core=430X",
            "--data_model=small",
            "--code_model=small",
            "--dlib_config", dlibIncludePath
        ]

        cpp.driverLinkerFlags: [
            "-D_STACK_SIZE=A0",
            "-D_DATA16_HEAP_SIZE=A0",
            "-D_DATA20_HEAP_SIZE=50"
        ]

        cpp.staticLibraries: [
            // Explicitly link with the runtime dlib library (which contains
            // all required startup code and other stuff).
            dlibRuntimePath
        ]
    }

    Group {
        condition: qbs.toolchain.contains("iar")
        name: "IAR Linker Script"
        prefix: cpp.toolchainInstallPath + "/../config/linker/"
        fileTags: ["linkerscript"]
        // Explicitly use the default linker scripts for current target.
        files: ["lnk430f5529.xcl"/*, "multiplier32.xcl"*/]
    }

    //
    // GCC-specific properties and soucres.
    //

    Properties {
        condition: qbs.toolchain.contains("gcc")
        property path supportFilesPath: 'c:/msp430-gcc-support-files/include/'
        // A path to the MSP430 support files, which are
        // provided by the Texas Instruments separately:
        // e.g. 'c:/msp430-gcc-support-files/include/'
        cpp.includePaths: supportFilesPath
        cpp.libraryPaths: supportFilesPath
        cpp.driverFlags: ["-mmcu=msp430f5529"]
    }

    Group {
        condition: qbs.toolchain.contains("gcc")
        name: "GCC Linker Script"
        fileTags: ["linkerscript"]
        files: ["gamepads.ld"]
    }

    files: [
        "gpio.c",
        "gpio.h",
        "hid.h",
        "hiddesc.c",
        "hidep0.c",
        "hidep1.c",
        "hwdefs.h",
        "main.c",
        "pmm.c",
        "pmm.h",
        "ucs.c",
        "ucs.h",
        "usb.c",
        "usb.h",
        "wdt_a.c",
        "wdt_a.h",
    ]
}
