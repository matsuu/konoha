################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include package/math/subdir.mk
-include gen/package/subdir.mk
-include gen/subdir.mk
-include gen/driver/subdir.mk
-include ext/subdir.mk
-include driver/mysql/subdir.mk
-include class/naruto/subdir.mk
-include class/konohac/subdir.mk
-include class/konoha/vm/subdir.mk
-include class/konoha/subdir.mk
-include class/konoha/deps/os/windows/subdir.mk
-include class/konoha/deps/os/tk/subdir.mk
-include class/konoha/deps/os/macosx/subdir.mk
-include class/konoha/deps/os/linux/subdir.mk
-include class/konoha/deps/api/win32/subdir.mk
-include class/konoha/deps/api/posix/subdir.mk
-include class/konoha/deps/api/btron/subdir.mk
-include api/naruto/subdir.mk
-include api/konoha/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: konoha

# Tool invocations
konoha: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc  -o"konoha" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) konoha
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
