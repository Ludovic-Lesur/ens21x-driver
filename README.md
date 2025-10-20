# Description

This repository contains the **ENS21x** temperature and humidity sensor driver.

# Dependencies

The driver relies on:

* An external `types.h` header file defining the **standard C types** of the targeted MCU.
* The **embedded utility functions** defined in the [embedded-utils](https://github.com/Ludovic-Lesur/embedded-utils) repository.

Here is the versions compatibility table:

| **ens21x-driver** | **embedded-utils** |
|:---:|:---:|
| [sw1.2](https://github.com/Ludovic-Lesur/ens21x-driver/releases/tag/sw1.2) | >= [sw5.0](https://github.com/Ludovic-Lesur/embedded-utils/releases/tag/sw5.0) |
| [sw1.1](https://github.com/Ludovic-Lesur/ens21x-driver/releases/tag/sw1.1) | >= [sw5.0](https://github.com/Ludovic-Lesur/embedded-utils/releases/tag/sw5.0) |
| [sw1.0](https://github.com/Ludovic-Lesur/ens21x-driver/releases/tag/sw1.0) | >= [sw5.0](https://github.com/Ludovic-Lesur/embedded-utils/releases/tag/sw5.0) |

# Compilation flags

| **Flag name** | **Value** | **Description** |
|:---:|:---:|:---:|
| `ENS21X_DRIVER_DISABLE_FLAGS_FILE` | `defined` / `undefined` | Disable the `ens21x_driver_flags.h` header file inclusion when compilation flags are given in the project settings or by command line. |
| `ENS21X_DRIVER_DISABLE` | `defined` / `undefined` | Disable the ENS21x driver. |
| `ENS21X_DRIVER_I2C_ERROR_BASE_LAST` | `<value>` | Last error base of the low level I2C driver. |
| `ENS21X_DRIVER_DELAY_ERROR_BASE_LAST` | `<value>` | Last error base of the low level delay driver. |
