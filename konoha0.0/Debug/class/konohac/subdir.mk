################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../class/konohac/knh_Cmpl.c \
../class/konohac/knh_Cmpl_annotation.c \
../class/konohac/knh_Cmpl_arithmetic.c \
../class/konohac/knh_Cmpl_asm.c \
../class/konohac/knh_Cmpl_asmv.c \
../class/konohac/knh_Cmpl_class.c \
../class/konohac/knh_Cmpl_eprint.c \
../class/konohac/knh_Cmpl_label.c \
../class/konohac/knh_Cmpl_method.c \
../class/konohac/knh_Cmpl_run.c \
../class/konohac/knh_Cmpl_seval.c \
../class/konohac/knh_Cmpl_variable.c \
../class/konohac/knh_Stmt.c \
../class/konohac/knh_Stmt_expr.c \
../class/konohac/knh_Stmt_foreach.c \
../class/konohac/knh_Stmt_meta.c \
../class/konohac/knh_Stmt_method.c \
../class/konohac/knh_Stmt_trycatch.c \
../class/konohac/knh_Stmt_using.c \
../class/konohac/knh_Stmt_value.c \
../class/konohac/knh_String_parser.c \
../class/konohac/knh_Token.c \
../class/konohac/knh_Token_generics.c \
../class/konohac/knh_Token_parser.c \
../class/konohac/knh_VirtualMachineCode.c \
../class/konohac/stmtvisit_asm.c \
../class/konohac/stmtvisit_declc.c \
../class/konohac/stmtvisit_declm.c \
../class/konohac/stmtvisit_declv.c 

OBJS += \
./class/konohac/knh_Cmpl.o \
./class/konohac/knh_Cmpl_annotation.o \
./class/konohac/knh_Cmpl_arithmetic.o \
./class/konohac/knh_Cmpl_asm.o \
./class/konohac/knh_Cmpl_asmv.o \
./class/konohac/knh_Cmpl_class.o \
./class/konohac/knh_Cmpl_eprint.o \
./class/konohac/knh_Cmpl_label.o \
./class/konohac/knh_Cmpl_method.o \
./class/konohac/knh_Cmpl_run.o \
./class/konohac/knh_Cmpl_seval.o \
./class/konohac/knh_Cmpl_variable.o \
./class/konohac/knh_Stmt.o \
./class/konohac/knh_Stmt_expr.o \
./class/konohac/knh_Stmt_foreach.o \
./class/konohac/knh_Stmt_meta.o \
./class/konohac/knh_Stmt_method.o \
./class/konohac/knh_Stmt_trycatch.o \
./class/konohac/knh_Stmt_using.o \
./class/konohac/knh_Stmt_value.o \
./class/konohac/knh_String_parser.o \
./class/konohac/knh_Token.o \
./class/konohac/knh_Token_generics.o \
./class/konohac/knh_Token_parser.o \
./class/konohac/knh_VirtualMachineCode.o \
./class/konohac/stmtvisit_asm.o \
./class/konohac/stmtvisit_declc.o \
./class/konohac/stmtvisit_declm.o \
./class/konohac/stmtvisit_declv.o 

C_DEPS += \
./class/konohac/knh_Cmpl.d \
./class/konohac/knh_Cmpl_annotation.d \
./class/konohac/knh_Cmpl_arithmetic.d \
./class/konohac/knh_Cmpl_asm.d \
./class/konohac/knh_Cmpl_asmv.d \
./class/konohac/knh_Cmpl_class.d \
./class/konohac/knh_Cmpl_eprint.d \
./class/konohac/knh_Cmpl_label.d \
./class/konohac/knh_Cmpl_method.d \
./class/konohac/knh_Cmpl_run.d \
./class/konohac/knh_Cmpl_seval.d \
./class/konohac/knh_Cmpl_variable.d \
./class/konohac/knh_Stmt.d \
./class/konohac/knh_Stmt_expr.d \
./class/konohac/knh_Stmt_foreach.d \
./class/konohac/knh_Stmt_meta.d \
./class/konohac/knh_Stmt_method.d \
./class/konohac/knh_Stmt_trycatch.d \
./class/konohac/knh_Stmt_using.d \
./class/konohac/knh_Stmt_value.d \
./class/konohac/knh_String_parser.d \
./class/konohac/knh_Token.d \
./class/konohac/knh_Token_generics.d \
./class/konohac/knh_Token_parser.d \
./class/konohac/knh_VirtualMachineCode.d \
./class/konohac/stmtvisit_asm.d \
./class/konohac/stmtvisit_declc.d \
./class/konohac/stmtvisit_declm.d \
./class/konohac/stmtvisit_declv.d 


# Each subdirectory must supply rules for building sources it contributes
class/konohac/%.o: ../class/konohac/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DKONOHA_DEBUGMODE -DKONOHA_MONOLITHIC -I"/home/kimio/Development/workspace/konoha0.0/include" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


