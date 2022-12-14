/*--------------------------------------------------------------------*/
/* miniassembler.c                                                    */
/* Author: Bob Dondero, Donna Gabai                                   */
/*--------------------------------------------------------------------*/

#include "miniassembler.h"
#include <assert.h>
#include <stddef.h>

/*--------------------------------------------------------------------*/
/* Modify *puiDest in place,
   setting uiNumBits starting at uiDestStartBit (where 0 indicates
   the least significant bit) with bits taken from uiSrc,
   starting at uiSrcStartBit.
   uiSrcStartBit indicates the rightmost bit in the field.
   setField sets the appropriate bits in *puiDest to 1.
   setField never unsets any bits in *puiDest.                        */
static void setField(unsigned int uiSrc, unsigned int uiSrcStartBit,
                     unsigned int *puiDest, unsigned int uiDestStartBit,
                     unsigned int uiNumBits)
{
   /* Your code here */
   /* the amount of bits needed to be shifted to obtain wanted bits from uiSrc*/
   unsigned int uiShiftAmount;
   uiShiftAmount = 32 - uiNumBits;
   /*get rid of all bits that are right of uiSrcStartBit*/
   uiSrc = uiSrc >> uiSrcStartBit;
   /*obtain only the wanted bits taken from uiSrc */
   uiSrc = uiSrc << uiShiftAmount;
   uiSrc = uiSrc >> uiShiftAmount;
   /*move uiSrc such that it aligns with puiDest starting at uiDestStartBit*/
   uiSrc = uiSrc << uiDestStartBit;
   /*set uiNumBits starting at uiDestStartBit with uiSrc*/
   *puiDest = uiSrc | *puiDest;

}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_mov(unsigned int uiReg, int iImmed)
{
   /* Your code here */

   unsigned int uiInstr;

   uiInstr = 0x00000000;

   /* add register */
   setField(uiReg, 0, &uiInstr, 0, 5);

   /* change bits from 30 to 21 to 10 100101 00 */
   setField(660, 0, &uiInstr, 21, 10);

   /* change bits from 20 to 5 to iImmed*/
   setField(iImmed, 0, &uiInstr, 5, 16);

   return uiInstr;

}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_adr(unsigned int uiReg, unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr;
   unsigned int uiDisp;

   /* Base Instruction Code */
   uiInstr = 0x10000000;

   /* register to be inserted in instruction */
   setField(uiReg, 0, &uiInstr, 0, 5);

   /* displacement to be split into immlo and immhi and inserted */
   uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr);

   setField(uiDisp, 0, &uiInstr, 29, 2);
   setField(uiDisp, 2, &uiInstr, 5, 19);

   return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_strb(unsigned int uiFromReg,
   unsigned int uiToReg)
{
   /* Your code here */

   unsigned int uiInstr;

   uiInstr = 0x39000000;

   /* add uiFromReg */
   setField(uiFromReg, 0, &uiInstr, 0, 5);

   /* add uiToReg */
   setField(uiToReg, 0, &uiInstr, 5, 5);


   return uiInstr;


}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_b(unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   /* Your code here */

   unsigned int uiInstr;
   unsigned int uiDisp;

   uiInstr = 0x00000000;

   /* change bits from 28 to 26 to 101 */
   setField(5, 0, &uiInstr, 26, 3);

   uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr);

   setField(uiDisp, 2, &uiInstr, 0, 26);

   return uiInstr;
}
