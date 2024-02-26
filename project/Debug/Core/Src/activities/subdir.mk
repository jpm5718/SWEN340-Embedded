################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/activities/activity3.c \
../Core/Src/activities/clock.c \
../Core/Src/activities/conversion.c \
../Core/Src/activities/echo.c \
../Core/Src/activities/hello.c \
../Core/Src/activities/homework.c \
../Core/Src/activities/hw4.c \
../Core/Src/activities/hw8.c \
../Core/Src/activities/ledswitch.c \
../Core/Src/activities/sqr_wave.c \
../Core/Src/activities/structs.c \
../Core/Src/activities/timer.c 

OBJS += \
./Core/Src/activities/activity3.o \
./Core/Src/activities/clock.o \
./Core/Src/activities/conversion.o \
./Core/Src/activities/echo.o \
./Core/Src/activities/hello.o \
./Core/Src/activities/homework.o \
./Core/Src/activities/hw4.o \
./Core/Src/activities/hw8.o \
./Core/Src/activities/ledswitch.o \
./Core/Src/activities/sqr_wave.o \
./Core/Src/activities/structs.o \
./Core/Src/activities/timer.o 

C_DEPS += \
./Core/Src/activities/activity3.d \
./Core/Src/activities/clock.d \
./Core/Src/activities/conversion.d \
./Core/Src/activities/echo.d \
./Core/Src/activities/hello.d \
./Core/Src/activities/homework.d \
./Core/Src/activities/hw4.d \
./Core/Src/activities/hw8.d \
./Core/Src/activities/ledswitch.d \
./Core/Src/activities/sqr_wave.d \
./Core/Src/activities/structs.d \
./Core/Src/activities/timer.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/activities/%.o Core/Src/activities/%.su Core/Src/activities/%.cyclo: ../Core/Src/activities/%.c Core/Src/activities/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Core/Inc/activities -I../Core/Inc/demos -I../Core/Inc/devices -I../Core/Inc/midi -I../Core/Inc/system -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-activities

clean-Core-2f-Src-2f-activities:
	-$(RM) ./Core/Src/activities/activity3.cyclo ./Core/Src/activities/activity3.d ./Core/Src/activities/activity3.o ./Core/Src/activities/activity3.su ./Core/Src/activities/clock.cyclo ./Core/Src/activities/clock.d ./Core/Src/activities/clock.o ./Core/Src/activities/clock.su ./Core/Src/activities/conversion.cyclo ./Core/Src/activities/conversion.d ./Core/Src/activities/conversion.o ./Core/Src/activities/conversion.su ./Core/Src/activities/echo.cyclo ./Core/Src/activities/echo.d ./Core/Src/activities/echo.o ./Core/Src/activities/echo.su ./Core/Src/activities/hello.cyclo ./Core/Src/activities/hello.d ./Core/Src/activities/hello.o ./Core/Src/activities/hello.su ./Core/Src/activities/homework.cyclo ./Core/Src/activities/homework.d ./Core/Src/activities/homework.o ./Core/Src/activities/homework.su ./Core/Src/activities/hw4.cyclo ./Core/Src/activities/hw4.d ./Core/Src/activities/hw4.o ./Core/Src/activities/hw4.su ./Core/Src/activities/hw8.cyclo ./Core/Src/activities/hw8.d ./Core/Src/activities/hw8.o ./Core/Src/activities/hw8.su ./Core/Src/activities/ledswitch.cyclo ./Core/Src/activities/ledswitch.d ./Core/Src/activities/ledswitch.o ./Core/Src/activities/ledswitch.su ./Core/Src/activities/sqr_wave.cyclo ./Core/Src/activities/sqr_wave.d ./Core/Src/activities/sqr_wave.o ./Core/Src/activities/sqr_wave.su ./Core/Src/activities/structs.cyclo ./Core/Src/activities/structs.d ./Core/Src/activities/structs.o ./Core/Src/activities/structs.su ./Core/Src/activities/timer.cyclo ./Core/Src/activities/timer.d ./Core/Src/activities/timer.o ./Core/Src/activities/timer.su

.PHONY: clean-Core-2f-Src-2f-activities

