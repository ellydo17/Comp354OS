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

#project 3

#add the Disk Map and Disk Directory in sector 2
dd if=map.img of=floppya.img bs=512 count=1 seek=1 conv=notrunc
dd if=dir.img of=floppya.img bs=512 count=1 seek=2 conv=notrunc

#compile loadFile.c with gcc
gcc -o loadFile loadFile.c

#once loadFile has been compiled, it can be used to copy the contents of the message.txt file to your disk image with this command
./loadFile message.txt

#to assemble the lib.asm file
as86 lib.asm -o lib.o

#compile uprog1.c with bcc
bcc -ansi -c -o uprog1.o uprog1.c

#to link the uprog1.o and lib.o files into the executable kernel file
ld86 -o uprog1 -d uprog1.o lib.o

#loadFile is used to copy the contents of the uprog1 file to the disk image
./loadfile uprog1

#run bochs to allow the bootloader to load the kernel
bochs -f opsys.bxrc
