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
C_SOURCES = $(wildcard src/kernel/*.c)
HEADERS = $(wildcard src/kernel/*.h)
OBJ = ${C_SOURCES:.c=.o}

all: mkbin boot.img
	
run: all
	qemu-system-x86_64 -fda bin/boot.img
	
debug: all
	bochs -f bochsrc

boot.img: bin/boot0.bin bin/boot1.bin bin/kernel.bin bin/pad
	cat $^ > bin/boot.img

bin/boot0.bin: src/boot/boot0.asm
	nasm $< -f bin -I src/boot/ -o $@

bin/boot1.bin: src/boot/boot1.asm
	nasm $< -f bin -I src/boot/ -o $@
	
bin/kernel_entry.o: src/kernel/kernel_entry.asm
	nasm -f elf $< -o $@
	
# bin/kernel.bin: bin/kernel_entry.o ${OBJ}
# 	i586-elf-ld -o $@ -Ttext 0x2000 --oformat binary $^

bin/kernel.bin: bin/kernel.elf
	objcopy -O binary bin/kernel.elf bin/kernel.bin
	
bin/kernel.elf: bin/kernel_entry.o ${OBJ}
	i586-elf-ld -o $@ -Ttext 0x2000 $^

%.o: %.c ${HEADERS}
	i586-elf-gcc -o $@ -c $< -Isrc/kernel -Wall -Wextra -Werror -nostdlib -nostartfiles -nodefaultlibs
	
kernel: src/kernel/kernel.c
	i586-elf-gcc -o bin/kernel.o -c src/kernel/kernel.c -Wall -Wextra -Werror -nostdlib -nostartfiles -nodefaultlibs
	
bin/pad: bin/kernel.bin #Padding kernel.bin to multiple of 512, because sectors in floppy are 512
	dd if=/dev/zero of=$@ bs=1 count=$(shell expr 512 - $(shell expr $(shell echo `ls -l $< | awk '{print $$5}'` % 512) % 512 ) )

mkbin:
	mkdir -p bin/

clean:
	rm -fr bin/ src/boot/*~ src/kernel/*~ *~ kernel.dis src/boot/*.bin src/kernel/*.o
	
kernel.dis: mkbin bin/kernel.bin
	ndisasm -b 32 bin/kernel.bin > $@

