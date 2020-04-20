# compiler settings
CXX=gcc

# Implented the solution for compiling with these flags found here:
# https://stackoverflow.com/questions/27669275/undefined-reference-to-in-os-kernel-linking
CFLAGS=-fno-PIC -g -m16 -ffreestanding -Os -Wall -fomit-frame-pointer

# build directory and included libs
BUILD_DIR=build
LIB_DIRS=graphics input menu score

# grabbing all source files + generating obj file names
SRC=main.c
SRC+=$(wildcard $(addsuffix /*.c, $(LIB_DIRS)))
OBJ=$(addprefix $(BUILD_DIR)/, $(notdir $(SRC:.c=.o)))

# making dirs searchable to make
vpath %.c $(LIB_DIRS)

all: $(OBJ)
	@echo 'building bootloader'
	@nasm -f elf32 -Fdwarf -g boot.asm -o $(BUILD_DIR)/boot.o
	@echo 'linking obj files'
	@ld -melf_i386 -nostartfiles -nostdlib -Tlinker.ld -L $(BUILD_DIR) -o os.elf $(OBJ)

# compiling all .c files into .o files
$(BUILD_DIR)/%.o: %.c
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)
	@echo "Compilation files removed"

force:
	@touch $(SRC)
	@echo "Forcing compilation"
	@echo "--------------------"
	@make all

help:
	@echo 'SRC: '
	@echo $(SRC)
	@echo 'OBJ: '
	@echo $(OBJ)
