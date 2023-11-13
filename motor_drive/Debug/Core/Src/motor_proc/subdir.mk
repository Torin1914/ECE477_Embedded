################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/motor_proc/motor_proc.c 

OBJS += \
./Core/Src/motor_proc/motor_proc.o 

C_DEPS += \
./Core/Src/motor_proc/motor_proc.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/motor_proc/%.o Core/Src/motor_proc/%.su Core/Src/motor_proc/%.cyclo: ../Core/Src/motor_proc/%.c Core/Src/motor_proc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F091xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I"C:/ECE477_Embedded/motor_drive/Core/Inc/motor_proc" -I"C:/ECE477_Embedded/motor_drive/Core/Inc/servo_proc" -I"C:/ECE477_Embedded/motor_drive/Core/Inc/i2c_proc" -I"C:/ECE477_Embedded/motor_drive/Core/Src/i2c_proc" -I"C:/ECE477_Embedded/motor_drive/Core/Inc/Jetson_Bridge" -I"C:/ECE477_Embedded/motor_drive/Core/Inc/UART_Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-motor_proc

clean-Core-2f-Src-2f-motor_proc:
	-$(RM) ./Core/Src/motor_proc/motor_proc.cyclo ./Core/Src/motor_proc/motor_proc.d ./Core/Src/motor_proc/motor_proc.o ./Core/Src/motor_proc/motor_proc.su

.PHONY: clean-Core-2f-Src-2f-motor_proc

