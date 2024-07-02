################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/subdir.mk
-include HAL/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
NEW_VERSION_WITHKPAD.lss \

FLASH_IMAGE += \
NEW_VERSION_WITHKPAD.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: NEW_VERSION_WITHKPAD.elf secondary-outputs

# Tool invocations
NEW_VERSION_WITHKPAD.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,NEW_VERSION_WITHKPAD.map -mmcu=atmega32 -o "NEW_VERSION_WITHKPAD.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

NEW_VERSION_WITHKPAD.lss: NEW_VERSION_WITHKPAD.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S NEW_VERSION_WITHKPAD.elf  >"NEW_VERSION_WITHKPAD.lss"
	@echo 'Finished building: $@'
	@echo ' '

NEW_VERSION_WITHKPAD.hex: NEW_VERSION_WITHKPAD.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex NEW_VERSION_WITHKPAD.elf  "NEW_VERSION_WITHKPAD.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: NEW_VERSION_WITHKPAD.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 NEW_VERSION_WITHKPAD.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) NEW_VERSION_WITHKPAD.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
