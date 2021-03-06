#############################################################################
#
# makefile.due common settings for Arduino Due projects
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# settings for Arduino Due projects
TARGET            ?= arduino_due
SERIAL_PORT       ?= COM3
CONSOLE_BAUDRATE  ?= 38400
STACK_SIZE        ?= 81920
HEAP              ?= BMPTK

PROJECT 	  	  ?= src/main

SOURCES 		  += ./src/tasks/buttonController.cpp ./src/tasks/soundController.cpp ./src/tasks/runGameController.cpp ./src/entities/gameParameters.cpp ./src/tasks/displayController.cpp ./src/tasks/command.cpp ./src/tasks/registerController.cpp ./src/tasks/initGameController.cpp ./src/tasks/receiver.cpp ./src/tasks/transmitter.cpp
HEADERS			  += ./src/tasks/buttonController.h ./src/tasks/soundController.h ./src/tasks/runGameController.h ./src/entities/gameParameters.h ./src/tasks/displayController.h ./src/tasks/command.h ./src/tasks/registerController.h ./src/tasks/controller.h  ./src/tasks/initGameController.h ./src/tasks/transmitter.h ./src/tasks/transmitter.h

# use hwlib
SEARCH            += ../libs/hwlib
SOURCES           += hwlib.cpp
# use the rtos
SEARCH            += ../libs/rtos
HEADERS           += coroutine.hpp switch_to.hpp
SOURCES           += coroutine.cpp switch_to.asm
HEADERS           += rtos.hpp
SOURCES           += rtos.cpp 

DEFINES           += -DPlAYER=2
DEFINES           += -DLEADER=1
DEFINES           += -DGAMEMODE=PLAYER

player:
	export DEFINES=DEFINES-DGAMEMODE=PLAYER

leader:
	export DEFINES=DEFINES-DGAMEMODE=LEADER
runAvr:
	sudo stty -F /dev/ttyACM0 speed 1200 cs8 -cstopb -parenb && make build && sudo bossac --info --port "ttyACM0" --erase --write --verify --reset --debug --boot -U false ./src/main.bin && sudo platformio serialports monitor -b 38400

playerRun: player runAvr
leaderRun: leader runAvr

# set BMPTK to the bmptk subdirectory
BMPTK := $(BMPTK)../libs/bmptk/

# Defer to the bmptk/Makefile.inc to do the work
include $(BMPTK)Makefile.inc
