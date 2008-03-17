################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../gen/konoha_load_.c \
../gen/konoha_spec_.c \
../gen/konoha_tuple_.c \
../gen/konoha_vm_.c \
../gen/konohac_asm_.c \
../gen/konohac_parser_.c \
../gen/konohac_visitor_.c 

OBJS += \
./gen/konoha_load_.o \
./gen/konoha_spec_.o \
./gen/konoha_tuple_.o \
./gen/konoha_vm_.o \
./gen/konohac_asm_.o \
./gen/konohac_parser_.o \
./gen/konohac_visitor_.o 

C_DEPS += \
./gen/konoha_load_.d \
./gen/konoha_spec_.d \
./gen/konoha_tuple_.d \
./gen/konoha_vm_.d \
./gen/konohac_asm_.d \
./gen/konohac_parser_.d \
./gen/konohac_visitor_.d 


# Each subdirectory must supply rules for building sources it contributes
gen/%.o: ../gen/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DKONOHA_DEBUGMODE -DKONOHA_MONOLITHIC -I"/home/kimio/Development/workspace/konoha0.0/include" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


