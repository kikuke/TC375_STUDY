################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ASW/Module/I2C/Module_I2C.c 

COMPILED_SRCS += \
ASW/Module/I2C/Module_I2C.src 

C_DEPS += \
ASW/Module/I2C/Module_I2C.d 

OBJS += \
ASW/Module/I2C/Module_I2C.o 


# Each subdirectory must supply rules for building sources it contributes
ASW/Module/I2C/Module_I2C.src: ../ASW/Module/I2C/Module_I2C.c ASW/Module/I2C/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/KJS/Documents/DV/TC375_STUDY/Main_Study/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
ASW/Module/I2C/Module_I2C.o: ASW/Module/I2C/Module_I2C.src ASW/Module/I2C/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-ASW-2f-Module-2f-I2C

clean-ASW-2f-Module-2f-I2C:
	-$(RM) ASW/Module/I2C/Module_I2C.d ASW/Module/I2C/Module_I2C.o ASW/Module/I2C/Module_I2C.src

.PHONY: clean-ASW-2f-Module-2f-I2C

