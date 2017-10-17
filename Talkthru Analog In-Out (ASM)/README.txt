-------------------------------------------------------------------------------
Example: Talkthru Digital In-Analog Out (J8=Input, J5 and J6=Output)
Target:   ADSP-21364
Date:     Sept 8, 2004
Tools:    VisualDSP++ 3.5
Hardware: ADSP-21364 EZ-KIT LITE
-------------------------------------------------------------------------------

Multichannel talk-through (stereo in -> four stereo pairs out)

TalkThrough reads audio samples from the on-chip SPDIF receiver and it
passes the unmodified data through to the four DACs of the AD1835.
 Each interrupt reads a single 24-bit sample (alternating left and right) using
SPORT0 and immediately writes the same value to both the A and B data channels
of SPORT1 and SPORT2. All audio is transmitted in I2S mode.  An MCLK is derived
from the SPDIF input stream, as well as the bit clock and the frame sync. All are
driven to the Codec.

NOTE: In this TalkThrough code, the TDM Clock (256*fs, where fs is the sample rate) extracted by the on-chip SPDIF receiver is routed to the MCLK input of the AD1835 CODEC. The maximum MCLK that is supported by the AD1835 CODEC is 12.288MHz. Thus, the talk-through code will work as expected only for sample rates of upto 48KHz.

-------------------------------------------------------------------------------
Instructions: Download the executable to the EZ-KIT.  There are no user
controls or visual outputs.  The four stereo output pairs are identical.

All switches on SW7 should be OFF.
-------------------------------------------------------------------------------
Source Files contained in this directory:
21364_IVT.asm          Interrupt vector table code
ADSP-21364-EZKIT.ldf         Linker description file
ad1835.h               Header with constants for controlling the audio codec
main.asm               Calls initialization routines then waits for interrupts
init1835viaSPI.asm     Initializes the codec
initDAI.asm            Initializes the SRU & DAI pins
initPLL.asm            Configures the DSP to run at 331 MHz
initSPORT.asm          Initializes the transmit and receive serial ports
initSPDIF.asm          Initializes the SPDIF receiver
SPORTisr.asm           The interrupt service routine
Talkthru Digital In-Analog Out.dpj    VisualDSP Project File
-------------------------------------------------------------------------------
Dependencies contained in VisualDSP++ default include path:
def21364.h             Header with constants for the SHARC
SRU.h                  Macro to simplify programming the SRU & DAI pins
*******************************************************************************
Analog Devices, Inc.
DSP Division
One Technology Way
Norwood, MA 02062

(c) 2003 Analog Devices, Inc.  All rights reserved.
*******************************************************************************

