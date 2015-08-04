################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/HCI_Utils/HCI_3WireUART.cpp 

OBJS += \
./src/HCI_Utils/HCI_3WireUART.o 

CPP_DEPS += \
./src/HCI_Utils/HCI_3WireUART.d 


# Each subdirectory must supply rules for building sources it contributes
src/HCI_Utils/%.o: ../src/HCI_Utils/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


