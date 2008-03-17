################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../driver/mysql/knh_Connection__mysql.c 

OBJS += \
./driver/mysql/knh_Connection__mysql.o 

C_DEPS += \
./driver/mysql/knh_Connection__mysql.d 


# Each subdirectory must supply rules for building sources it contributes
driver/mysql/%.o: ../driver/mysql/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DKONOHA_DEBUGMODE -DKONOHA_MONOLITHIC -I"/home/kimio/Development/workspace/konoha0.0/include" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


