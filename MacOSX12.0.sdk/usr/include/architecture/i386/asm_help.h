/*
 * Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */
/* Copyright (c) 1991 NeXT Computer, Inc.  All rights reserved.
 *
 *	File:	architecture/i386/asm_help.h
 *	Author:	Mike DeMoney, NeXT Computer, Inc.
 *	Modified for i386 by: Bruce Martin, NeXT Computer, Inc.
 *
 *	This header file defines macros useful when writing assembly code
 *	for the Intel i386 family processors.
 *
 * HISTORY
 * 10-Mar-92  Bruce Martin (bmartin@next.com)
 *	Adapted to i386
 * 23-Jan-91  Mike DeMoney (mike@next.com)
 *	Created.
 */

#ifndef	_ARCH_I386_ASM_HELP_H_
#define	_ARCH_I386_ASM_HELP_H_

#include	<architecture/i386/reg_help.h>


#ifdef	__ASSEMBLER__

#define ALIGN						\
	.align	2, 0x90

#define	ROUND_TO_STACK(len)				\
	(((len) + STACK_INCR - 1) / STACK_INCR * STACK_INCR)

#ifdef notdef
#if defined(__i386__)
#define CALL_MCOUNT						\
	pushl	%ebp						;\
	movl	%esp, %ebp					;\
	.data							;\
	1: .long 0						;\
	.text							;\
	lea 9b,%edx						;\
	call mcount						;\
	popl	%ebp						;
#elif defined(__x86_64__)
#define CALL_MCOUNT						\
	pushq	%rbp						;\
	movq	%rsp, %rbp					;\
	.data							;\
	1: .quad 0						;\
	.text							;\
	lea 9b,%r13						;\
	call mcount						;\
	popq	%rbp					;
#endif
#else
#define CALL_MCOUNT
#endif

/*
 * Prologue for functions that may call other functions.  Saves
 * registers and sets up a C frame.
 */
#if defined(__i386__)
#define NESTED_FUNCTION_PROLOGUE(localvarsize)			\
	.set	L__framesize,ROUND_TO_STACK(localvarsize)	;\
	.set	L__nested_function, 1				;\
	CALL_MCOUNT						\
	.if L__framesize						;\
	  pushl	%ebp						;\
	  movl	%esp, %ebp					;\
	  subl	$L__framesize, %esp				;\
	.endif							;\
	pushl	%edi						;\
	pushl	%esi						;\
	pushl	%ebx
#elif defined(__x86_64__)
#define NESTED_FUNCTION_PROLOGUE(localvarsize)			\
	.set	L__framesize,ROUND_TO_STACK(localvarsize)	;\
	.set	L__nested_function, 1				;\
	CALL_MCOUNT						\
	.if L__framesize						;\
	  pushq	%rbp						;\
	  movq	%rsp, %rbp					;\
	  subq	$L__framesize, %rsp				;\
	.endif							;
#endif

/*
 * Prologue for functions that do not call other functions.  Does not
 * save registers (this is the functions responsibility).  Does set
 * up a C frame.
 */
#if defined(__i386__)
#define LEAF_FUNCTION_PROLOGUE(localvarsize)			\
	.set	L__framesize,ROUND_TO_STACK(localvarsize)	;\
	.set	L__nested_function, 0				;\
	CALL_MCOUNT						\
	.if L__framesize						;\
	  pushl	%ebp						;\
	  movl	%esp, %ebp					;\
	  subl	$L__framesize, %esp				;\
	.endif
#elif defined(__x86_64__)
#define LEAF_FUNCTION_PROLOGUE(localvarsize)			\
	.set	L__framesize,ROUND_TO_STACK(localvarsize)	;\
	.set	L__nested_function, 0				;\
	CALL_MCOUNT						\
	.if L__framesize						;\
	  pushq	%rbp						;\
	  movq	%rsp, %rbp					;\
	  subq	$L__framesize, %rsp				;\
	.endif
#endif

/*
 * Epilogue for any function.
 *
 * We assume that all Leaf functions will be responsible for saving any
 * local registers they clobber.
 */
#if defined(__i386__)
#define FUNCTION_EPILOGUE					\
	.if L__nested_function					;\
	  popl	%ebx						;\
	  popl	%esi						;\
	  popl	%edi						;\
	.endif							;\
	.if L__framesize						;\
	  movl	%ebp, %esp					;\
	  popl	%ebp						;\
	.endif							;\
	ret
#elif defined(__x86_64__)
#define FUNCTION_EPILOGUE					\
	.if L__framesize						;\
	  movq	%rbp, %rsp					;\
	  popq	%rbp						;\
	.endif							;\
	ret
#endif

/*
 * Macros for declaring procedures
 *
 * Use of these macros allows ctags to have a predictable way
 * to find various types of declarations.  They also simplify
 * inserting appropriate symbol table information.
 *
 * NOTE: these simple stubs will be replaced with more
 * complicated versions once we know what the linker and gdb
 * will require as far as register use masks and frame declarations.
 * These macros may also be ifdef'ed in the future to contain profiling
 * code.
 *
 */

/*
 * TEXT -- declare start of text segment
 */
#define	TEXT						\
	.text

/*
 * DATA -- declare start of data segment
 */
#define DATA						\
	.data

/*
 * LEAF -- declare global leaf procedure
 * NOTE: Control SHOULD NOT FLOW into a LEAF!  A LEAF should only
 * be jumped to.  (A leaf may do an align.)  Use a LABEL() if you
 * need control to flow into the label.
 */
#define	LEAF(name, localvarsize)			\
	.globl	name					;\
	ALIGN						;\
