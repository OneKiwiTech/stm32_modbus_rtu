################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/modbus/functions/mbfunccoils.c \
../Middlewares/modbus/functions/mbfuncdiag.c \
../Middlewares/modbus/functions/mbfuncdisc.c \
../Middlewares/modbus/functions/mbfuncholding.c \
../Middlewares/modbus/functions/mbfuncinput.c \
../Middlewares/modbus/functions/mbfuncother.c \
../Middlewares/modbus/functions/mbutils.c 

OBJS += \
./Middlewares/modbus/functions/mbfunccoils.o \
./Middlewares/modbus/functions/mbfuncdiag.o \
./Middlewares/modbus/functions/mbfuncdisc.o \
./Middlewares/modbus/functions/mbfuncholding.o \
./Middlewares/modbus/functions/mbfuncinput.o \
./Middlewares/modbus/functions/mbfuncother.o \
./Middlewares/modbus/functions/mbutils.o 

C_DEPS += \
./Middlewares/modbus/functions/mbfunccoils.d \
./Middlewares/modbus/functions/mbfuncdiag.d \
./Middlewares/modbus/functions/mbfuncdisc.d \
./Middlewares/modbus/functions/mbfuncholding.d \
./Middlewares/modbus/functions/mbfuncinput.d \
./Middlewares/modbus/functions/mbfuncother.d \
./Middlewares/modbus/functions/mbutils.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/modbus/functions/%.o: ../Middlewares/modbus/functions/%.c Middlewares/modbus/functions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/modbus/include -I../Middlewares/modbus/port -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/modbus/rtu -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

