################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../class/konoha/vm/konoha_api.c \
../class/konoha/vm/konoha_call.c \
../class/konoha/vm/konoha_ext.c \
../class/konoha/vm/konoha_hobject.c \
../class/konoha/vm/konoha_init.c \
../class/konoha/vm/konoha_loader.c \
../class/konoha/vm/konoha_metadata.c \
../class/konoha/vm/konoha_print.c \
../class/konoha/vm/konoha_shell.c \
../class/konoha/vm/konoha_tclass.c \
../class/konoha/vm/konoha_tconst.c \
../class/konoha/vm/konoha_texpt.c \
../class/konoha/vm/konoha_tglobal.c \
../class/konoha/vm/konoha_throwcatch.c \
../class/konoha/vm/konoha_tmapmap.c \
../class/konoha/vm/konoha_tmemory.c \
../class/konoha/vm/konoha_tmethod.c \
../class/konoha/vm/konoha_tname.c \
../class/konoha/vm/konoha_tstruct.c \
../class/konoha/vm/konoha_typesystem.c 

OBJS += \
./class/konoha/vm/konoha_api.o \
./class/konoha/vm/konoha_call.o \
./class/konoha/vm/konoha_ext.o \
./class/konoha/vm/konoha_hobject.o \
./class/konoha/vm/konoha_init.o \
./class/konoha/vm/konoha_loader.o \
./class/konoha/vm/konoha_metadata.o \
./class/konoha/vm/konoha_print.o \
./class/konoha/vm/konoha_shell.o \
./class/konoha/vm/konoha_tclass.o \
./class/konoha/vm/konoha_tconst.o \
./class/konoha/vm/konoha_texpt.o \
./class/konoha/vm/konoha_tglobal.o \
./class/konoha/vm/konoha_throwcatch.o \
./class/konoha/vm/konoha_tmapmap.o \
./class/konoha/vm/konoha_tmemory.o \
./class/konoha/vm/konoha_tmethod.o \
./class/konoha/vm/konoha_tname.o \
./class/konoha/vm/konoha_tstruct.o \
./class/konoha/vm/konoha_typesystem.o 

C_DEPS += \
./class/konoha/vm/konoha_api.d \
./class/konoha/vm/konoha_call.d \
./class/konoha/vm/konoha_ext.d \
./class/konoha/vm/konoha_hobject.d \
./class/konoha/vm/konoha_init.d \
./class/konoha/vm/konoha_loader.d \
./class/konoha/vm/konoha_metadata.d \
./class/konoha/vm/konoha_print.d \
./class/konoha/vm/konoha_shell.d \
./class/konoha/vm/konoha_tclass.d \
./class/konoha/vm/konoha_tconst.d \
./class/konoha/vm/konoha_texpt.d \
./class/konoha/vm/konoha_tglobal.d \
./class/konoha/vm/konoha_throwcatch.d \
./class/konoha/vm/konoha_tmapmap.d \
./class/konoha/vm/konoha_tmemory.d \
./class/konoha/vm/konoha_tmethod.d \
./class/konoha/vm/konoha_tname.d \
./class/konoha/vm/konoha_tstruct.d \
./class/konoha/vm/konoha_typesystem.d 


# Each subdirectory must supply rules for building sources it contributes
class/konoha/vm/%.o: ../class/konoha/vm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DKONOHA_DEBUGMODE -DKONOHA_MONOLITHIC -I"/home/kimio/Development/workspace/konoha0.0/include" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


