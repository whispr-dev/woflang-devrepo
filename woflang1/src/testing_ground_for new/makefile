# Makefile for Woflang Assembly

# Compiler and linker settings
NASM=nasm
LD=ld

# Flags
NASMFLAGS=-f win64    # Use -f elf64 for Linux
LDFLAGS=

# Source files
ASM_SOURCES=main64.asm str64.asm mth64.asm lgc64.asm err64.asm woflang_modul64.asm

# Object files
OBJECTS=$(ASM_SOURCES:.asm=.obj)    # Use .o instead of .obj for Linux

# Output executable
EXECUTABLE=woflang.exe              # Remove .exe for Linux

# Default target
all: $(EXECUTABLE)

# Link object files to create executable
$(EXECUTABLE): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

# Compile assembly files
%.obj: %.asm                        # Use %.o instead of %.obj for Linux
	$(NASM) $(NASMFLAGS) -o $@ $<

# Clean built files
clean:
	del *.obj $(EXECUTABLE)         # Use rm for Linux
	
# Help target
help:
	@echo "Available targets:"
	@echo "  all      - Build everything (default)"
	@echo "  clean    - Remove built files"
	@echo "  help     - Show this help"