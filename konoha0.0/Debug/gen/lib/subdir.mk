################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../gen/lib/m_.c \
../gen/lib/readline_.c 

OBJS += \
./gen/lib/m_.o \
./gen/lib/readline_.o 

C_DEPS += \
./gen/lib/m_.d \
./gen/lib/readline_.d 


# Each subdirectory must supply rules for building sources it contributes
gen/lib/%.o: ../gen/lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DKONOHA_DEBUGMODE -DKONOHA_MONOLITHIC -DKONOHA_DEMOMODE -I"/Users/kiki/Developments/workspace/konoha0.0/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


