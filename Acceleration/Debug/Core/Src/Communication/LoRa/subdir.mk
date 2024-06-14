################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Communication/LoRa/gpio_controls.c \
../Core/Src/Communication/LoRa/lora.c 

OBJS += \
./Core/Src/Communication/LoRa/gpio_controls.o \
./Core/Src/Communication/LoRa/lora.o 

C_DEPS += \
./Core/Src/Communication/LoRa/gpio_controls.d \
./Core/Src/Communication/LoRa/lora.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Communication/LoRa/%.o Core/Src/Communication/LoRa/%.su Core/Src/Communication/LoRa/%.cyclo: ../Core/Src/Communication/LoRa/%.c Core/Src/Communication/LoRa/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Communication-2f-LoRa

clean-Core-2f-Src-2f-Communication-2f-LoRa:
	-$(RM) ./Core/Src/Communication/LoRa/gpio_controls.cyclo ./Core/Src/Communication/LoRa/gpio_controls.d ./Core/Src/Communication/LoRa/gpio_controls.o ./Core/Src/Communication/LoRa/gpio_controls.su ./Core/Src/Communication/LoRa/lora.cyclo ./Core/Src/Communication/LoRa/lora.d ./Core/Src/Communication/LoRa/lora.o ./Core/Src/Communication/LoRa/lora.su

.PHONY: clean-Core-2f-Src-2f-Communication-2f-LoRa

