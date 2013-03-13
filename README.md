This file is part of Marvin OS project.
   
Marvin OS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Marvin OS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Marvin OS.  If not, see <http://www.gnu.org/licenses/>.

*	Description: Readme 
*	Created by Nilton Vasques
*	Email: niltonvasues@gmail.com
*	Date 13 - 03 - 2013
========================================================
README OF PROJECT MARVIN OS
========================================================


========================================================
HISTORY
========================================================
 We named project like Marvin because I found in many places
 talking that OS development is very sadness, hardness,
 terrible task in Computer Science hehe. 
 However, this can be the most fun and interactive job.
 So Marvin is a reference of sadness robot in Book's Series
 the hitchhiker's guide to the galaxy writed by Douglas Adams.

========================================================
INSTRUCTIONS FOR CREATE IMAGE OF BOOTLOADER
========================================================
==> Creating an image of a disket file empty 
mkdosfs -C meuos.flp 1440

==> Write bootloader.bin in disket image (FLP)
dd status=noxfer conv=notrunc if=meuos.bin of=meuos.flp

==> Testing if all are ok and works fine
qemu meuos.flp OR some cases use qemu-system-x86_64 meuos.flp

==> Create a ISO image of OS
mkiso -V 'meuos' -input-charset iso8859-1 -o disco/meuos.iso -b meuos.flp disco/

==> With ISO image you can load in VirtualBox and boot from ISO Image for testing the system
