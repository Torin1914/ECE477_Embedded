################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f091rctx.s 

OBJS += \
./Core/Startup/startup_stm32f091rctx.o 

S_DEPS += \
./Core/Startup/startup_stm32f091rctx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0 -g3 -DDEBUG -c -I"C:/Users/jacob/STM32CubeIDE/workspace_1.13.1/motor_drive/Core/Inc/motor_proc" -I"C:/Users/jacob/STM32CubeIDE/workspace_1.13.1/motor_drive/Core/Inc/servo_proc" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f091rctx.d ./Core/Startup/startup_stm32f091rctx.o

.PHONY: clean-Core-2f-Startup

