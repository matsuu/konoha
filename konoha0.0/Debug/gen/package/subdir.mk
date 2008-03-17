################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../gen/package/konoha_.c \
../gen/package/konohac_.c \
../gen/package/math_.c \
../gen/package/naruto_.c 

OBJS += \
./gen/package/konoha_.o \
./gen/package/konohac_.o \
./gen/package/math_.o \
./gen/package/naruto_.o 

C_DEPS += \
./gen/package/konoha_.d \
./gen/package/konohac_.d \
./gen/package/math_.d \
./gen/package/naruto_.d 


# Each subdirectory must supply rules for building sources it contributes
gen/package/%.o: ../gen/package/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DKONOHA_DEBUGMODE -DKONOHA_MONOLITHIC -I"/home/kimio/Development/workspace/konoha0.0/include" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


