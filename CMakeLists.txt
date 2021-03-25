add_library(stm32-hal-eeprom eeprom.c eeprom.h)
target_include_directories(stm32-hal-eeprom INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
