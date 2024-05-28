CC = aarch64-none-elf-gcc
CXX = aarch64-none-elf-g++
AS = aarch64-none-elf-as
AR = aarch64-none-elf-ar
prefix:=$(HOME)/.cros/root

COMMANDS_SRCS = $(wildcard src/commands/*.cpp)
SHELL_OBJS = src/shell.o src/utility.o src/command.o 
INIT_OBJ = init.o

COMMANDS_TARGETS = $(COMMANDS_SRCS:src/commands/%.cpp=bin/%)
SHELL_TARGET = shell
INIT_TARGET = init

CXXFLAGS = -I$(prefix)/include -Isrc -Isrc/commands -ffreestanding -nostdlib -fpermissive -fno-exceptions -fno-rtti -Wall -Wextra -ggdb -O0
LDFLAGS = -L$(prefix)/lib -nostdlib
LIBS = -lc -lsyscall

.PHONY: all 
all: $(COMMANDS_TARGETS) $(SHELL_TARGET) $(INIT_TARGET)

.PHONY: clean
clean:
	rm -rf ./bin $(SHELL_TARGET) $(INIT_TARGET) $(SHELL_OBJS) $(INIT_OBJ) src/commands/*.o

.PHONY: install
install:
	mkdir -p $(prefix)/bin
	cp -a bin/. $(prefix)/bin
	cp $(SHELL_TARGET) $(prefix)/bin
	cp $(INIT_TARGET) $(prefix)/bin

# Compiling individual command files
bin/%: src/commands/%.o
	@mkdir -p bin 
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $@ $< $(LIBS)

# Compiling shell.cpp
$(SHELL_TARGET): $(SHELL_OBJS)
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)

# Compiling shell INIT
$(INIT_TARGET): $(INIT_OBJ) 
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)
