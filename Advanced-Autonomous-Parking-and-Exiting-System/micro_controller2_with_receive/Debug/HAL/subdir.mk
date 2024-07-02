################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/servo_motor_1.c \
../HAL/servo_motor_2.c \
../HAL/servo_motor_4.c \
../HAL/ultra_sonic.c 

OBJS += \
./HAL/servo_motor_1.o \
./HAL/servo_motor_2.o \
./HAL/servo_motor_4.o \
./HAL/ultra_sonic.o 

C_DEPS += \
./HAL/servo_motor_1.d \
./HAL/servo_motor_2.d \
./HAL/servo_motor_4.d \
./HAL/ultra_sonic.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o: ../HAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


