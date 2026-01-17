/*
 * Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * "Portions Copyright (c) 1999 Apple Computer, Inc.  All Rights
 * Reserved.  This file contains Original Code and/or Modifications of
 * Original Code as defined in and that are subject to the Apple Public
 * Source License Version 1.0 (the 'License').  You may not use this file
 * except in compliance with the License.  Please obtain a copy of the
 * License at http://www.apple.com/publicsource and read it before using
 * this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License."
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/* Copyright (c) 1992 NeXT Computer, Inc.  All rights reserved.
 *
 *	Zilog Z85C30 Serial Controller Chip definitions
 *
 * The 85C30 contains the following registers:
 * Read Register:	Function:
 * 	RR0		Transmit/Receive buffer and external status
 * 	RR1		Special receive condition status
 * 	RR2		Interrupt vector.
 * 	RR3		Interrupt pending bits.
 * 	RR8		Receive buffer.
 * 	RR10		Miscellaneous status
 * 	RR12		Lower byte of baud rate generator time constant
 * 	RR13		Upper byte of baud rate generator time constant
 * 	RR15		External/Status interrupt information
 *
 * Write register:	Function:
 *	WR0		Initialization commands.
 *	WR1		Transmit/Receive interrupt and data transfer mode
 *	WR2		Interrupt vector
 *	WR3		Receive parameters and control
 *	WR4		Transmit/Receive miscellaneous parameters and modes
 *	WR5		Transmit parameters and controls
 *	WR6		Sync characters or SDLC address field
 *	WR7		Sync character or SDLC flag
 *	WR8		Transmit buffer
 *	WR9		Master interrupt control and reset
 *	WR10		Miscellaneous transmitter/receiver control bits
 *	WR11		Clock mode control
 *	WR12		Lower byte of baud rate generator time constant
 *	WR13		Upper byte of baud rate generator time constant
 *	WR14		Miscellaneous control bits
 *	WR15		External/Status interrupt control
 */

/* Read register 0 */
#define RR0_RXAVAIL	0x01		/* Rx Character Available */
#define RR0_ZERO_COUNT	0x02		/* Zero count (timer) */
#define RR0_TXEMPTY	0x04		/* Tx Buffer Empty */
#define RR0_DCD		0x08		/* DCD status */
#define RR0_SYNC_HUNT	0x10		/* Sync hunt mode */

/*
 * NOTE: the sense of CTS is dependent on the cpu board rev
 */
#define RR0_CTS		0x20		/* CTS status */

#define RR0_TXUNDER	0x40		/* Tx Underrun/EOM */
#define RR0_BREAK	0x80		/* Break/Abort */

/* Read register 1 */
#define RR1_ALLSENT	0x01		/* All Sent */
#define RR1_RESCODE2	0x02		/* Residue Code 2 */
#define RR1_RESCODE1	0x04		/* Residue Code 1 */
#define RR1_RESCODE0	0x08		/* Residue Code 0 */
#define RR1_PARITY	0x10		/* Parity Error */
#define RR1_RXOVER	0x20		/* Rx Overrun Error */
#define RR1_FRAME	0x40		/* CRC/Framing Error */
#define RR1_EOF		0x80		/* End of Frame (SDLC) */

/*
 * Read/Write Register 2: 8 bits of interrupt vector
 * Channel A unmodified, channel B is modified by current UART status
 */

/* Read register 3 -- ONLY CHANNEL A */
#define RR3_B_STATIP	0x01		/* Chanel B Ext/Status intr pending */
#define RR3_B_TXIP	0x02		/* Chanel B Tx interrupt pending */
#define RR3_B_RXIP	0x04		/* Chanel B Rx interrupt pending */
#define RR3_A_STATIP	0x08		/* Chanel A Ext/Status intr pending */
#define RR3_A_TXIP	0x10		/* Chanel A Tx interrupt pending */
#define RR3_A_RXIP	0x20		/* Chanel A Rx interrupt pending */

#define	RR3_A_IP	(RR3_A_STATIP|RR3_A_TXIP|RR3_A_RXIP)
#define	RR3_B_IP	(RR3_B_STATIP|RR3_B_TXIP|RR3_B_RXIP)

/*
 * Read Register 8: same as data port (receive buffer)
 */

