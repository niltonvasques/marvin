#This file is part of Marvin OS project.
#
#Marvin OS is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.

#Marvin OS is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.

#You should have received a copy of the GNU General Public License
#along with Marvin OS.  If not, see <http://www.gnu.org/licenses/>.

#	Description: Makefile.
#	Author: Carlos Marx
#	Author: Nilton Vasques
#	Date: 20 - 03 - 2013
#

#Instructions
# $ ^ is substituted with all of the target ’ s dependancy files
# $ < is the first dependancy and $@ is the target files
CC 		= i586-elf-gcc
LD 		= i586-elf-ld
CFLAGS 		= -Wall -Wextra -Werror -nostdlib -nostartfiles -nodefaultlibs -fno-builtin
ASM 		= nasm
C_SOURCES 	= $(wildcard src/kernel/system/*.c src/kernel/drivers/*.c)
HEADERS 	= $(wildcard src/kernel/system/*.h src/kernel/drivers/*.h)
OBJ 		= ${C_SOURCES:.c=.o}
KLINK 		= src/kernel/system/kernel.lnk
KENTRY 		= src/kernel/system/kernel_entry.asm
INC_DIRS 	= -Isrc/kernel/system -Isrc/kernel/drivers

all: mkbin boot.img
	
run: all
	export PATH=$PATH:/usr/local/cross/bin
	qemu-system-x86_64 -fda bin/boot.img
	
debug: all
	bochs -f bochsrc

boot.img: bin/boot0.bin bin/boot1.bin bin/kernel.bin bin/pad
	cat $^ > bin/boot.img

bin/boot0.bin: src/boot/boot0.asm
	$(ASM) $< -f bin -I src/boot/ -o $@

bin/boot1.bin: src/boot/boot1.asm
	$(ASM) $< -f bin -I src/boot/ -o $@
	
bin/kernel_entry.o: $(KENTRY)
	$(ASM) -f elf $< -o $@

bin/kernel.bin: bin/kernel.elf
	objcopy -O binary bin/kernel.elf bin/kernel.bin
	
bin/kernel.elf: $(KLINK) bin/kernel_entry.o ${OBJ}
	$(LD) -o $@ -T $^
# 	$(LD) -o $@ -Ttext 0x2000 $^

%.o: %.c ${HEADERS}
	$(CC) -o $@ -c $< $(INC_DIRS) $(CFLAGS)
	
kernel: src/kernel/kernel.c
	$(CC) -o bin/kernel.o -c src/kernel/kernel.c $(CFLAGS)
	
bin/pad: bin/kernel.bin #Padding kernel.bin to multiple of 512, because sectors in floppy are 512
	dd if=/dev/zero of=$@ bs=1 count=$(shell expr 512 - $(shell expr $(shell echo `ls -l $< | awk '{print $$5}'` % 512) % 512 ) )

mkbin:
	mkdir -p bin/

clean:
	rm -fr bin/ src/boot/*~ src/kernel/system/*~ src/kernel/drivers/*~ *~ kernel.dis src/boot/*.bin $(OBJ)
	
kernel.dis: mkbin bin/kernel.bin
	ndisasm -b 32 bin/kernel.bin > $@

