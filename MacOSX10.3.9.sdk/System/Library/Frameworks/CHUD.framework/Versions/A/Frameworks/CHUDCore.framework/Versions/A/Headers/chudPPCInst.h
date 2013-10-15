/*
 * Copyright (c) 2002-2004 Apple Computer, Inc. All rights reserved.
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

#ifndef _CHUD_PPC_INST_H_
#define _CHUD_PPC_INST_H_

#include <sys/types.h>
#include <stdint.h>

#define HI16(x) (((uint32_t)x)>>16 & 0xFFFF)
#define LO16(x) (((uint32_t)x) & 0xFFFF)

typedef struct ppc_a_form {
    uint32_t majorOp : 6;		/* major opcode */
    uint32_t fT_idx : 5;		/* index of register fT */
    uint32_t fA_idx : 5;		/* index of register fA */
    uint32_t fB_idx : 5;		/* index of register fB */
    uint32_t fC_idx : 5;		/* index of register fC */
    uint32_t minorOp : 5;		/* minor opcode */
    uint32_t record : 1;		/* record */
} ppc_a_form;

typedef struct ppc_b_form {
    uint32_t majorOp : 6;		/* major opcode */
    uint32_t bo : 5;			/* bo */
    uint32_t bi : 5;			/* bi */
    int32_t bd : 14;			/* bd */
    uint32_t abs_addr : 1;		/* absolute address */
    uint32_t link : 1;			/* link */
} ppc_b_form;

typedef struct ppc_d_form {
    uint32_t majorOp : 6;		/* major opcode */
    uint32_t rDST_idx : 5;		/* index of register rD/rS/rT */
    uint32_t rA_idx : 5;		/* index of register rA */
    int32_t simm : 16;			/* signed immediate */
} ppc_d_form;

typedef struct ppc_ds_form { // 64-bit only
    uint32_t majorOp : 6;		/* major opcode */
    uint32_t rDST_idx : 5;		/* index of register rD/rS/rT */
    uint32_t rA_idx : 5;		/* index of register rA */
    int32_t simm : 14;			/* signed immediate */
    uint32_t minorOp : 2;		/* minor (extended) opcode */
} ppc_ds_form;

typedef struct ppc_i_form {
    uint32_t majorOp : 6;		/* major opcode */
    int32_t simm : 24;			/* signed immediate */
    uint32_t abs_addr : 1;		/* absolute address */
    uint32_t link : 1;			/* link */
} ppc_i_form;

typedef struct ppc_m_form {
    uint32_t majorOp : 6;		/* major opcode */
    uint32_t rS_idx : 5;		/* index of register rS/rT */
    uint32_t rA_idx : 5;		/* index of register rA */
    uint32_t rB_idx : 5;		/* index of register rB */
    uint32_t mb : 5;			/* first bit of bit mask (mask begin) */
    uint32_t me : 5;			/* last bit of bit mask (mask end) */
    uint32_t record : 1;		/* record */
} ppc_m_form;

typedef struct ppc_md_form { // 64-bit only
    uint32_t majorOp : 6;		/* major opcode */
    uint32_t rS_idx : 5;		/* index of register rS/rT */
    uint32_t rA_idx : 5;		/* index of register rA */
    uint32_t shamt : 5;			/* shift amount */
    uint32_t mx : 6;			/* mask bit (begin or end depending on instruction) */
    uint32_t minorOp : 3;		/* minor (extended) opcode */
    uint32_t shamt2 : 1;		/* shift amount (cont.) */
    uint32_t record : 1;		/* record */
} ppc_md_form;

typedef struct ppc_mds_form { // 64-bit only
    uint32_t majorOp : 6;		/* major opcode */
    uint32_t rS_idx : 5;		/* index of register rS/rT */
    uint32_t rA_idx : 5;		/* index of register rA */
    uint32_t rB_idx : 5;		/* index of register rB */
    uint32_t mx : 6;			/* mask bit (begin or end depending on instruction) */
    uint32_t minorOp : 4;		/* minor (extended) opcode */
    uint32_t record : 1;		/* record */
} ppc_mds_form;

