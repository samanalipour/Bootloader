################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Applicaction/Src/FATFS_SD.c \
../Applicaction/Src/Hex_parser.c \
../Applicaction/Src/MY_FLASH.c \
../Applicaction/Src/Programming.c \
../Applicaction/Src/SD.c \
../Applicaction/Src/printf_redirect.c 

OBJS += \
./Applicaction/Src/FATFS_SD.o \
./Applicaction/Src/Hex_parser.o \
./Applicaction/Src/MY_FLASH.o \
./Applicaction/Src/Programming.o \
./Applicaction/Src/SD.o \
./Applicaction/Src/printf_redirect.o 

C_DEPS += \
./Applicaction/Src/FATFS_SD.d \
./Applicaction/Src/Hex_parser.d \
./Applicaction/Src/MY_FLASH.d \
./Applicaction/Src/Programming.d \
./Applicaction/Src/SD.d \
./Applicaction/Src/printf_redirect.d 


# Each subdirectory must supply rules for building sources it contributes
Applicaction/Src/%.o Applicaction/Src/%.su Applicaction/Src/%.cyclo: ../Applicaction/Src/%.c Applicaction/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/saman/Desktop/Bootloader/Bootloader/Applicaction/Inc" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Applicaction-2f-Src

clean-Applicaction-2f-Src:
	-$(RM) ./Applicaction/Src/FATFS_SD.cyclo ./Applicaction/Src/FATFS_SD.d ./Applicaction/Src/FATFS_SD.o ./Applicaction/Src/FATFS_SD.su ./Applicaction/Src/Hex_parser.cyclo ./Applicaction/Src/Hex_parser.d ./Applicaction/Src/Hex_parser.o ./Applicaction/Src/Hex_parser.su ./Applicaction/Src/MY_FLASH.cyclo ./Applicaction/Src/MY_FLASH.d ./Applicaction/Src/MY_FLASH.o ./Applicaction/Src/MY_FLASH.su ./Applicaction/Src/Programming.cyclo ./Applicaction/Src/Programming.d ./Applicaction/Src/Programming.o ./Applicaction/Src/Programming.su ./Applicaction/Src/SD.cyclo ./Applicaction/Src/SD.d ./Applicaction/Src/SD.o ./Applicaction/Src/SD.su ./Applicaction/Src/printf_redirect.cyclo ./Applicaction/Src/printf_redirect.d ./Applicaction/Src/printf_redirect.o ./Applicaction/Src/printf_redirect.su

.PHONY: clean-Applicaction-2f-Src

