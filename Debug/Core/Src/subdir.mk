################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Alarm.c \
../Core/Src/DHT11_library.c \
../Core/Src/Delay_us.c \
../Core/Src/LCD_1602.c \
../Core/Src/Main_menu.c \
../Core/Src/RTC_library.c \
../Core/Src/Rotary_encoder.c \
../Core/Src/main.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c 

OBJS += \
./Core/Src/Alarm.o \
./Core/Src/DHT11_library.o \
./Core/Src/Delay_us.o \
./Core/Src/LCD_1602.o \
./Core/Src/Main_menu.o \
./Core/Src/RTC_library.o \
./Core/Src/Rotary_encoder.o \
./Core/Src/main.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o 

C_DEPS += \
./Core/Src/Alarm.d \
./Core/Src/DHT11_library.d \
./Core/Src/Delay_us.d \
./Core/Src/LCD_1602.d \
./Core/Src/Main_menu.d \
./Core/Src/RTC_library.d \
./Core/Src/Rotary_encoder.d \
./Core/Src/main.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Alarm.d ./Core/Src/Alarm.o ./Core/Src/Alarm.su ./Core/Src/DHT11_library.d ./Core/Src/DHT11_library.o ./Core/Src/DHT11_library.su ./Core/Src/Delay_us.d ./Core/Src/Delay_us.o ./Core/Src/Delay_us.su ./Core/Src/LCD_1602.d ./Core/Src/LCD_1602.o ./Core/Src/LCD_1602.su ./Core/Src/Main_menu.d ./Core/Src/Main_menu.o ./Core/Src/Main_menu.su ./Core/Src/RTC_library.d ./Core/Src/RTC_library.o ./Core/Src/RTC_library.su ./Core/Src/Rotary_encoder.d ./Core/Src/Rotary_encoder.o ./Core/Src/Rotary_encoder.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su

.PHONY: clean-Core-2f-Src

