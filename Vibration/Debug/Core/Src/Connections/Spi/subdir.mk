################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Connections/Spi/spi.c 

OBJS += \
./Core/Src/Connections/Spi/spi.o 

C_DEPS += \
./Core/Src/Connections/Spi/spi.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Connections/Spi/%.o Core/Src/Connections/Spi/%.su Core/Src/Connections/Spi/%.cyclo: ../Core/Src/Connections/Spi/%.c Core/Src/Connections/Spi/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Connections-2f-Spi

clean-Core-2f-Src-2f-Connections-2f-Spi:
	-$(RM) ./Core/Src/Connections/Spi/spi.cyclo ./Core/Src/Connections/Spi/spi.d ./Core/Src/Connections/Spi/spi.o ./Core/Src/Connections/Spi/spi.su

.PHONY: clean-Core-2f-Src-2f-Connections-2f-Spi

