################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/modbus/rtu/mbcrc.c \
../Middlewares/modbus/rtu/mbrtu.c \
../Middlewares/modbus/rtu/mbrtu_m.c 

OBJS += \
./Middlewares/modbus/rtu/mbcrc.o \
./Middlewares/modbus/rtu/mbrtu.o \
./Middlewares/modbus/rtu/mbrtu_m.o 

C_DEPS += \
./Middlewares/modbus/rtu/mbcrc.d \
./Middlewares/modbus/rtu/mbrtu.d \
./Middlewares/modbus/rtu/mbrtu_m.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/modbus/rtu/%.o: ../Middlewares/modbus/rtu/%.c Middlewares/modbus/rtu/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/modbus/include -I../Middlewares/modbus/port -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/modbus/rtu -I../User -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

