## 
AR     :=/usr/bin/ar rcu
AS     :=/usr/bin/as
CC     :=/usr/bin/gcc
CXX    :=/usr/bin/g++
LINKER :=/usr/bin/g++
ASFLAGS     :=
CFLAGS      :=
CXXFLAGS    := -std=c++14
CPPFLAGS    := -MMD -MP
LDFLAGS     :=
LINKERFLAGS :=

##
TARGET_EXEC  :=TestGame
BUILD_DIR    :=build
SRC_DIR      :=src
OBJ_DIR      :=obj
EXE_DIR      :=bin

##
LIBS_PATH += .
LIBS_PATH += /usr/lib
LIBS_PATH += ./lib
LIBS_PATH += ./lib/Debug/
LIBS_PATH := $(addprefix -L,$(LIBS_PATH))

##
LIBS += sfml-graphics
LIBS += sfml-system
LIBS += sfml-window
LIBS := $(addprefix -l,$(LIBS))

##
INC_PATH += .
INC_PATH += /usr/include
INC_PATH += ./include
INC_PATH := $(addprefix -I,$(INC_PATH))

##
MAKE_DIR :=mkdir -p

DEBUG ?= 0
ifeq ($(DEBUG), 1)
	CONFIG_NAME = Debug
	CFLAGS      += -pg -g -O0 -Wall
	CXXFLAGS    += -pg -g -O0 -Wall
else
	CONFIG_NAME = Release
	CFLAGS      += -O -W
	CXXFLAGS    += -O -W
endif

.PHONY: all clean prebuild postbuild rebuild
SRC_PATH     :=$(SRC_DIR)
OBJ_PATH     :=$(BUILD_DIR)/$(CONFIG_NAME)/$(OBJ_DIR)
OUTPUT_FILE  :=$(TARGET_EXEC)

##
C_SRC_FILES   := $(shell find $(SRC_PATH) -name '*.c')
CPP_SRC_FILES := $(shell find $(SRC_PATH) -name '*.cpp')
OBJ_FILES := $(C_SRC_FILES:%.c=$(OBJ_PATH)/%.o)
OBJ_FILES += $(CPP_SRC_FILES:%.cpp=$(OBJ_PATH)/%.o)

##
DEPS := $(OBJ_FILES:.o=.d)

all: $(OUTPUT_FILE)

$(OUTPUT_FILE): $(OBJ_PATH) $(OBJ_FILES)
	@$(MAKE_DIR) $(@D)
	$(LINKER) $(LINKERFLAGS) $(LIBS_PATH) $(LIBS) $(OBJ_FILES) -o $(OUTPUT_FILE)

$(OBJ_PATH)/%.o: %.c
	@$(MAKE_DIR) $(@D)
	$(CC) $(INC_PATH) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)/%.o: %.cpp
	@$(MAKE_DIR) $(@D)
	$(CXX) $(INC_PATH) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(OBJ_PATH):
	@$(MAKE_DIR) $@

clean:
	@$(RM) -r $(OBJ_PATH)

-include $(DEPS)
