################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Sensors/Vibration/vibration.c 

OBJS += \
./Core/Src/Sensors/Vibration/vibration.o 

C_DEPS += \
./Core/Src/Sensors/Vibration/vibration.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Sensors/Vibration/%.o Core/Src/Sensors/Vibration/%.su Core/Src/Sensors/Vibration/%.cyclo: ../Core/Src/Sensors/Vibration/%.c Core/Src/Sensors/Vibration/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Sensors-2f-Vibration

clean-Core-2f-Src-2f-Sensors-2f-Vibration:
	-$(RM) ./Core/Src/Sensors/Vibration/vibration.cyclo ./Core/Src/Sensors/Vibration/vibration.d ./Core/Src/Sensors/Vibration/vibration.o ./Core/Src/Sensors/Vibration/vibration.su

.PHONY: clean-Core-2f-Src-2f-Sensors-2f-Vibration