typedef struct ppc_sc_form {
    uint32_t majorOp : 6;		/* major opcode */
    uint32_t /* reserved */ : 26;	/* reserved */
} ppc_sc_form;

typedef struct ppc_x_form {
    uint32_t majorOp : 6;		/* major opcode */
    uint32_t rST_idx : 5;		/* index of register rS/rT */
    uint32_t rA_idx : 5;		/* index of register rA */
    uint32_t rB_idx : 5;		/* index of register rB */
    uint32_t minorOp : 10;		/* minor opcode */
    uint32_t record : 1;		/* record */
} ppc_x_form;

typedef struct ppc_xfx_form {
    uint32_t majorOp : 6;		/* major opcode */
    uint32_t rST_idx : 5;		/* index of register rS/rT */
    uint32_t spr_lo : 5;		/* spr lo bits - hi and lo bits of SPR # are swapped when encoded in instruction */
    uint32_t spr_hi : 5;		/* spr hi bits */
    uint32_t minorOp : 10;		/* minor opcode */
    uint32_t /* reserved */ : 1;	/* reserved */
} ppc_xfx_form;

typedef struct ppc_xfl_form {
    uint32_t majorOp : 6;		/* major opcode */
    uint32_t /* reserved */ : 1;	/* reserved */
    uint32_t flm : 8;			/*  */
    uint32_t /* reserved */ : 1;	/* reserved */
    uint32_t fB_idx : 5;		/* index of register fB */
    uint32_t minorOp : 10;		/* minor (extended) opcode */
    uint32_t record : 1;		/* record */
} ppc_xfl_form;

typedef struct ppc_xl_form {
    uint32_t majorOp : 6;		/* major opcode */
    uint32_t bT_idx : 5;		/* index of CR field bT */
    uint32_t bA_idx : 5;		/* index of CR field bA */
    uint32_t bB_idx : 5;		/* index of CR field bB */
    uint32_t minorOp : 10;		/* minor opcode */
    uint32_t link : 1;			/* link */
} ppc_xl_form;

typedef struct ppc_xo_form {
    uint32_t majorOp : 6;		/* major opcode */
    uint32_t rT_idx : 5;		/* index of register rT */
    uint32_t rA_idx : 5;		/* index of register rA */
    uint32_t rB_idx : 5;		/* index of register rB */
    uint32_t overflow : 1;		/* overflow enable */
    uint32_t minorOp : 9;		/* minor opcode */
    uint32_t record : 1;		/* record */
} ppc_xo_form;

typedef struct ppc_xs_form { // 64-bit only
    uint32_t majorOp : 6;		/* major opcode */
    uint32_t rS_idx : 5;		/* index of register rS */
    uint32_t rA_idx : 5;		/* index of register rA */
    uint32_t shamt : 5;			/* shift amount */
    uint32_t minorOp : 9;		/* minor opcode */
    uint32_t shamt2 : 1;		/* shift amount (cont.) */
    uint32_t record : 1;		/* record */
} ppc_xs_form;

typedef union ppc_inst_t {
  uint32_t value;
  ppc_a_form a_form;
  ppc_b_form b_form;
  ppc_d_form d_form;
  ppc_ds_form ds_form;
  ppc_i_form i_form;
  ppc_m_form m_form;
  ppc_md_form md_form;
  ppc_mds_form mds_form;
  ppc_sc_form sc_form;
  ppc_x_form x_form;
  ppc_xfx_form xfx_form;
  ppc_xfl_form xfl_form;
  ppc_xl_form xl_form;
  ppc_xo_form xo_form;
  ppc_xs_form xs_form;
} ppc_inst_t;

static inline ppc_inst_t PTMakePPCInst(uint32_t val)
{
    ppc_inst_t inst;
    inst.value = val;
    return inst;
}

typedef ppc_inst_t ppc_inst;

#endif /* _CHUD_PPC_INST_H_ */
