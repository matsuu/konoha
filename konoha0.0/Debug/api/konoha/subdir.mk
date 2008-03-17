################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../api/konoha/knh_Array_api1.c \
../api/konoha/knh_Bool_api1.c \
../api/konoha/knh_Bytes_api1.c \
../api/konoha/knh_Bytes_api2.c \
../api/konoha/knh_Class_api1.c \
../api/konoha/knh_Class_api2.c \
../api/konoha/knh_Connection_api1.c \
../api/konoha/knh_Context_api0.c \
../api/konoha/knh_Context_api1.c \
../api/konoha/knh_DictMap_api1.c \
../api/konoha/knh_DictMap_api2.c \
../api/konoha/knh_DictSet_api1.c \
../api/konoha/knh_DictSet_api2.c \
../api/konoha/knh_Exception_api0.c \
../api/konoha/knh_Exception_api1.c \
../api/konoha/knh_Float_api1.c \
../api/konoha/knh_Float_api2.c \
../api/konoha/knh_HashMap_api1.c \
../api/konoha/knh_HashMap_api2.c \
../api/konoha/knh_HashSet_api1.c \
../api/konoha/knh_HashSet_api2.c \
../api/konoha/knh_Int_api0.c \
../api/konoha/knh_Int_api1.c \
../api/konoha/knh_Object_api0.c \
../api/konoha/knh_Object_api1.c \
../api/konoha/knh_Object_api2.c \
../api/konoha/knh_OutputStream_api0.c \
../api/konoha/knh_String_api1.c \
../api/konoha/knh_String_api2.c \
../api/konoha/knh_System_api1.c \
../api/konoha/knh_any_api0.c 

OBJS += \
./api/konoha/knh_Array_api1.o \
./api/konoha/knh_Bool_api1.o \
./api/konoha/knh_Bytes_api1.o \
./api/konoha/knh_Bytes_api2.o \
./api/konoha/knh_Class_api1.o \
./api/konoha/knh_Class_api2.o \
./api/konoha/knh_Connection_api1.o \
./api/konoha/knh_Context_api0.o \
./api/konoha/knh_Context_api1.o \
./api/konoha/knh_DictMap_api1.o \
./api/konoha/knh_DictMap_api2.o \
./api/konoha/knh_DictSet_api1.o \
./api/konoha/knh_DictSet_api2.o \
./api/konoha/knh_Exception_api0.o \
./api/konoha/knh_Exception_api1.o \
./api/konoha/knh_Float_api1.o \
./api/konoha/knh_Float_api2.o \
./api/konoha/knh_HashMap_api1.o \
./api/konoha/knh_HashMap_api2.o \
./api/konoha/knh_HashSet_api1.o \
./api/konoha/knh_HashSet_api2.o \
./api/konoha/knh_Int_api0.o \
./api/konoha/knh_Int_api1.o \
./api/konoha/knh_Object_api0.o \
./api/konoha/knh_Object_api1.o \
./api/konoha/knh_Object_api2.o \
./api/konoha/knh_OutputStream_api0.o \
./api/konoha/knh_String_api1.o \
./api/konoha/knh_String_api2.o \
./api/konoha/knh_System_api1.o \
./api/konoha/knh_any_api0.o 

C_DEPS += \
./api/konoha/knh_Array_api1.d \
./api/konoha/knh_Bool_api1.d \
./api/konoha/knh_Bytes_api1.d \
./api/konoha/knh_Bytes_api2.d \
./api/konoha/knh_Class_api1.d \
./api/konoha/knh_Class_api2.d \
./api/konoha/knh_Connection_api1.d \
./api/konoha/knh_Context_api0.d \
./api/konoha/knh_Context_api1.d \
./api/konoha/knh_DictMap_api1.d \
./api/konoha/knh_DictMap_api2.d \
./api/konoha/knh_DictSet_api1.d \
./api/konoha/knh_DictSet_api2.d \
./api/konoha/knh_Exception_api0.d \
./api/konoha/knh_Exception_api1.d \
./api/konoha/knh_Float_api1.d \
./api/konoha/knh_Float_api2.d \
./api/konoha/knh_HashMap_api1.d \
./api/konoha/knh_HashMap_api2.d \
./api/konoha/knh_HashSet_api1.d \
./api/konoha/knh_HashSet_api2.d \
./api/konoha/knh_Int_api0.d \
./api/konoha/knh_Int_api1.d \
./api/konoha/knh_Object_api0.d \
./api/konoha/knh_Object_api1.d \
./api/konoha/knh_Object_api2.d \
./api/konoha/knh_OutputStream_api0.d \
./api/konoha/knh_String_api1.d \
./api/konoha/knh_String_api2.d \
./api/konoha/knh_System_api1.d \
./api/konoha/knh_any_api0.d 


# Each subdirectory must supply rules for building sources it contributes
api/konoha/%.o: ../api/konoha/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DKONOHA_DEBUGMODE -DKONOHA_MONOLITHIC -I"/home/kimio/Development/workspace/konoha0.0/include" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


