/*
*	README OF PROJECT MARVIN OS
*	Created by Nilton Vasques
*	Date 13 - 03 - 2013
*
*/

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