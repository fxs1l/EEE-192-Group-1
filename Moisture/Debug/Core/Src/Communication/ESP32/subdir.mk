################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Communication/ESP32/ESPDataLogger.c \
../Core/Src/Communication/ESP32/UartRingbuffer.c 

OBJS += \
./Core/Src/Communication/ESP32/ESPDataLogger.o \
./Core/Src/Communication/ESP32/UartRingbuffer.o 

C_DEPS += \
./Core/Src/Communication/ESP32/ESPDataLogger.d \
./Core/Src/Communication/ESP32/UartRingbuffer.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Communication/ESP32/%.o Core/Src/Communication/ESP32/%.su Core/Src/Communication/ESP32/%.cyclo: ../Core/Src/Communication/ESP32/%.c Core/Src/Communication/ESP32/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Communication-2f-ESP32

clean-Core-2f-Src-2f-Communication-2f-ESP32:
	-$(RM) ./Core/Src/Communication/ESP32/ESPDataLogger.cyclo ./Core/Src/Communication/ESP32/ESPDataLogger.d ./Core/Src/Communication/ESP32/ESPDataLogger.o ./Core/Src/Communication/ESP32/ESPDataLogger.su ./Core/Src/Communication/ESP32/UartRingbuffer.cyclo ./Core/Src/Communication/ESP32/UartRingbuffer.d ./Core/Src/Communication/ESP32/UartRingbuffer.o ./Core/Src/Communication/ESP32/UartRingbuffer.su

.PHONY: clean-Core-2f-Src-2f-Communication-2f-ESP32

