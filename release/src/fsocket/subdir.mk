################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/fsocket/fsocket.cpp 

OBJS += \
./src/fsocket/fsocket.o 

CPP_DEPS += \
./src/fsocket/fsocket.d 


# Each subdirectory must supply rules for building sources it contributes
src/fsocket/%.o: ../src/fsocket/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../include -O3 -Wall -c -fmessage-length=0 `xml2-config --cflags --libs` -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


