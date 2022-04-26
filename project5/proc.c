#include "proc.h"
#include "userlib.h"

/*
 * This function initializes all of the global variables and 
 * structures defined in proc.h file.
 */
void initializeProcStructures(){
  int i=0;
  //All entries in the memory map should be marked as FREE.
  for(i=0; i<8; i++){
    //memoryMap[i] = FREE;
    memoryMap[i] = FREE;
  }

  //All of the PCBs in the pcbPool should have the first character of their 
  //names set to null, their state set to DEFUNCT and their segment and stack
  //pointers set to 0x0000.
  for(i=0; i<8; i++){
    pcbPool[i].name[0] = NULL;
    pcbPool[i].state = DEFUNCT;
    pcbPool[i].segment = 0x0000;
    pcbPool[i].stackPointer = 0x0000;
  }

  //The PCB for the idle process should be initialized 
  //with the name IDLE, the state READY, and both the segment and stack pointers
  //set to 0x0000.
  idleProc.name[0] = 'I';
  idleProc.name[1] = 'D';
  idleProc.name[2] = 'L';
  idleProc.name[3] = 'E';
  idleProc.name[4] = '\0';
  idleProc.state = READY;
  idleProc.segment = 0x0000;
  idleProc.stackPointer = 0x0000;

  //running should refer to the PCB for the idle process
  running = &idleProc;

  //ready queue should be empty
  readyHead = NULL;
  readyTail = NULL;
}

/*
 * Returns the index of the first free memory segment or -1 if 
 * all of the memory segments are used.  The returned memory segment
 * should be marked as used.
 */
int getFreeMemorySegment(){
  int j=0;
  int foundMemory = -1;
  //printString("Running getFree... method\r\n\0");
  //printString("print this line\r\n\0");
  while(j<8 && foundMemory == -1){
    //printString("ONE\r\n\0");
    //if(memoryMap[j] == FREE){
    if(memoryMap[j] == FREE){
      foundMemory = j;
      //printString("Found the free memory\r\n\0");
    }
    j++;
  }
  memoryMap[foundMemory] = USED;
  if (foundMemory == -1) {
    printString("Error\0");
  }
  return foundMemory;
}

/*
 * Release the memory segment indicated by the given index into
 * the memory map.
 */
void releaseMemorySegment(int seg){
  int segIndex;
  segIndex = memorySegmentHelper(seg);
  memoryMap[segIndex] = FREE;
}

int memorySegmentHelper(int seg){
  if (seg == 0x2000) {
    return 0;
  } else if (seg == 0x3000) {
    return 1;
  }  else if (seg == 0x4000) {
    return 2;
  } else if (seg == 0x5000) {
    return 3;
  } else if (seg == 0x6000) {
    return 4;
  } else if (seg == 0x7000) {
    return 5;
  } else if (seg == 0x8000) {
    return 6;
  } else {
    return 7;
  }
}

/*
 * Return a pointer to an available PCB from the PCB pool.  All of the
 * available PCBs should be marked as DEFUNCT.  The returned PCB should
 * be marked as STARTING. Return NULL if there are no PCBs available.
 */
struct PCB *getFreePCB(){
  int j=0;
  int foundFreePCB = NULL;
  while(j<8 && foundFreePCB == NULL){
    if(pcbPool[j].state == DEFUNCT){
      foundFreePCB = j;
    }
    j++;
  }
  pcbPool[foundFreePCB].state = STARTING;

  if(foundFreePCB != NULL){
    return &pcbPool[foundFreePCB];
  }else{
    return NULL;
  }
}

/*
 * Release the provided PCB by setting its state to DEFUNCT, setting
 * its next and prev pointers to NULL and setting the first character
 * of its name to 0x00.
 */
void releasePCB(struct PCB *pcb){
  pcb->state = DEFUNCT;
  pcb->next = NULL;
  pcb->prev = NULL;
  pcb->name[0] = 0x00;
}

/*
 * Add the provided PCB to the tail of the ready queue.
 */
void addToReady(struct PCB *pcb){
  pcb->prev = readyTail;
  readyTail->next = pcb;
  readyTail = pcb;
  readyTail->next = NULL;
}

/*
 * Remove the PCB at the head of the ready queue and return a 
 * pointer to it.
 */
struct PCB *removeFromReady(){
  struct PCB *removedPCB;
  removedPCB = readyHead;
  readyHead = readyHead->next;
  readyHead->prev = NULL;
  return removedPCB;
}