/* Read Register 10 */
#define RR10_ONLOOP	0x02		/* On Loop */
#define RR10_LOOPSEND	0x10		/* Loop Sending */
#define RR10_MISS2	0x40		/* Two Clocks Missing */
#define RR10_MISS1	0x80		/* One Clock Missing */

/*
 * Read/Write Register 12/13 16 bits of time constant
 */

/* Read/Write Register 15 */
#define RW15_ZEROCNTIE	0x02		/* Enable interrupt on timer zero */
#define RW15_DCDIE	0x08		/* Enable interrupt on DCD change */
#define RW15_SYNCIE	0x10		/* Enable interrupt on Sync Hunt */
#define RW15_CTSIE	0x20		/* Enable interrupt on CTS change */
#define RW15_TXUNDERIE	0x40		/* Enable interrupt on TxUnderrun/EOM*/
#define RW15_BREAKIE	0x80		/* Enable interrupt on Break/Abort */

/* Write register 0 */
#define WR0_REGMASK	0x0F		/* Mask for register select */
#define WR0_RESET_STAT	0x10		/* Reset Ext/Status Interrupts */
#define WR0_ABORT	0x18		/* Send abort */
#define WR0_NEXTRXIE	0x20		/* Enable interrupt on next char Rx */
#define WR0_RESETTXPEND	0x28		/* Reset Pending Tx Interrupt */
#define WR0_RESET	0x30		/* Error Reset */
#define WR0_RESETIUS	0x38		/* Reset Interrupt Under Service */
#define WR0_RESETRXCRC	0x40		/* Reset Rx CRC Checker */
#define WR0_RESETTXCRC	0x80		/* Reset Rx CRC Generator */
#define WR0_RESETEOM	0xC0		/* Reset Underrun/EOM latch */

/* Write register 1 */
#define WR1_EXTIE	0x01		/* External Interrupt Enable */
#define WR1_TXIE	0x02		/* Transmit Interrupt Enable */
#define WR1_PARSPEC	0x04		/* Parity is Special Condition */
#define WR1_RXFIRSTIE	0x08		/* Interrupt Enable on First Rx */
#define WR1_RXALLIE	0x10		/* Interrupt Enable on ALL Rx */
#define WR1_SPECIE	0x18		/* Interrupt on Special only */
#define WR1_REQRX	0x20		/* Request on Rx (else Tx) */
#define WR1_REQFUNC	0x40		/* DMA Request (else cpu wait) */
#define WR1_REQENABLE	0x80		/* Request/Wait enable */

/* Read/Write register 2, interrupt vector */

/* Write register 3 */
#define WR3_RXENABLE	0x01		/* Rx Enable */
#define WR3_SYNCINHIB	0x02		/* Sync Character Load Inhibit */
#define WR3_ADDRSRCH	0x04		/* Address search mode (SDLC) */
#define WR3_RXCRCENABLE	0x08		/* Rx CRC enable */
#define WR3_ENTERHUNT	0x10		/* Enter Hunt Mode */
#define WR3_AUTOENABLES	0x20		/* Auto Enables */
#define WR3_RX5		0x00		/* Rx 5 bit characters */
#define WR3_RX7		0x40		/* Rx 7 bit characters */
#define WR3_RX6		0x80		/* Rx 6 bit characters */
#define WR3_RX8		0xC0		/* Rx 8 bit characters */

/* Write register 4 */
#define WR4_PARENABLE	0x01		/* Parity enable */
#define WR4_PAREVEN	0x02		/* Even parity */
#define WR4_STOP1	0x04		/* 1 stop bit */
#define WR4_STOP15	0x08		/* 1.5 stop bits */
#define WR4_STOP2	0x0C		/* 2 stop bits */
#define WR4_SYNC8	0x00		/* 8 bit sync character */
#define WR4_SYNC16	0x10		/* 16 bit sync character */
#define WR4_SDLC	0x10		/* SDLC mode */
#define WR4_EXTSYNC	0x30		/* External sync */
#define WR4_X1CLOCK	0x00		/* x1 clock mode */
#define WR4_X16CLOCK	0x40		/* x16 clock mode */
#define WR4_X32CLOCK	0x80		/* x32 clock mode */
#define WR4_X64CLOCK	0xC0		/* x64 clock mode */

