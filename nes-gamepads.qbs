import qbs

CppApplication {
    name: "nes-gamepads"

    /// GCC-specific properties.
    Properties {
        condition: qbs.toolchain.contains("gcc")
        cpp.staticLibraries: [ "c", "m", "nosys" ]

        cpp.driverFlags: [
            "-mcpu=cortex-m3",
            "-mthumb",
            "-mfloat-abi=soft",
            "-fdata-sections",
            "-ffunction-sections",
            "-fstack-usage",
            "-specs=nano.specs",
        ]

        cpp.linkerFlags: [
            "--cref",
            "--gc-sections",
            "--defsym=malloc_getpagesize_P=0x80",
        ]

        cpp.driverLinkerFlags: [
            "-specs=nosys.specs",
            "-static",
        ]

        cpp.commonCompilerFlags: {
            if (qbs.debugInformation)
                return "-gdwarf-2";
            return "";
        }
    }

    Group {
        condition: qbs.toolchain.contains("gcc")
        name: "GCC Linker Scripts"
        fileTags: ["linkerscript"]
        files: [ "STM32F103C8_FLASH_GCC.ld" ]
    }

    Group {
        condition: qbs.toolchain.contains("gcc")
        name: "GCC Startup"
        prefix: "startup/"
        files: [ "startup_stm32f103xb_gcc.s" ]
    }

    /// Keil-specific properties.

    Properties {
        condition: qbs.toolchain.contains("keil")
        cpp.driverFlags: [
            "--cpu", "cortex-m3",
        ]
    }

    Group {
        condition: qbs.toolchain.contains("keil")
        name: "KEIL Linker Scripts"
        fileTags: ["linkerscript"]
        files: [ "STM32F103C8_FLASH_KEIL.ld" ]
    }

    Group {
        condition: qbs.toolchain.contains("keil")
        name: "KEIL Startup"
        prefix: "startup/"
        files: [ "startup_stm32f103xb_keil.s" ]
    }

    cpp.positionIndependentCode: false
    cpp.cLanguageVersion: "c99"

    cpp.includePaths: [
        "Drivers/CMSIS/Device/ST/STM32F1xx/Include",
        "Drivers/CMSIS/Include",
        "Drivers/STM32F1xx_HAL_Driver/Inc",
        "Drivers/STM32F1xx_HAL_Driver/Inc/Legacy",
        "Inc",
        "Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc",
        "Middlewares/ST/STM32_USB_Device_Library/Core/Inc",
    ]

    cpp.defines: [
        "USE_HAL_DRIVER",
        "STM32F103xB",
    ]

    Group {
        name: "User"
        prefix: "Src/"
        files: [
            "main.c",
            "stm32f1xx_hal_msp.c",
            "stm32f1xx_it.c",
            "usb_device.c",
            "usbd_conf.c",
            "usbd_custom_hid_if.c",
            "usbd_desc.c",
        ]
    }

    Group {
        name: "CMSIS"
        prefix: "Src/"
        files: [
            "system_stm32f1xx.c",
        ]
    }

    Group {
        name: "UsbCore"
        prefix: "Middlewares/ST/STM32_USB_Device_Library/Core/Src/"
        files: [
            "usbd_core.c",
            "usbd_ctlreq.c",
            "usbd_ioreq.c",
        ]
    }

    Group {
        name: "UsbCustomHid"
        prefix: "Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Src/"
        files: [
            "usbd_customhid.c",
        ]
    }

    Group {
        name: "HAL"
        prefix: "Drivers/STM32F1xx_HAL_Driver/Src/"
        files: [
            "stm32f1xx_hal.c",
            "stm32f1xx_hal_cortex.c",
            "stm32f1xx_hal_dma.c",
            "stm32f1xx_hal_flash.c",
            "stm32f1xx_hal_flash_ex.c",
            "stm32f1xx_hal_gpio.c",
            "stm32f1xx_hal_pcd.c",
            "stm32f1xx_hal_pcd_ex.c",
            "stm32f1xx_hal_pwr.c",
            "stm32f1xx_hal_rcc.c",
            "stm32f1xx_hal_rcc_ex.c",
            "stm32f1xx_hal_tim.c",
            "stm32f1xx_hal_tim_ex.c",
            "stm32f1xx_ll_usb.c",
        ]
    }
}
