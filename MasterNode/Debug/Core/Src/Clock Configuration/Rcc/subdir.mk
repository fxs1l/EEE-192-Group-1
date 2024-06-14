################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Clock\ Configuration/Rcc/rcc.c 

OBJS += \
./Core/Src/Clock\ Configuration/Rcc/rcc.o 

C_DEPS += \
./Core/Src/Clock\ Configuration/Rcc/rcc.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Clock\ Configuration/Rcc/rcc.o: ../Core/Src/Clock\ Configuration/Rcc/rcc.c Core/Src/Clock\ Configuration/Rcc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Core/Src/Clock Configuration/Rcc/rcc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Clock-20-Configuration-2f-Rcc

clean-Core-2f-Src-2f-Clock-20-Configuration-2f-Rcc:
	-$(RM) ./Core/Src/Clock\ Configuration/Rcc/rcc.cyclo ./Core/Src/Clock\ Configuration/Rcc/rcc.d ./Core/Src/Clock\ Configuration/Rcc/rcc.o ./Core/Src/Clock\ Configuration/Rcc/rcc.su

.PHONY: clean-Core-2f-Src-2f-Clock-20-Configuration-2f-Rcc

