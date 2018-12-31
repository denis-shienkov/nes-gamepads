import qbs

CppApplication {
    name: "nes-gamepads"

    cpp.includePaths: [
        "Inc",
        "Drivers/STM32F4xx_HAL_Driver/Inc",
        "Drivers/STM32F4xx_HAL_Driver/Inc/Legacy",
        "Middlewares/ST/STM32_USB_Device_Library/Core/Inc",
        "Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc",
        "Drivers/CMSIS/Device/ST/STM32F4xx/Include",
        "Drivers/CMSIS/Include",
    ]

    cpp.defines: [
        "USE_HAL_DRIVER",
        "STM32F407xx",
    ]

    cpp.staticLibraries: [
        "c",
        "m",
        "nosys"
    ]

    cpp.driverFlags: [
        "-mcpu=cortex-m4",
        "-mfpu=fpv4-sp-d16",
        "-mthumb",
        "-mfloat-abi=hard",
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

    cpp.positionIndependentCode: false
    cpp.cLanguageVersion: "c11"

    Properties {
        condition: qbs.debugInformation
        cpp.commonCompilerFlags: [
            "-gdwarf-2"
        ]
    }

    Group {
        name: "Linker scripts"
        fileTags: ["linkerscript"]
        files: [
            "STM32F407VG_FLASH.ld",
        ]
    }

    Group {
        name: "Startup"
        prefix: "startup/"
        files: [
            "startup_stm32f407xx.s",
        ]
    }

    Group {
        name: "User"
        prefix: "Src/"
        files: [
            "main.c",
            "stm32f4xx_hal_msp.c",
            "stm32f4xx_it.c",
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
            "system_stm32f4xx.c",
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
        prefix: "Drivers/STM32F4xx_HAL_Driver/Src/"
        files: [
            "stm32f4xx_hal.c",
            "stm32f4xx_hal_cortex.c",
            "stm32f4xx_hal_dma.c",
            "stm32f4xx_hal_dma_ex.c",
            "stm32f4xx_hal_flash.c",
            "stm32f4xx_hal_flash_ex.c",
            "stm32f4xx_hal_flash_ramfunc.c",
            "stm32f4xx_hal_gpio.c",
            "stm32f4xx_hal_pcd.c",
            "stm32f4xx_hal_pcd_ex.c",
            "stm32f4xx_hal_pwr.c",
            "stm32f4xx_hal_pwr_ex.c",
            "stm32f4xx_hal_rcc.c",
            "stm32f4xx_hal_rcc_ex.c",
            "stm32f4xx_hal_spi.c",
            "stm32f4xx_hal_tim.c",
            "stm32f4xx_hal_tim_ex.c",
            "stm32f4xx_ll_usb.c",
        ]
    }

}
