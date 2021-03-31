# compiler
CC = g++

#compiler flags
CFLAGS = -Wall 
LIBS = -lncurses

#build target
TARGET_NAME = linerender

#directorys
BUILD_DIR = build
SRC_DIR = src

#Build target
TARGET = $(BUILD_DIR)/$(TARGET_NAME)


#Source files
SRC =$(shell find $(SRC_DIR) -name '*.cpp')

#Build commands
REMOVE_BUILD = $(shell rm -r $(BUILD_DIR))
BUILD = $(shell mkdir -p $(BUILD_DIR)) $(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)


default:
	$(BUILD)

new: 
	$(REMOVE_BUILD)
	$(BUILD)

.PHONY: clean

clean: 
	$(REMOVE_BUILD)
