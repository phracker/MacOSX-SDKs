/*
     File:       PMPrinterModule.h
 
     Contains:   Mac OS X Printing Manager Printer Module Interfaces.
 
     Version:    Technology: Mac OS X
                 Release:    1.0
 
     Copyright:  © 1998-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
	History:

*/
#ifndef __PMPRINTERMODULE__
#define __PMPRINTERMODULE__

#include <CoreFoundation/CFString.h>
#include <PrintCore/PMPrinterModuleDeprecated.h>

#ifdef __cplusplus
extern "C" {
#endif

// Paper names must all be ISO or PPD standard names, so we've defined constants here for 
// developers to use in their code, mostly to make things more readable.

#define USExecutiveEnvelope		CFSTR( "Executive" )
#define Envelope9				CFSTR( "na-number-9-envelope" )
#define Envelope10				CFSTR( "na-number-10-envelope" )
#define Envelope10x15			CFSTR( "na-10x15-envelope" )
#define EnvelopeB4				CFSTR( "iso-b4-envelope" )
#define EnvelopeB5				CFSTR( "iso-b5-envelope" )
#define EnvelopeC3				CFSTR( "iso-c3-envelope" )
#define EnvelopeC4				CFSTR( "iso-c4-envelope" )
#define EnvelopeC5				CFSTR( "iso-c5-envelope" )
#define EnvelopeC6				CFSTR( "iso-c6-envelope" )
#define Envelope6x9				CFSTR( "na-6x9-envelope" )
#define Envelope7x9				CFSTR( "na-7x9-envelope" )
#define Envelope9x11			CFSTR( "na-9x11-envelope" )
#define Envelope9x12			CFSTR( "na-9x12-envelope" )
#define Envelope10x13			CFSTR( "na-10x13-envelope" )
#define Envelope10x14			CFSTR( "na-10x14-envelope" )
#define EnvelopeMonarch			CFSTR( "monarch-envelope" )
#define EnvelopeLong			CFSTR( "iso-designated-long-envelope" )

#define Invoice					CFSTR( "invoice" )
#define USLetter				CFSTR( "na-letter" )
#define USLegal					CFSTR( "na-legal" ) 
#define Tabloid					CFSTR( "tabloid" )
#define Ledger					CFSTR( "ledger" )
#define Folio					CFSTR( "folio" )
#define Quarto					CFSTR( "quarto" )

#define A0						CFSTR( "iso-a0" )
#define A1						CFSTR( "iso-a1" )
#define A2						CFSTR( "iso-a2" )
#define A3						CFSTR( "iso-a3" )
#define A4						CFSTR( "iso-a4" )
#define A5						CFSTR( "iso-a5" )
#define A6						CFSTR( "iso-a6" )
#define A7						CFSTR( "iso-a7" )
#define A8						CFSTR( "iso-a8" )
#define A9						CFSTR( "iso-a9" )

#define B0						CFSTR( "iso-b0" )
#define B1						CFSTR( "iso-b1" )
#define B2						CFSTR( "iso-b2" )
#define B3						CFSTR( "iso-b3" )
#define B4						CFSTR( "iso-b4" )
#define B5						CFSTR( "iso-b5" )
#define B6						CFSTR( "iso-b6" )
#define B7						CFSTR( "iso-b7" )
#define B8						CFSTR( "iso-b8" )
#define B9						CFSTR( "iso-b9" )
#define B10						CFSTR( "iso-b10" )

#define JISB0					CFSTR( "jis-b0" )
#define JISB1					CFSTR( "jis-b1" )
#define JISB2					CFSTR( "jis-b2" )
#define JISB3					CFSTR( "jis-b3" )
#define JISB4					CFSTR( "jis-b4" )
#define JISB5					CFSTR( "jis-b5" )
#define JISB7					CFSTR( "jis-b7" )
#define JISB8					CFSTR( "jis-b8" )
#define JISB9					CFSTR( "jis-b9" )
#define JISB10					CFSTR( "jis-b10" )

#define ASize					CFSTR( "a" )
#define BSize					CFSTR( "b" )
#define CSize					CFSTR( "c" )
#define DSize					CFSTR( "d" )
#define ESize					CFSTR( "e" )

#define iso10					CFSTR( "iso-10" )

// A string to define the default paper name. See sample code for usage.

#define DefaultPaper			CFSTR( "DefaultPaperSize" )

#ifdef __cplusplus
}
#endif

#endif /* __PMPRINTERMODULE__ */

