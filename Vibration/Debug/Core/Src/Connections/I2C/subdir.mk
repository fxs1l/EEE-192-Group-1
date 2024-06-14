################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Connections/I2C/i2c.c 

OBJS += \
./Core/Src/Connections/I2C/i2c.o 

C_DEPS += \
./Core/Src/Connections/I2C/i2c.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Connections/I2C/%.o Core/Src/Connections/I2C/%.su Core/Src/Connections/I2C/%.cyclo: ../Core/Src/Connections/I2C/%.c Core/Src/Connections/I2C/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Connections-2f-I2C

clean-Core-2f-Src-2f-Connections-2f-I2C:
	-$(RM) ./Core/Src/Connections/I2C/i2c.cyclo ./Core/Src/Connections/I2C/i2c.d ./Core/Src/Connections/I2C/i2c.o ./Core/Src/Connections/I2C/i2c.su

.PHONY: clean-Core-2f-Src-2f-Connections-2f-I2C

