################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/MODBUS-LIB/Src/Modbus.c \
../Middlewares/Third_Party/MODBUS-LIB/Src/UARTCallback.c 

OBJS += \
./Middlewares/Third_Party/MODBUS-LIB/Src/Modbus.o \
./Middlewares/Third_Party/MODBUS-LIB/Src/UARTCallback.o 

C_DEPS += \
./Middlewares/Third_Party/MODBUS-LIB/Src/Modbus.d \
./Middlewares/Third_Party/MODBUS-LIB/Src/UARTCallback.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/MODBUS-LIB/Src/%.o Middlewares/Third_Party/MODBUS-LIB/Src/%.su: ../Middlewares/Third_Party/MODBUS-LIB/Src/%.c Middlewares/Third_Party/MODBUS-LIB/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32H743xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"E:/Backup DUc 18/Backupcanon/ModbusH743/ModbusH743/Middlewares/Third_Party/MODBUS-LIB/Inc" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-MODBUS-2d-LIB-2f-Src

clean-Middlewares-2f-Third_Party-2f-MODBUS-2d-LIB-2f-Src:
	-$(RM) ./Middlewares/Third_Party/MODBUS-LIB/Src/Modbus.d ./Middlewares/Third_Party/MODBUS-LIB/Src/Modbus.o ./Middlewares/Third_Party/MODBUS-LIB/Src/Modbus.su ./Middlewares/Third_Party/MODBUS-LIB/Src/UARTCallback.d ./Middlewares/Third_Party/MODBUS-LIB/Src/UARTCallback.o ./Middlewares/Third_Party/MODBUS-LIB/Src/UARTCallback.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-MODBUS-2d-LIB-2f-Src

