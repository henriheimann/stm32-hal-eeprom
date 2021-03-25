project (stm32-hal-eeprom_tests)

cmake_minimum_required(VERSION 3.10)

# Set TESTING definition for actual source code
add_definitions(-DTESTING)

# Add library under test
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_BINARY_DIR}/eeprom)

# Look for CppUTest
if(DEFINED ENV{CPPUTEST_HOME})
    message("Using CppUTest found in $ENV{CPPUTEST_HOME}")
    include_directories($ENV{CPPUTEST_HOME}/include)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -include $ENV{CPPUTEST_HOME}/include/CppUTest/MemoryLeakDetectorMallocMacros.h")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -include $ENV{CPPUTEST_HOME}/include/CppUTest/MemoryLeakDetectorNewMacros.h")
    add_library(CppUTest STATIC IMPORTED)
    set_property(TARGET CppUTest PROPERTY IMPORTED_LOCATION $ENV{CPPUTEST_HOME}/lib/libCppUTest.a)
    add_library(CppUTestExt STATIC IMPORTED)
    set_property(TARGET CppUTestExt PROPERTY IMPORTED_LOCATION $ENV{CPPUTEST_HOME}/lib/libCppUTestExt.a)
else()
    find_package(CppUTest CONFIG REQUIRED)
endif()

add_executable(run_all_tests test_main.cc eeprom_tests.cc mock_hal.cc mock_hal.h)
target_link_libraries(run_all_tests PRIVATE stm32-hal-eeprom CppUTest CppUTestExt)
