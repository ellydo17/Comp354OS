/*
 *  testproc.c
 
 */

#define MAIN

#include "stdio.h"
#include "assert.h"
#include <string.h>
#include "proc.h"

void testInit() {	
	initializeProcStructures();
	
	assert(running == &idleProc);
	assert(readyHead == NULL);
	assert(readyTail == NULL);
	int i=0;
	for (i=0; i<8; i++) {
		assert(memoryMap[i] == FREE);
		assert(pcbPool[i].name[0] == 0x00);
		assert(pcbPool[i].state == DEFUNCT);
		assert(pcbPool[i].segment == 0x00);
		assert(pcbPool[i].stackPointer == 0x00);
	}
	
	assert(strcmp(idleProc.name, "IDLE\0") == 0);
	assert(idleProc.segment == 0x0000);
	assert(idleProc.stackPointer == 0x0000); 
}

void testFreeMemorySegmentTrue() {	
	initializeProcStructures();

	int i=0;
	int segment = -1;
	for (i=0; i<5; i++) {
		memoryMap[i] = USED;
	}
	memoryMap[i] = FREE;
	for (i=6; i<8; i++) {
		memoryMap[i] = USED;
	}
	segment = getFreeMemorySegment();
	printf("The free memory segment is %d.\n", segment);
	assert(segment == 5);
}

void testFreeMemorySegmentFalse() {	
	initializeProcStructures();

	int i=0;
	int segment = -1;
	for (i=0; i<8; i++) {
		memoryMap[i] = USED;
	}
	segment = getFreeMemorySegment();
	printf("No free memory segments. Therefore, value of segment is %d\n", segment);
	assert(segment == -1);
}

void testReleaseMemorySegmentTrue() {	
	initializeProcStructures();

	int i=0;

	for (i=0; i<8; i++) {
		memoryMap[i] = USED;
	}
	releaseMemorySegment(0x3000); //0x3000 corresponds to 1
	printf("Released memory segment at 0x3000.\n");
	assert(memoryMap[1] == FREE);
}

void testGetFreePCBTrue() {	
	initializeProcStructures();

	int i=0;
        struct PCB *freePCB;
	assert(pcbPool[0].state == 0);
	assert(pcbPool[1].state == 0);
	freePCB = getFreePCB();
	printf("The state of the free PCB is %d.\n", freePCB->state);
	printf("PCB at index 0 is %d.\n", pcbPool[0].state);
	assert(pcbPool[1].state == 4);
	assert(pcbPool[2].state == 0);
}

int main() {
  /*
	printf("Testing initializeProcStructures\n");
	testInit();
	printf("done\n");
  */
  printf("Testing free memory segment True\n");
  testFreeMemorySegmentTrue();
  printf("done\n");
  
  printf("Testing free memory segment False\n");
  testFreeMemorySegmentFalse();
  printf("done\n");

  //doesn't work
  printf("Testing free PCB True\n");
  testGetFreePCBTrue();
  printf("done\n");
}
