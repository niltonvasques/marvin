#!/bin/bash

echo 'Booting for floppy disk img: $1'
qemu-system-x86_64 -fda $1