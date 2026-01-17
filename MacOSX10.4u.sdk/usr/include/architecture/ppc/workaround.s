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
/*
 *  Copyright 1997 Apple Computer, Inc. (unpublished)
 *
 *	architecture/ppc/workaround.s
 *
 *	Contains macros for POWER instructions which are not supported
 *	on 604.
 *  r21 used as mq.
 *
 *  Umesh Vaishampayan, umeshv@NeXT.com
 *		Feb. 1997	Created.
 */
 
 /* -----------------------------------------------
  * --  Woraround macros for 601 instructions    --
  * ----------------------------------------------- */

.no_ppc601
.flag_reg 21
.flag_reg 22

 
/*
 * nabs
 * f(int i) { return -(i >= 0 ? i : -i); }
 */

.macro nabs
	srawi r0,$0,31
	xor $0,r0,$0
	subf $0,$0,r0
.endmacro

/*
 * abs
 * b(int i) { return (i >= 0 ? i : -i); }
 */

.macro abs
	srawi r0,$0,31
	xor $0,r0,$0
	subf $0,r0,$0
.endmacro

/*
 * mtspr and mfspr  to take care of mq
 */

# Define all the SPRs here.
.set mq, 0
# mq is provided by 601 for POWER compatibility
.set xer, 1
.set lr, 8
.set ctr, 9
.set dsisr, 18
.set dar, 19
.set dec, 22
.set sdr1, 25
.set srr0, 26
.set srr1, 27
.set sprg0, 272
.set sprg1, 273
.set sprg2, 274
.set sprg3, 275
.set asr, 280
.set ear, 282
.set pvr, 287
.set ibat0u, 528
.set ibat1u, 530
.set ibat2u, 532
.set ibat3u, 534
.set ibat0l, 529
.set ibat1l, 531
.set ibat2l, 533
.set ibat3l, 535
.set dbat0u, 536
.set dbat1u, 538
.set dbat2u, 540
.set dbat3u, 542
.set dbat0l, 537
.set dbat1l, 539
.set dbat2l, 541
.set dbat3l, 543

.macro mtspr
.if $0==0
.noflag_reg 21
	mr r21, $1
.flag_reg 21
.else
.macros_off
	mtspr $0, $1
.macros_on
.endif
.endmacro

.macro mfspr
.if $1==0
.noflag_reg 21
	mr $0, r21
.flag_reg 21
.else
.macros_off
	mfspr $0, $1
.macros_on
.endif
.endmacro

/*
 * divs
 * d(int i, int j) { return i/j; }
 *
 * rT <- rA / rB
 * r21 <- rT * rB
 * r21 <- rA - (rT * rB)
 */

.macro divs
.noflag_reg 22
	divw r22, $1, $2
.noflag_reg 21
	mullw r21, r22, $2
	subf r21, r21, $1
	mr $0, r22
.flag_reg 21
.flag_reg 22
.endmacro


/*
 * div
 * void p(unsigned long n, int b) { register char *c; *c=n%b; n/=b; }
 *
 * this is the test case which causes the cc to produce div. But I have noticed
 * that is always makes sure that rA has 0. Need to revisit this macro in case
 * that is not true.
 *
 * doing a divs macro for now.
 */

.macro div
.noflag_reg 21
	mr $1, r21
.noflag_reg 22
	divwu r22, $1, $2
	mullw r21, r22, $2
	subf r21, r21, $1
	mr $0, r22
.flag_reg 21
.flag_reg 22
.endmacro


/*
 * mul
 */

.macro mul
.noflag_reg 21
	mullw r21, $1, $2
.flag_reg 21
	mulhw $0, $1, $2
.endmacro

/*
 * doz
 * void d(int i, int j) { register int *c; *c = j-((i>j)? j : i); }
 */

.set CR7MASK,0x40

.macro doz
.noflag_reg 22
	mfcr r22
.flag_reg 22
	cmp cr7, 0, $1, $2
	bc 12, 5, 0f
	subfc $0, $1, $2
	b 1f
0:
	addi $0, 0, 0
1:
.noflag_reg 22
	mtcrf CR7MASK, r22
.flag_reg 22
.endmacro


/*
 * dozi
 * void d(int i) { register int *c; *c = 23-((i>23)? 23 : i); }
 */

.macro dozi
.noflag_reg 22
	mfcr r22
