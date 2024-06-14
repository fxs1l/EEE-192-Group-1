################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/Sensors/Vibration/subdir.mk
-include Core/Src/Sensors/Moisture/subdir.mk
-include Core/Src/Sensors/GY521/subdir.mk
-include Core/Src/Connections/Spi/subdir.mk
-include Core/Src/Connections/I2C/subdir.mk
-include Core/Src/Connections/ADC/subdir.mk
-include Core/Src/Communication/LoRa/subdir.mk
-include Core/Src/Communication/LCD/subdir.mk
-include Core/Src/Communication/ESP32/subdir.mk
-include Core/Src/Clock\ Configuration/Rcc/subdir.mk
-include Core/Src/Clock\ Configuration/Delay/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Acceleration
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Acceleration.elf \

MAP_FILES += \
Acceleration.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Acceleration.list \

OBJCOPY_HEX += \
Acceleration.hex \


# All Target
all: main-build

# Main-build Target
main-build: Acceleration.elf secondary-outputs

# Tool invocations
Acceleration.elf Acceleration.map: $(OBJS) $(USER_OBJS) C:\Users\User\Documents\Academics\To\ Do\EEE\ 192\Acceleration\STM32F411RETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Acceleration.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\User\Documents\Academics\To Do\EEE 192\Acceleration\STM32F411RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Acceleration.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Acceleration.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Acceleration.list"
	@echo 'Finished building: $@'
	@echo ' '

Acceleration.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "Acceleration.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Acceleration.elf Acceleration.hex Acceleration.list Acceleration.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
