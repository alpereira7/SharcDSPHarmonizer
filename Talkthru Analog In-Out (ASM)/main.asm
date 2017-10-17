//-----------------------------------------
//   main.asm
//-----------------------------------------
//
//   21364 EZ-KIT Test
//
//-----------------------------------------

#include <def21364.h>

.section /pm seg_pmco;

.global _main;
.extern _initDAI;
.extern _init1835viaSPI;
.extern _initSPORT;
.extern Init_PLL;


_main:
    call Init_PLL;          // Initialize PLL for the correct core clock (CCLK) frequency
	
    call _initDAI;

    call _init1835viaSPI;
    
    call _initSPORT;


	//----------------------------------------------
	// Enable interrupts (globally)
	BIT SET MODE1 IRPTEN;

	//----------------------------------------------
	// Unmask the SPORT0 ISR
	LIRPTL = SP0IMSK;
	
	//----------------------------------------------
	// Loop forever.  Work is driven by interrupts
	jump (pc,0);

_main.end:




