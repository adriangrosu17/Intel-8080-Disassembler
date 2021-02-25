WIN ?= y
EXT ?= elf
DEBUG ?= n
CC = gcc
CXX = g++
TARGET_EXEC ?= 8080_disass.$(EXT)
BUILD_DIR ?= build
SRC_DIRS ?= src
DEBUG ?= n
SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
ifeq ($(WIN), y)
	TARGET_ARCH = x86_64
	CC = $(TARGET_ARCH)-w64-mingw32-gcc
	CXX = $(TARGET_ARCH)-w64-mingw32-g++
	EXT = exe
endif

INC_DIRS += inc
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP
CFLAGS ?= -Wall -Wextra -Werror -pedantic -std=c99
ifeq ($(DEBUG), y)
	CFLAGS += -g
	CPPFLAGS += -DDEBUG
endif
LDFLAGS += -Xlinker -Map=$(BUILD_DIR)/$(TARGET_EXEC).map

# executable
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)
-include $(DEPS)

MKDIR_P ?= mkdir -p

