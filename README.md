# EEPROM
Generic STM32 HAL driver for EEPROM devices.

[![Software License: MIT](https://img.shields.io/badge/Software_License-MIT-blue)](https://opensource.org/licenses/MIT)
[![Build Status](https://github.com/henriheimann/stm32-hal-eeprom/workflows/Tests/badge.svg)](https://github.com/henriheimann/stm32-hal-eeprom/actions)


## Usage
For CMake based projects (for example when using STM32CubeMX projects with CLion) you can for example setup the driver as submodule and link to it:
```cmake
add_subdirectory("<directory-to-driver>/eeprom")
target_link_libraries(<target-name> stm32-hal-eeprom)
```


## Getting Started
After connecting the EEPROM to your microcontroller via I2C and initialising the bus using Cube you can use this
library to interact with the EEPROM as shown in the following example:
```c
// Create the handle for the EEPROM.
eeprom_handle_t handle = {
    .i2c_handle = &hi2c1,
    .device_address = EEPROM_24LC32A_ADDRESS,
    .page_size = EEPROM_24LC32A_PAGE_SIZE,
    .max_address = EEPROM_24LC32A_MAX_ADDRESS
};

byte[] buffer = {0xaa, 0x12, 0xbb, 0x34};

// Write bytes to the EEPROM pagewise.
if (!eeprom_write_bytes(&handle, 0x000, buffer, sizeof(buffer))) {
    printf("EEPROM write failed\n\r");
}

if (!eeprom_read_bytes(&handle, 0x000, buffer, sizeof(buffer))) {
    printf("EEPROM read failed\n\r");
} else {
printf("Read back values from EEPROM: %02x %02x %02x %02x\n\r", buffer[0], buffer[1], buffer[2], buffer[3]);	
}
```

## Supported Platforms
STM32L0 and STM32L4 microcontrollers are supported. Address, memory size and page size values for the 24LC32A EEPROM are predefined.
The HAL header includes for other microcontrollers and defines for new EEPROM devices may be added in `eeprom.h`.