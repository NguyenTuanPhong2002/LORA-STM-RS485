################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HARDWARE/EWG/ewg.c 

OBJS += \
./HARDWARE/EWG/ewg.o 

C_DEPS += \
./HARDWARE/EWG/ewg.d 


# Each subdirectory must supply rules for building sources it contributes
HARDWARE/EWG/%.o HARDWARE/EWG/%.su HARDWARE/EWG/%.cyclo: ../HARDWARE/EWG/%.c HARDWARE/EWG/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L052xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-HARDWARE-2f-EWG

clean-HARDWARE-2f-EWG:
	-$(RM) ./HARDWARE/EWG/ewg.cyclo ./HARDWARE/EWG/ewg.d ./HARDWARE/EWG/ewg.o ./HARDWARE/EWG/ewg.su

.PHONY: clean-HARDWARE-2f-EWG