.flag_reg 22
	cmpi cr7,0, $1, $2
	bc 12, 5, 0f
	subfic $0, $1, $2
	b 1f
0:
	addi $0, 0, 0
1:
.noflag_reg 22
	mtcrf CR7MASK, r22
.flag_reg 22
.endmacro

/*
 * maskir rA, rS, rB
 *
 *  rA <- (rB & rS) | ((~rB)&rA)
 *
 */

.macro maskir
	andc $0, $0, $2
.noflag_reg 22
	and r22, $2, $1
	or $0, r22, $0
.flag_reg 22
.endmacro

/*
 * sliq
 */

.macro sliq
.noflag_reg 22
	slwi r22, $1, $2
.noflag_reg 21
	rotlwi r21, $1, $2
	mr $0, r22
.flag_reg 21
.flag_reg 22
.endmacro


/*
 * sriq
 */

.macro sriq
.noflag_reg 22
	srwi r22, $1, $2
.noflag_reg 21
	rotrwi r21, $1, $2
	mr $0, r22
.flag_reg 21
.flag_reg 22
.endmacro

/*
 * sle
 *
 */
.set LOW5BITS, 0x001F

.macro sle
.noflag_reg 22
	andi. r22, $2, LOW5BITS
	slw $0, $1, r22
.noflag_reg 21
	rotlw r21, $1, r22
.flag_reg 21
.flag_reg 22
.endmacro

/*
 * sre
 */

.macro sre
.noflag_reg 22
    andi. r22, $2, LOW5BITS
	srw $0, $1, r22
	subfic r22, r22, 32
.noflag_reg 21
	rotlw r21, $1, r22
.flag_reg 21
.flag_reg 22
.endmacro

/*
 * sre.
 */

.macro sre.
.noflag_reg 22
    andi. r22, $2, LOW5BITS
    srw. $0, $1, r22
    subfic r22, r22, 32
.noflag_reg 21
    rotlw r21, $1, r22
.flag_reg 21
.flag_reg 22
.endmacro

/*
 * srea
 */

.macro srea
.noflag_reg 22
    andi. r22, $2, LOW5BITS
	sraw $0, $1, r22
	subfic r22, r22, 32
.noflag_reg 21
	rotlw r21, $1, r22
.flag_reg 21
.flag_reg 22
.endmacro

/*
 * srq
 */

.macro srq
.noflag_reg 22
    andi. r22, $2, LOW5BITS
	srw $0, $1, $2
	subfic r22, r22, 32
.noflag_reg 21
	rotlw r21, $1, r22
.flag_reg 21
.flag_reg 22
.endmacro

/*
 * srlq
 *
 * check bit 26
 * if bit 26 == 0 goto 0f
 * take care os the case where bit26 == 1
 * goto 1f 
 * 0: take care of bit26 == 0 case
 * 1:
 *
 *   THIS MACRO THRASHES CR0
 */

.set HIGHBIT, 0x8000
.set BIT26, 0x0040

.macro srlq
.noflag_reg 22
	andi. r22, $2, BIT26
	cmpi cr7, 0,  r22, BIT26
	beq cr7, 0f 
	andi. r22, $2, LOW5BITS
.noflag_reg 21
	slw $0, r21, r22
	srw $0, r21, r22
	b 1f
0:
	addis r22, 0, HIGHBIT
	sraw r22, r22, $2
	srw $0, $1, $2
	and r22, r21, r22
	or $0, $0, r22
.flag_reg 21
.flag_reg 22
1:
.endmacro

/*
 * slliq
 */

.macro slliq
.noflag_reg 21
.noflag_reg 22
	rlwimi r22, $1, $2 , 0, (31-$2)
	rotlwi r21, $1, $2
	mr $0, r22
.flag_reg 21
.flag_reg 22
.endmacro

/*
 * srliq
 */

.macro srliq
.noflag_reg 22
    rlwimi r22, $1, (32-$2), 0, $2
.noflag_reg 21
    rotlwi r21, $1, $2
	mr $0, r22
.flag_reg 21
.flag_reg 22
.endmacro


 /* -----------------------------------------------
  * --  Woraround macros for mftb assembler bug  --
  * ----------------------------------------------- */
 
