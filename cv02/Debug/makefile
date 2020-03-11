################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
cviceni1.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
cviceni1.list \

OBJCOPY_BIN += \
cviceni1.bin \


# All Target
all: cviceni1.elf secondary-outputs

# Tool invocations
cviceni1.elf: $(OBJS) $(USER_OBJS) D:\www\xbenit01\MMIA\cv02\STM32F030R8TX_FLASH.ld
	arm-none-eabi-gcc -o "cviceni1.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0 -T"D:\www\xbenit01\MMIA\cv02\STM32F030R8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="cviceni1.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

cviceni1.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "cviceni1.list"
	@echo 'Finished building: $@'
	@echo ' '

cviceni1.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "cviceni1.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
