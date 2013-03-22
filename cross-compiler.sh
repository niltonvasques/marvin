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

#	Description: Script for setup an Cross Compiler to i586 machines
#	Author: Nilton Vasques, Caio Lima
#	Date: 21 - 03 - 2013
#
#!bin/bash

export PREFIX=/usr/local/cross
export TARGET=i586-elf
cd /usr/src
echo 'Creating directories for toolchain Naked GCC Cross Compiler'
mkdir build-binutils build-gcc
echo 'Downloading binutils'
wget http://ftp.gnu.org/gnu/binutils/binutils-2.22.tar.gz
echo 'Extracting  binutils'
tar -xvf binutils-2.22.tar.gz
cd /usr/src/build-binutils
../binutils-2.22/configure --target=$TARGET --prefix=$PREFIX --disable-nls
make all
make install

cd /usr/src/build-gcc
echo 'Downloading gcc-core'
wget http://ftp.gnu.org/gnu/gcc/gcc-4.6.3/gcc-core-4.6.3.tar.gz
echo 'Extracting gcc-core'
tar -xvf gcc-core-4.6.3.tar.gz

../gcc-4.6.3/configure --target=$TARGET --prefix=$PREFIX --disable-nls --enable-languages=c --without-headers
make all-gcc
make install-gcc
make all-target-libgcc
make install-target-libgcc
