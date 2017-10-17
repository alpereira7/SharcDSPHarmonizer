/////////////////////////////////////////////////////////////
//                                                         //
//     SPORT1 and SPORT3 Interrupt Service Routines        //
//                                                         //
/////////////////////////////////////////////////////////////

#include <def21364.h>

.section /pm seg_pmco;
.global _talkThroughISR;

_talkThroughISR:


	r10=dm(RXSP0A);		// read new left sample from ADC
	
	dm(TXSP1A)=r10;			// write to DAC1
	dm(TXSP1B)=r10;			// write to DAC2
	dm(TXSP2A)=r10;			// write to DAC3
	dm(TXSP2B)=r10;			// write to DAC4
	
	rti;

_talkThroughISR.end:

//--------------------------------------------

