################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/modbus/port/portevent.c \
../Middlewares/modbus/port/portserial.c \
../Middlewares/modbus/port/porttimer.c 

OBJS += \
./Middlewares/modbus/port/portevent.o \
./Middlewares/modbus/port/portserial.o \
./Middlewares/modbus/port/porttimer.o 

C_DEPS += \
./Middlewares/modbus/port/portevent.d \
./Middlewares/modbus/port/portserial.d \
./Middlewares/modbus/port/porttimer.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/modbus/port/%.o: ../Middlewares/modbus/port/%.c Middlewares/modbus/port/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/modbus/include -I../Middlewares/modbus/port -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/modbus/rtu -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

