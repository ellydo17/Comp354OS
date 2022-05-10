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

void testFreeMemorySegment() {	
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

void testNoFreeMemorySegment() {	
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

void testReleaseMemorySegment() {	
	initializeProcStructures();

	int i=0;

	for (i=0; i<8; i++) {
		memoryMap[i] = USED;
	}
	releaseMemorySegment(0x3000); //0x3000 corresponds to 1
	printf("Released memory segment at 0x3000.\n");
	assert(memoryMap[1] == FREE);
}

void testGetFreePCB() {	
	initializeProcStructures();

	int i=0;
        struct PCB *freePCB;
	assert(pcbPool[0].state == 0);
	assert(pcbPool[1].state == 0);
	freePCB = getFreePCB();
	printf("The state of the free PCB is %d.\n", freePCB->state);
	printf("PCB at index 0 is %d.\n", pcbPool[0].state);
	assert(pcbPool[0].state == 0);
	assert(pcbPool[1].state == 4);
	assert(pcbPool[2].state == 0);
}

void testReleasePCB() {	
	initializeProcStructures();
	printf("Initialized proc structures.\n");
	
	struct PCB *dummypcb1;
	dummypcb1 = getFreePCB();

	struct PCB *dummypcb2;
	dummypcb2 = getFreePCB();
	struct PCB *dummypcb3;
	dummypcb3 = getFreePCB();
	
	dummypcb1->next = dummypcb2;
	dummypcb1->prev = dummypcb3;
	dummypcb1->name[0] = 'D';
	dummypcb1->name[1] = 'P';
	dummypcb1->name[2] = 'C';
	dummypcb1->name[3] = 'B';
	dummypcb1->name[4] = '1';
	dummypcb1->name[5] = '\0';
	printf("set name.\n");

	assert(dummypcb1->state == STARTING);
	assert(dummypcb1->next == dummypcb2);
	assert(dummypcb1->prev == dummypcb3);
	assert(strcmp(dummypcb1->name, "DPCB1\0") == 0);

	printf("Dummy pcb was initialized succesfully.\n");

	releasePCB(dummypcb1);

	printf("Dummy pcb was released.\n");
	
	assert(dummypcb1->state == DEFUNCT);
	assert(dummypcb1->next == NULL);
	assert(dummypcb1->prev == NULL);
	assert(dummypcb1->name[0] == '\0');
}


int main() {
  /*
  printf("Testing initializeProcStructures\n");
  testInit();
  printf("done\n");
  
  printf("Testing free memory segment.\n");
  testFreeMemorySegment();
  printf("done\n");
  printf("\n");
  
  printf("Testing no free memory segment.\n");
  testNoFreeMemorySegment();
  printf("done\n");
  printf("\n");

  printf("Testing release memory segment.\n");
  testReleaseMemorySegment();
  printf("done\n");
  printf("\n");
  */

  //doesn't work
  printf("Testing free PCB.\n");
  testGetFreePCB();
  printf("done\n");
  printf("\n");

  
  /*
  printf("Testing release PCB.\n");
  testReleasePCB();
  printf("done\n");
  printf("\n");
  */
}
