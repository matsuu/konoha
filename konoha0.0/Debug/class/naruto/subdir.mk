################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../class/naruto/knh_Amazon.c \
../class/naruto/knh_Counter.c 

OBJS += \
./class/naruto/knh_Amazon.o \
./class/naruto/knh_Counter.o 

C_DEPS += \
./class/naruto/knh_Amazon.d \
./class/naruto/knh_Counter.d 


# Each subdirectory must supply rules for building sources it contributes
class/naruto/%.o: ../class/naruto/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DKONOHA_DEBUGMODE -DKONOHA_MONOLITHIC -I"/home/kimio/Development/workspace/konoha0.0/include" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


