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

QUEMU = "qemu-system-x86_64 -fda"

all: marvin.img

marvin.img: boot0.bin boot1.bin
	cat boot0.bin boot1.bin > boot.img

boot0.bin:
	nasm boot0.asm -f bin -o boot0.bin

boot1.bin:
	nasm boot1.asm -f bin -o boot1.bin

clean:
	rm -fr *~ *.bin *.img

run: all
	$QUEMU boot.img
