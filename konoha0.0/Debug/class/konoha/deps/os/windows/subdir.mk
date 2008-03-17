################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../class/konoha/deps/os/windows/file__windows.c 

OBJS += \
./class/konoha/deps/os/windows/file__windows.o 

C_DEPS += \
./class/konoha/deps/os/windows/file__windows.d 


# Each subdirectory must supply rules for building sources it contributes
class/konoha/deps/os/windows/%.o: ../class/konoha/deps/os/windows/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DKONOHA_DEBUGMODE -DKONOHA_MONOLITHIC -I"/home/kimio/Development/workspace/konoha0.0/include" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


