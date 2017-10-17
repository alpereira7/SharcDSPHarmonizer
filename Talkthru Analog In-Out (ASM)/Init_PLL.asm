/********************************************************************************************
**
**  File:   Init_PLL.asm
**  Date:   7-27-05
**  Author: BM
**  Use:    Initialize the DSP PLL for the required CCLK rate
**  Note:
**      CLKIN will be 24.576MHz from an external oscillator.  The PLL is programmed
**      to generate a core clock (CCLK) of 331.7MHz - PLL multiplier = 0x001B and
**      divider = 0x02.
**
**      Updated code to not set Bypass and enable the divisor in the same cycle.
**
**
*********************************************************************************************/

#include <def21364.h>
.section/pm     seg_pmco;

.global Init_PLL;

/********************************************************************************************/
Init_PLL:

plldiv:
//Divide by 2

pllmult:
     //24.576 MHz CLKIN
     //(24.576MHz * 27) /2 = 331.776 MHz

ustat1=dm(PMCTL);
bit clr ustat1 0xc0;    // Clear any old divisor
bit set ustat1 DIVEN|PLLD2; //Set and enable new divisor
bit clr ustat1 INDIV | 0x3f;    //Clear old multiplier
bit set ustat1 PLLM27; //Set new multiplier
dm(PMCTL)=ustat1;

bit set ustat1 PLLBP; // put PLL in bypass so it can lock at the new multiplier
dm(PMCTL)=ustat1;

lcntr=0xffff, do pllwait until lce; //wait for PLL to lock at new rate
pllwait: nop;
nop;
ustat1=dm(PMCTL);
bit clr ustat1 PLLBP;       //out of bypass
bit set ustat1 CLKOUTEN;    //and start clkout
dm(PMCTL)=ustat1;

Init_PLL.end:    rts;

/*********************************************** EOF ****************************************/
