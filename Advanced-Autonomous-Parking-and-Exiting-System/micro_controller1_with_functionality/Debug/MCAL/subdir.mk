################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/DIO_program.c \
../MCAL/GIE_program.c \
../MCAL/PWM0_program.c \
../MCAL/PWM_program.c \
../MCAL/UART_program.c \
../MCAL/icu.c 

OBJS += \
./MCAL/DIO_program.o \
./MCAL/GIE_program.o \
./MCAL/PWM0_program.o \
./MCAL/PWM_program.o \
./MCAL/UART_program.o \
./MCAL/icu.o 

C_DEPS += \
./MCAL/DIO_program.d \
./MCAL/GIE_program.d \
./MCAL/PWM0_program.d \
./MCAL/PWM_program.d \
./MCAL/UART_program.d \
./MCAL/icu.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/%.o: ../MCAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


