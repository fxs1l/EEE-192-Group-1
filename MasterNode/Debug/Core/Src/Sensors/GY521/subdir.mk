################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Sensors/GY521/gy521.c 

OBJS += \
./Core/Src/Sensors/GY521/gy521.o 

C_DEPS += \
./Core/Src/Sensors/GY521/gy521.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Sensors/GY521/%.o Core/Src/Sensors/GY521/%.su Core/Src/Sensors/GY521/%.cyclo: ../Core/Src/Sensors/GY521/%.c Core/Src/Sensors/GY521/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Sensors-2f-GY521

clean-Core-2f-Src-2f-Sensors-2f-GY521:
	-$(RM) ./Core/Src/Sensors/GY521/gy521.cyclo ./Core/Src/Sensors/GY521/gy521.d ./Core/Src/Sensors/GY521/gy521.o ./Core/Src/Sensors/GY521/gy521.su

.PHONY: clean-Core-2f-Src-2f-Sensors-2f-GY521