/* Write register 5 */
#define WR5_TXCRCENABLE	0x01		/* Enable CRC on Rx */
#define WR5_RTS		0x02		/* RTS */
#define WR5_CRC16	0x04		/* SDLC/CRC-16 */
#define WR5_TXENABLE	0x08		/* Enable transmitter */
#define WR5_BREAK	0x10		/* Send a break */
#define WR5_TX5		0x00		/* Tx 5 bit characters */
#define WR5_TX7		0x20		/* Tx 7 bit characters */
#define WR5_TX6		0x40		/* Tx 6 bit characters */
#define WR5_TX8		0x60		/* Tx 8 bit characters */
#define WR5_DTR		0x80		/* DTR */

/* Write register 6 (Sync characters or SDLC address) */

/* Write register 7 more sync/SDLC */

/* Write register 8, same as data port, (Tx buffer) */

/* Write register 9 -- ONLY 1, SHARED BETWEEN CHANNELS, ACCESSABLE FROM BOTH */
#define WR9_VIS		0x01		/* Vector Includes Status */
#define WR9_NV		0x02		/* No Vector (don't respond to IACK) */
#define WR9_DLC		0x04		/* Disable Lower Chain */
#define WR9_MIE		0x08		/* Master Interrupt Enable */
#define WR9_STATHIGH	0x10		/* Status high */
#define WR9_RESETB	0x40		/* Reset channel B */
#define WR9_RESETA	0x80		/* Reset channel A */
#define WR9_RESETHARD	0xC0		/* Hardware reset */

/* Write register 10 */
#define WR10_SYNC6	0x01		/* 6 bit sync */
#define WR10_LOOP	0x02		/* Loop mode */
#define WR10_ABORTUNDER	0x04		/* Abort on Underrun */
#define WR10_MARKIDLE	0x08		/* Mark Idle */
#define WR10_POLLACT	0x10		/* Go active on poll */
#define WR10_NRZ	0x00		/* NRZ */
#define WR10_NRZI	0x20		/* NRZI */
#define WR10_FM1	0x40		/* FM (Transition = 1) */
#define WR10_FM0	0x60		/* FM (Transition = 0) */
#define WR10_PRESET1	0x80		/* CRC Preset 1 */

/* Write register 11 */
#define WR11_XTAL	0x00		/* TRxC Out = XTAL Output */
#define WR11_TXCLOCK	0x01		/* TRxC Out = Transmit clock */
#define WR11_BRGEN	0x02		/* TRxC Out = BR Generator Output */
#define WR11_DPLL	0x03		/* TRxC Out = DPLL Output */
#define WR11_TRXCOUTEN	0x04		/* Enable TRxC as output */
#define WR11_TXCLKRTXC	0x00		/* Tx clock = RTxC pin */
#define WR11_TXCLKTRXC	0x08		/* Tx clock = TRxC pin */
#define WR11_TXCLKBRGEN	0x10		/* Tx clock = BR Generator Output */
#define WR11_TXCLKDPLL	0x18		/* Tx clock = DPLL Output */
#define WR11_RXCLKRTXC	0x00		/* Rx clock = RTxC pin */
#define WR11_RXCLKTRXC	0x20		/* Rx clock = TRxC pin */
#define WR11_RXCLKBRGEN	0x40		/* Rx clock = BR Generator Output */
#define WR11_RXCLKDPLL	0x60		/* Rx clock = DPLL Output */
#define WR11_RTXCXTAL	0x80		/* Crystal RTxC in (else TTL) */

/* Read/Write register 12/13 Time constant */

/* Write register 14 */
#define WR14_BRENABLE	0x01		/* BR Generator Enable */
#define WR14_BRPCLK	0x02		/* BR Generator CLK from PCLK */
#define WR14_DTRREQ	0x04		/* DTR low is DMA request */
#define WR14_AUTOECHO	0x08		/* Auto echo */
#define WR14_LOOPBACK	0x10		/* Local loopback */
#define WR14_SEARCH	0x20		/* Enter Search mode */
#define WR14_RESET	0x40		/* Reset Missing Clock */
#define WR14_DPLLDISABLE 0x60		/* Disable DPLL */
#define WR14_SRCBR	0x80		/* Set DPLL CLK Src = BR Generator */
#define WR14_SRCRTXC	0xA0		/* Set DPLL CLK Src = RTxC */
#define WR14_FM		0xC0		/* Set FM mode */
#define WR14_NRZI	0xE0		/* Set NRZI mode */

