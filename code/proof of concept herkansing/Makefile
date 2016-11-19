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

# Entities
SOURCES 		  += src/entities/weapon.cpp src/entities/arsenal.cpp src/entities/gameParameters.cpp
HEADERS			  += src/entities/weapon.h src/entities/arsenal.h src/entities/gameParameters.h

#application logic
SOURCES           += src/applicationLogic/command.cpp
HEADERS           += src/applicationLogic/command.h

#Boundaries
SOURCES           += src/boundaries/button.cpp src/boundaries/receiver.cpp src/boundaries/sound.cpp src/boundaries/transmitter.cpp
HEADERS           += src/boundaries/button.h src/boundaries/receiver.h src/boundaries/sound.h src/boundaries/transmitter.h

#controllers
SOURCES           += src/controllers/displayController.cpp src/controllers/initGameController.cpp src/controllers/runGameController.cpp
HEADERS           += src/controllers/displayController.h src/controllers/initGameController.h src/controllers/runGameController.h

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
	sudo stty -F /dev/ttyACM0 speed 1200 cs8 -cstopb -parenb && make build && sudo bossac --info --port "ttyACM0" --erase --write --verify --reset --boot -U false ./src/main.bin && sudo platformio serialports monitor -b 38400

playerRun: player runAvr
leaderRun: leader runAvr

# set BMPTK to the bmptk subdirectory
BMPTK := $(BMPTK)../libs/bmptk/

# Defer to the bmptk/Makefile.inc to do the work
include $(BMPTK)Makefile.inc
