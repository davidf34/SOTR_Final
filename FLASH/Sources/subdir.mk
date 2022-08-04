################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/BinarySem.c" \
"../Sources/Eventos.c" \
"../Sources/Events.c" \
"../Sources/Message.c" \
"../Sources/Mutex.c" \
"../Sources/Queue.c" \
"../Sources/RTOS.c" \
"../Sources/Semaforo.c" \
"../Sources/main.c" \
"../Sources/portable.c" \
"../Sources/scheduller.c" \
"../Sources/task.c" \

C_SRCS += \
../Sources/BinarySem.c \
../Sources/Eventos.c \
../Sources/Events.c \
../Sources/Message.c \
../Sources/Mutex.c \
../Sources/Queue.c \
../Sources/RTOS.c \
../Sources/Semaforo.c \
../Sources/main.c \
../Sources/portable.c \
../Sources/scheduller.c \
../Sources/task.c \

OBJS += \
./Sources/BinarySem_c.obj \
./Sources/Eventos_c.obj \
./Sources/Events_c.obj \
./Sources/Message_c.obj \
./Sources/Mutex_c.obj \
./Sources/Queue_c.obj \
./Sources/RTOS_c.obj \
./Sources/Semaforo_c.obj \
./Sources/main_c.obj \
./Sources/portable_c.obj \
./Sources/scheduller_c.obj \
./Sources/task_c.obj \

OBJS_QUOTED += \
"./Sources/BinarySem_c.obj" \
"./Sources/Eventos_c.obj" \
"./Sources/Events_c.obj" \
"./Sources/Message_c.obj" \
"./Sources/Mutex_c.obj" \
"./Sources/Queue_c.obj" \
"./Sources/RTOS_c.obj" \
"./Sources/Semaforo_c.obj" \
"./Sources/main_c.obj" \
"./Sources/portable_c.obj" \
"./Sources/scheduller_c.obj" \
"./Sources/task_c.obj" \

C_DEPS += \
./Sources/BinarySem_c.d \
./Sources/Eventos_c.d \
./Sources/Events_c.d \
./Sources/Message_c.d \
./Sources/Mutex_c.d \
./Sources/Queue_c.d \
./Sources/RTOS_c.d \
./Sources/Semaforo_c.d \
./Sources/main_c.d \
./Sources/portable_c.d \
./Sources/scheduller_c.d \
./Sources/task_c.d \

C_DEPS_QUOTED += \
"./Sources/BinarySem_c.d" \
"./Sources/Eventos_c.d" \
"./Sources/Events_c.d" \
"./Sources/Message_c.d" \
"./Sources/Mutex_c.d" \
"./Sources/Queue_c.d" \
"./Sources/RTOS_c.d" \
"./Sources/Semaforo_c.d" \
"./Sources/main_c.d" \
"./Sources/portable_c.d" \
"./Sources/scheduller_c.d" \
"./Sources/task_c.d" \

OBJS_OS_FORMAT += \
./Sources/BinarySem_c.obj \
./Sources/Eventos_c.obj \
./Sources/Events_c.obj \
./Sources/Message_c.obj \
./Sources/Mutex_c.obj \
./Sources/Queue_c.obj \
./Sources/RTOS_c.obj \
./Sources/Semaforo_c.obj \
./Sources/main_c.obj \
./Sources/portable_c.obj \
./Sources/scheduller_c.obj \
./Sources/task_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/BinarySem_c.obj: ../Sources/BinarySem.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/BinarySem.args" -ObjN="Sources/BinarySem_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/Eventos_c.obj: ../Sources/Eventos.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/Eventos.args" -ObjN="Sources/Eventos_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/Events_c.obj: ../Sources/Events.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/Events.args" -ObjN="Sources/Events_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/Message_c.obj: ../Sources/Message.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/Message.args" -ObjN="Sources/Message_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/Mutex_c.obj: ../Sources/Mutex.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/Mutex.args" -ObjN="Sources/Mutex_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/Queue_c.obj: ../Sources/Queue.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/Queue.args" -ObjN="Sources/Queue_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/RTOS_c.obj: ../Sources/RTOS.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/RTOS.args" -ObjN="Sources/RTOS_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/Semaforo_c.obj: ../Sources/Semaforo.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/Semaforo.args" -ObjN="Sources/Semaforo_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/main.args" -ObjN="Sources/main_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/portable_c.obj: ../Sources/portable.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/portable.args" -ObjN="Sources/portable_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/scheduller_c.obj: ../Sources/scheduller.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/scheduller.args" -ObjN="Sources/scheduller_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/task_c.obj: ../Sources/task.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/task.args" -ObjN="Sources/task_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