.set r0, 0
.set r1, 1
.set r2, 2
.set r3, 3
.set r4, 4
.set r5, 5
.set r6, 6
.set r7, 7
.set r8, 8
.set r9, 9
.set r10, 10
.set r11, 11
.set r12, 12
.set r13, 13
.set r14, 14
.set r15, 15
.set r16, 16
.set r17, 17
.set r18, 18
.set r19, 19
.set r20, 20
.set r21, 21
.set r22, 22
.set r23, 23
.set r24, 24
.set r25, 25
.set r26, 26
.set r27, 27
.set r28, 28
.set r29, 29
.set r30, 30
.set r31, 31


.macro mftb
.if $0==0
	.long	0x7C0C42E6
.elseif $0==1
	.long	0x7C2C42E6
.elseif $0==2
	.long	0x7C4C42E6
.elseif $0==3
	.long	0x7C6C42E6
.elseif $0==4
	.long	0x7C8C42E6
.elseif $0==5
	.long	0x7CAC42E6
.elseif $0==6
	.long	0x7CCC42E6
.elseif $0==7
	.long	0x7CEC42E6
.elseif $0==8
	.long	0x7D0C42E6
.elseif $0==9
	.long	0x7D2C42E6
.elseif $0==10
	.long	0x7D4C42E6
.elseif $0==11
	.long	0x7D6C42E6
.elseif $0==12
	.long	0x7D8C42E6
.elseif $0==13
	.long	0x7DAC42E6
.elseif $0==14
	.long	0x7DCC42E6
.elseif $0==15
	.long	0x7DEC42E6
.elseif $0==16
	.long	0x7E0C42E6
.elseif $0==17
	.long	0x7E2C42E6
.elseif $0==18
	.long	0x7E4C42E6
.elseif $0==19
	.long	0x7E6C42E6
.elseif $0==20
	.long	0x7E8C42E6
.elseif $0==21
	.long	0x7EAC42E6
.elseif $0==22
	.long	0x7ECC42E6
.elseif $0==23
	.long	0x7EEC42E6
.elseif $0==24
	.long	0x7F0C42E6
.elseif $0==25
	.long	0x7F2C42E6
.elseif $0==26
	.long	0x7F4C42E6
.elseif $0==27
	.long	0x7F6C42E6
.elseif $0==28
	.long	0x7F8C42E6
.elseif $0==29
	.long	0x7FAC42E6
.elseif $0==30
	.long	0x7FCC42E6
.elseif $0==31
	.long	0x7FEC42E6
.else
	.abort "invalid register for mftb"
.endif
.endmacro


.macro mftbu
.if $0==0
	.long	0x7C0D42E6
.elseif $0==1
	.long	0x7C2D42E6
.elseif $0==2
	.long	0x7C4D42E6
.elseif $0==3
	.long	0x7C6D42E6
.elseif $0==4
	.long	0x7C8D42E6
.elseif $0==5
	.long	0x7CAD42E6
.elseif $0==6
	.long	0x7CCD42E6
.elseif $0==7
	.long	0x7CED42E6
.elseif $0==8
	.long	0x7D0D42E6
.elseif $0==9
	.long	0x7D2D42E6
.elseif $0==10
	.long	0x7D4D42E6
.elseif $0==11
	.long	0x7D6D42E6
.elseif $0==12
	.long	0x7D8D42E6
.elseif $0==13
	.long	0x7DAD42E6
.elseif $0==14
	.long	0x7DCD42E6
.elseif $0==15
	.long	0x7DED42E6
.elseif $0==16
	.long	0x7E0D42E6
.elseif $0==17
	.long	0x7E2D42E6
.elseif $0==18
	.long	0x7E4D42E6
.elseif $0==19
	.long	0x7E6D42E6
.elseif $0==20
	.long	0x7E8D42E6
.elseif $0==21
	.long	0x7EAD42E6
.elseif $0==22
	.long	0x7ECD42E6
.elseif $0==23
	.long	0x7EED42E6
.elseif $0==24
	.long	0x7F0D42E6
.elseif $0==25
	.long	0x7F2D42E6
.elseif $0==26
	.long	0x7F4D42E6
.elseif $0==27
	.long	0x7F6D42E6
.elseif $0==28
	.long	0x7F8D42E6
.elseif $0==29
	.long	0x7FAD42E6
.elseif $0==30
	.long	0x7FCD42E6
.elseif $0==31
	.long	0x7FED42E6
.else
	.abort "invalid register for mftb"
.endif
.endmacro
