/*
 * Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _PPC_MODE_INDEPENDENT_ASM_H_
#define _PPC_MODE_INDEPENDENT_ASM_H_


/* This file facilitates writing mode-independent PPC assembler source, ie
 * source which can be built both for 32-bit mode (__ppc__) and 64-bit 
 * mode (__ppc64__.)
 *
 * It defines constants such as the number of bytes in a GPR (GPR_BYTES),
 * macros to address and call externals (MI_GET_ADDRESS), and a set of mode
 * independent PPC assembler pseudo-mnemonics.
 *
 * The assembler mnemonics map to word operations when building for __ppc__,
 * and to doubleword operations when building for __ppc64__.  They use "g" to
 * stand for either word or doubleword, depending on the target mode.  
 *
 * Although there are certainly other things to be aware of when writing code
 * targeted at both 32 and 64-bit mode, using these macros and psuedo-mnemonics
 * is surprisingly helpful.
 */

#if defined(__ppc64__)
#define MODE_CHOICE(x, y) y
#elif defined(__ppc__)
#define MODE_CHOICE(x, y) x
#else
#error undefined architecture
#endif


/* The mode-independent "g" mnemonics.  */

#define cmpg    MODE_CHOICE(cmpw, cmpd)
#define cmplg   MODE_CHOICE(cmplw, cmpld)
#define cmpgi   MODE_CHOICE(cmpwi, cmpdi)
#define cmplgi  MODE_CHOICE(cmplwi, cmpldi)
#define srgi    MODE_CHOICE(srwi, srdi)
#define srg     MODE_CHOICE(srw, srd)
#define sragi   MODE_CHOICE(srawi, sradi)
#define slgi    MODE_CHOICE(slwi, sldi)
#define rotlgi  MODE_CHOICE(rotlwi, rotldi)
#define clrrgi  MODE_CHOICE(clrrwi, clrrdi)
#define cntlzg  MODE_CHOICE(cntlzw, cntlzd)
#define lg      MODE_CHOICE(lwz, ld)
#define stg     MODE_CHOICE(stw, std)
#define lgx     MODE_CHOICE(lwzx, ldx)
#define stgx    MODE_CHOICE(stwx, stdx)
#define lgu     MODE_CHOICE(lwzu, ldu)
#define stgu    MODE_CHOICE(stwu, stdu)
#define lgux    MODE_CHOICE(lwzux, ldux)
#define stgux   MODE_CHOICE(stwux, stdux)
#define lgwa    MODE_CHOICE(lwz, lwa)

#define g_long  MODE_CHOICE(long, quad)         // usage is ".g_long"


/* Architectural constants.  */

#define GPR_BYTES       MODE_CHOICE(4,8)        // size of a GPR in bytes
#define LOG2_GPR_BYTES  MODE_CHOICE(2,3)        // log2(GPR_BYTES)


/* Stack frame definitions.  To keep things simple, we are limited
 * to eight arguments and two locals.
 */
#define SF_CRSAVE       MODE_CHOICE(4,8)
#define SF_RETURN       MODE_CHOICE(8,16)
#define SF_ARG1         MODE_CHOICE(24,48)
#define SF_ARG2         MODE_CHOICE(28,56)
#define SF_ARG3         MODE_CHOICE(32,64)
#define SF_ARG4         MODE_CHOICE(36,72)
#define SF_ARG5         MODE_CHOICE(40,80)
#define SF_ARG6         MODE_CHOICE(44,88)
#define SF_ARG7         MODE_CHOICE(48,96)
#define SF_ARG8         MODE_CHOICE(52,104)
#define SF_LOCAL1       MODE_CHOICE(56,112)
#define SF_LOCAL2       MODE_CHOICE(60,120)
#define SF_SIZE         MODE_CHOICE(64,128)

#define SF_ALIGNMENT    MODE_CHOICE(16,32)
#define SF_REDZONE      MODE_CHOICE(224,320)

#define SF_ROUND(x)     (((x)+SF_ALIGNMENT-1)&(-SF_ALIGNMENT))

#define SF_MINSIZE      MODE_CHOICE(64,128)
 
 
/* WARNING: some clients fall through this macro, so do not attempt
 * to optimize by doing an ".align 5" in the macro.  Do the 32-byte
 * alignment in the .s file, before invoking the macro.
 */
#define MI_ENTRY_POINT(name)     \
    .globl  name                @\
    .text                       @\
    .align  2                   @\
name:

#define MI_PUSH_STACK_FRAME      \
    mflr    r0                  @\
    stg     r0,SF_RETURN(r1)    @\
    stgu    r1,-SF_SIZE(r1)
    
#define MI_POP_STACK_FRAME_AND_RETURN    \
    lg      r0,SF_RETURN+SF_SIZE(r1)    @\
    addi    r1,r1,SF_SIZE               @\
    mtlr    r0                          @\
    blr
    

/* MI_GET_ADDRESS(reg,var) is the basic primitive to address data or code.
 * It works both in 32 and 64-bit mode, and with static and dynamic
 * code generation.  Note however that it can be invoked at most once per
 * symbol, since it always creates a non_lazy_ptr in dynamic mode.
 * Save the address for re-use, rather than invoking the macro again.
 */
#if defined(__DYNAMIC__)
#define MI_GET_ADDRESS(reg,var)  \
    mflr    r0                  @\
    bcl     20,31,1f            @\
1:  mflr    reg                 @\
    mtlr    r0                  @\
    addis   reg,reg,ha16(L ## var ## __non_lazy_ptr - 1b) @\
    lg      reg,lo16(L ## var ## __non_lazy_ptr - 1b)(reg) @\
    .non_lazy_symbol_pointer    @\
    .align  LOG2_GPR_BYTES      @\
    .indirect_symbol var        @\
L ## var ## __non_lazy_ptr:      @\
    .g_long 0                   @\
    .text                       @\
    .align  2
#else /* ! __DYNAMIC__ */
#define MI_GET_ADDRESS(reg,var)  \
    lis     reg,hi16(var)       @\
    ori     reg,reg,lo16(var)
#endif


/* MI_CALL_EXTERNAL(var)  */

#if defined(__DYNAMIC__)
#define MI_CALL_EXTERNAL(var)    \
    MI_GET_ADDRESS(r12,var)     @\
    mtctr   r12                 @\
    bctrl
#else /* ! __DYNAMIC__ */
#define MI_CALL_EXTERNAL(var)    \
    bl      var
#endif


/* MI_BRANCH_EXTERNAL(var)  */

#if defined(__DYNAMIC__)
#define MI_BRANCH_EXTERNAL(var)  \
    MI_GET_ADDRESS(r12,var)     @\
    mtctr   r12                 @\
    bctr
#else /* ! __DYNAMIC__ */
#define MI_BRANCH_EXTERNAL(var)  \
    b       var
#endif

    
#endif  /* _PPC_MODE_INDEPENDENT_ASM_H_ */
