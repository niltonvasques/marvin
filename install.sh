#!/bin/bash

echo 'Compiling boot0.asm...'
nasm src/boot0.asm -f bin -o bin/boot0.bin -I src
echo 'Compiling boot1.asm...'
nasm -f bin src/boot1.asm -I src/ -o bin/boot1.bin
echo 'Create floppy image marvin.img...'
cat bin/boot0.bin bin/boot1.bin > bin/marvin.img
./run.sh bin/marvin.img
