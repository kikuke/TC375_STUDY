################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ASW/Module/SSD1306/SSD1306.c 

COMPILED_SRCS += \
ASW/Module/SSD1306/SSD1306.src 

C_DEPS += \
ASW/Module/SSD1306/SSD1306.d 

OBJS += \
ASW/Module/SSD1306/SSD1306.o 


# Each subdirectory must supply rules for building sources it contributes
ASW/Module/SSD1306/SSD1306.src: ../ASW/Module/SSD1306/SSD1306.c ASW/Module/SSD1306/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/KJS/Documents/DV/TC375_STUDY/Main_Study/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<"
ASW/Module/SSD1306/SSD1306.o: ASW/Module/SSD1306/SSD1306.src ASW/Module/SSD1306/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-ASW-2f-Module-2f-SSD1306

clean-ASW-2f-Module-2f-SSD1306:
	-$(RM) ASW/Module/SSD1306/SSD1306.d ASW/Module/SSD1306/SSD1306.o ASW/Module/SSD1306/SSD1306.src

.PHONY: clean-ASW-2f-Module-2f-SSD1306

