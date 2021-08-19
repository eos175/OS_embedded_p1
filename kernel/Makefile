KERNEL := kernel.elf

CXX = g++
CC = gcc
LD = ld
AS = nasm


## https://gcc.gnu.org/onlinedocs/gcc-3.4.6/gcc/Optimize-Options.html

CXXFLAGS = -fno-builtin \
            -nostdlib \
            -fno-rtti \
            -fno-exceptions \
            -std=c++0x -O2

ASFLAGS = -f elf64 -O2

CFLAGS = -O1 -pipe \
	-mcmodel=kernel


LDFLAGS =

INTERNALLDFLAGS :=         \
	-Tlinker.ld            \
	-nostdlib              \
	-zmax-page-size=0x1000 \
	-static                \
	--no-dynamic-linker    \
	-ztext

INTERNALCFLAGS  :=       \
	-I.                  \
	-Iinclude            \
	-std=gnu11           \
	-ffreestanding       \
	-fno-stack-protector \
	-fno-pic      \
	-mno-80387           \
	-mno-mmx             \
	-mno-3dnow           \
	-mno-red-zone	\
	-ffast-math


CPPFILES := $(shell find ./ -type f -name '*.cpp')
CFILES := $(shell find ./ -type f -name '*.c')
ASMFILES := $(shell find ./ -type f -name '*.asm')

OBJ    := $(CFILES:.c=.o) \
			$(ASMFILES:.asm=.o) \
			$(CPPFILES:.cpp=.o)


.PHONY: all clean

all: $(KERNEL)

stivale2.h:
	wget https://github.com/stivale/stivale/raw/master/stivale2.h

$(KERNEL): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) $(INTERNALLDFLAGS) -o $@

%.o: %.c stivale2.h
	$(CC) $(CFLAGS) $(INTERNALCFLAGS) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@




clean:
	rm -rf $(KERNEL) $(OBJ)
