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
	printf("free memory segment is %d\n", segment);
	assert(segment == 5);
}

int main() {
  /*
	printf("Testing initializeProcStructures\n");
	testInit();
	printf("done\n");
  */
  printf("Testing free memory segment\n");
	testFreeMemorySegmentTrue();
	printf("done\n");
}
