################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/fdebug.cpp \
../src/fdebugclient.cpp \
../src/fdebugconfig.cpp \
../src/fdebugexception.cpp \
../src/fdebugmessage.cpp 

OBJS += \
./src/fdebug.o \
./src/fdebugclient.o \
./src/fdebugconfig.o \
./src/fdebugexception.o \
./src/fdebugmessage.o 

CPP_DEPS += \
./src/fdebug.d \
./src/fdebugclient.d \
./src/fdebugconfig.d \
./src/fdebugexception.d \
./src/fdebugmessage.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../include -O3 -Wall -c -fmessage-length=0 `xml2-config --cflags --libs` -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


