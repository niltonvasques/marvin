#!/bin/bash

echo 'Compiling boot0.asm...'
nasm boot0.asm -f bin -o boot0.bin
echo 'Compiling boot1.asm...'
nasm boot1.asm -f bin -o boot1.bin
echo 'Create floppy image marvin.img...'
cat boot0.bin boot1.bin > marvin.img
./run.sh marvin.img
