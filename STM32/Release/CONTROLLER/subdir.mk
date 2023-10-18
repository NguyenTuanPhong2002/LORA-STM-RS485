################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CONTROLLER/controller.c 

OBJS += \
./CONTROLLER/controller.o 

C_DEPS += \
./CONTROLLER/controller.d 


# Each subdirectory must supply rules for building sources it contributes
CONTROLLER/%.o CONTROLLER/%.su CONTROLLER/%.cyclo: ../CONTROLLER/%.c CONTROLLER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L052xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-CONTROLLER

clean-CONTROLLER:
	-$(RM) ./CONTROLLER/controller.cyclo ./CONTROLLER/controller.d ./CONTROLLER/controller.o ./CONTROLLER/controller.su

.PHONY: clean-CONTROLLER

