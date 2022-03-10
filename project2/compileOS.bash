#!/bin/bash

source ../PathSetter.bash

#complie the c file
bcc -ansi -c -o kernel.o kernel.c

#to assemble the kernel.asm file
as86 kernel.asm -o kernel_asm.o

#to link the kernel.o and kernel_asm.o files into the executable kernel file
ld86 -o kernel -d kernel.o kernel_asm.o

#to copy the kernel file to sector 3
dd if=kernel of=floppya.img bs=512 conv=notrunc seek=3

#use the dd command to place the provided message.txt file into the sector 30 of the disk
dd if=message.txt of=floppya.img bs=512 count=1 conv=notrunc seek=30

#run bochs to allow the bootloader to load the kernel
bochs -f opsys.bxrc
