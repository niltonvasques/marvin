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
#	Date: 20 - 03 - 2013

all: boot.img

boot.img: boot0.bin boot1.bin
	cat bin/boot0.bin bin/boot1.bin > bin/boot.img

boot0.bin: mkbin
	nasm src/boot/boot0.asm -f bin -I src/boot/ -o bin/boot0.bin

boot1.bin: mkbin
	nasm src/boot/boot1.asm -f bin -I src/boot/ -o bin/boot1.bin

mkbin:
	mkdir bin/

clean:
	rm -fr bin/

run-deb:
	qemu -fda bin/boot.img

run-ubt:
	qemu-system-x86_64 -fda bin/boot.img