name:							;\
	LEAF_FUNCTION_PROLOGUE(localvarsize)

/*
 * X_LEAF -- declare alternate global label for leaf
 */
#define	X_LEAF(name, value)				\
	.globl	name					;\
	.set	name,value

/*
 * P_LEAF -- declare private leaf procedure
 */
#define	P_LEAF(name, localvarsize)			\
	ALIGN						;\
name:							;\
	LEAF_FUNCTION_PROLOGUE(localvarsize)

/*
 * LABEL -- declare a global code label
 * MUST be used (rather than LEAF, NESTED, etc) if control
 * "flows into" the label.
 */
#define	LABEL(name)					\
	.globl	name					;\
name:

/*
 * NESTED -- declare procedure that invokes other procedures
 */
#define	NESTED(name, localvarsize)			\
	.globl	name					;\
	ALIGN						;\
name:							;\
	NESTED_FUNCTION_PROLOGUE(localvarsize)

/*
 * X_NESTED -- declare alternate global label for nested proc
 */
#define	X_NESTED(name, value)				\
	.globl	name					;\
	.set	name,value

/*
 * P_NESTED -- declare private nested procedure
 */
#define	P_NESTED(name, localvarsize)			\
	ALIGN						;\
name:							;\
	NESTED_FUNCTION_PROLOGUE(localvarsize)

/*
 * END -- mark end of procedure
 */
#define	END(name)					\
	FUNCTION_EPILOGUE


/*
 * Storage definition macros
 * The main purpose of these is to allow an easy handle for ctags
 */

/*
 * IMPORT -- import symbol
 */
#define	IMPORT(name)					\
	.reference	name

/*
 * ABS -- declare global absolute symbol
 */
#define	ABS(name, value)				\
	.globl	name					;\
	.set	name,value

/*
 * P_ABS -- declare private absolute symbol
 */
#define	P_ABS(name, value)				\
	.set	name,value

/*
 * EXPORT -- declare global label for data
 */
#define	EXPORT(name)					\
	.globl	name					;\
name:

/*
 * BSS -- declare global zero'ed storage
 */
#define	BSS(name,size)					\
	.comm	name,size


/*
 * P_BSS -- declare private zero'ed storage
 */
#define	P_BSS(name,size)				\
	.lcomm	name,size

/*
 * dynamic/PIC macros for routines which reference external symbols
 */

#if defined(__DYNAMIC__)
#if defined(__i386__)
#define PICIFY(var)					\
	call	1f					; \
1:							; \
	popl	%edx					; \
	movl	L ## var ## __non_lazy_ptr-1b(%edx),%edx
#elif defined(__x86_64__)
#define PICIFY(var)					\
	movq	var@GOTPCREL(%rip),%r11
#endif

#if defined(__i386__)
#define CALL_EXTERN_AGAIN(func)	\
	PICIFY(func)		; \
	call	*%edx
#elif defined(__x86_64__)
#define CALL_EXTERN_AGAIN(func)	\
	call	func
#endif

#if defined(__i386__)
#define NON_LAZY_STUB(var)	\
.section __IMPORT,__pointers,non_lazy_symbol_pointers	; \
L ## var ## __non_lazy_ptr:	; \
.indirect_symbol var		; \
.long 0				; \
.text
#elif defined(__x86_64__)
#define NON_LAZY_STUB(var)
#endif

#define CALL_EXTERN(func)	\
	CALL_EXTERN_AGAIN(func)	; \
	NON_LAZY_STUB(func)

#if defined(__i386__)
#define BRANCH_EXTERN(func)	\
	PICIFY(func)		; \
	jmp	*%edx		; \
	NON_LAZY_STUB(func)
#elif defined(__x86_64__)
#define BRANCH_EXTERN(func)	\
	jmp	func
#endif

#if defined(__i386__)
#define PUSH_EXTERN(var)	\
	PICIFY(var)		; \
	movl	(%edx),%edx	; \
	pushl	%edx		; \
	NON_LAZY_STUB(var)
#endif

#if defined(__i386__)
#define REG_TO_EXTERN(reg, var)	\
	PICIFY(var)		; \
	movl	reg, (%edx)	; \
	NON_LAZY_STUB(var)
#elif defined(__x86_64__)
#define REG_TO_EXTERN(reg, var)	\
	PICIFY(var)		; \
	mov		reg, (%r11)
#endif

#if defined(__i386__)
#define EXTERN_TO_REG(var, reg)				\
	call	1f					; \
1:							; \
	popl	%edx					; \
	movl	L ## var ##__non_lazy_ptr-1b(%edx),reg	; \
	NON_LAZY_STUB(var)
#elif defined(__x86_64__)
#define EXTERN_TO_REG(var, reg)				\
	PICIFY(var)		; \
	mov    (%r11), reg
#endif

#else
#define BRANCH_EXTERN(func)	jmp	func
#define PUSH_EXTERN(var)	push	var
#define CALL_EXTERN(func)	call	func
#define CALL_EXTERN_AGAIN(func)	call	func
#if defined(__i386__)
#define REG_TO_EXTERN(reg, var)	mov	reg, var
#define EXTERN_TO_REG(var, reg)	mov	$ ## var, reg
#elif defined(__x86_64__)
#define REG_TO_EXTERN(reg, var)	mov	reg, var ## (%rip)
#define EXTERN_TO_REG(var, reg)	mov	var ## (%rip), reg
#endif
#endif

#endif	/* __ASSEMBLER__ */

#endif	/* _ARCH_I386_ASM_HELP_H_ */
