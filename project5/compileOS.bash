#!/bin/bash

source ../PathSetter.bash
#############
# assemble to install the bootloader
nasm bootload.asm

#copy the boatload program to sector 0 of the floppya.img disk image
dd if=bootload of=floppya.img bs=512 count=1 conv=notrunc seek=0
##############

#complie the c file
bcc -ansi -c -o kernel.o kernel.c

#to assemble the kernel.asm file
as86 kernel.asm -o kernel_asm.o

#to link the kernel.o and kernel_asm.o files into the executable kernel file
#ld86 -o kernel -d kernel.o kernel_asm.o

#to copy the kernel file to sector 3
dd if=kernel of=floppya.img bs=512 conv=notrunc seek=3

#use the dd command to place the provided message.txt file into the sector 30 of the disk
dd if=message.txt of=floppya.img bs=512 count=1 conv=notrunc seek=30

#add the Disk Map and Disk Directory in sector 2
dd if=map.img of=floppya.img bs=512 count=1 seek=1 conv=notrunc
dd if=dir.img of=floppya.img bs=512 count=1 seek=2 conv=notrunc

#compile loadFile.c with gcc
gcc -o loadFile loadFile.c

#once loadFile has been compiled, it can be used to copy the contents of the message.txt, happy.txt file to your disk image with this command
./loadFile message.txt
./loadFile happy1.txt #for testing writeFile from project 4
./loadFile apple.txt #for testing writeFile from project 4

#Similarly, copy the contents of the fileToDelete.txt file to your disk image with this command
./loadFile delete.txt

#Loading and Executing a User Program

#assemble the lib.asm file
as86 lib.asm -o lib.o

#compile userlib.c with bcc
bcc -ansi -c -o userlib.o userlib.c

#compile uprog1.c with bcc, link the uprog1.o and lib.o files into the executable kernel file,
#and use loadFile to copy the contents of the uprog1 file to the disk image
bcc -ansi -c -o uprog1.o uprog1.c
ld86 -o uprog1 -d uprog1.o lib.o
./loadfile uprog1

#Terminating a User Program

#compile uprog2.c with bcc, link the uprog2.o and lib.o files into the executable kernel file,
#and use loadFile to copy the contents of the uprog2 file to the disk image
bcc -ansi -c -o uprog2.o uprog2.c
ld86 -o uprog2 -d uprog2.o lib.o
./loadfile uprog2

#compile textEditor.c with bcc, link the textEditor.o and lib.o files into the executable kernel file,
#and use loadFile to copy the contents of the textEditor file to the disk image
bcc -ansi -c -o textEditor.o textEditor.c
ld86 -o textEditor -d textEditor.o userlib.o lib.o
./loadfile textEditor

#compile hello.c, world.c with bcc, link the hello.o, world.c and lib.o files into the executable kernel file,
#and use loadFile to copy the contents of the hello and world file to the disk image
bcc -ansi -c -o hello.o hello.c
bcc -ansi -c -o world.o world.c
ld86 -o hello -d hello.o userlib.o lib.o
ld86 -o world -d world.o userlib.o lib.o
./loadfile hello
./loadfile world

#Command line shell, Improvements - creating a user library

#compile shell.c with bcc, link the shell.o and lib.o files into the executable kernel file,
#and use loadfile to copy the contents of the shell file to the disk image
bcc -ansi -c -o shell.o shell.c
ld86 -o shell -d shell.o userlib.o lib.o
./loadfile shell

#compile proc.c with bcc, link the proc.o and lib.o files into the executable kernel file,
#and use loadfile to copy the contents of the proc file to the disk image
bcc -ansi -c -o proc.o proc.c
ld86 -o kernel -d kernel.o proc.o kernel_asm.o
./loadfile proc

#run bochs to allow the bootloader to load the kernel
bochs -f opsys.bxrc
