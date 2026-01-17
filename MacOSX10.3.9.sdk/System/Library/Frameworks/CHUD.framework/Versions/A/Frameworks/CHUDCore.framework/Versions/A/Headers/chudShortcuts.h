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
 
#ifndef	CHUD_SHORTCUTS_H
#define	CHUD_SHORTCUTS_H

#include <CoreFoundation/CoreFoundation.h>

#ifdef __cplusplus
extern "C" {
#endif

int     chudOpenShortcutFile( char *fpath );
int     chudSaveShortcutFile( char *fpath );

int     chudShortcutSelectCpuType( int cpuType );

CFMutableDictionaryRef chudGetShortcutDictionary(void);
CFMutableDictionaryRef chudGetShortcutDictionaryForCurrentCPU(void);
extern char	*shortcut_dict_key[];

typedef enum {
	ksc_desc = 0,
	ksc_ptype,
	ksc_mtype,
	ksc_eq1,
	ksc_eq1_desc,
	ksc_eq2,
	ksc_eq2_desc,	
	ksc_eq3,
	ksc_eq3_desc,	
	ksc_eq4,		
	ksc_eq4_desc,
	ksc_eq5,		
	ksc_eq5_desc,
	ksc_eq6,
	ksc_eq6_desc,
	ksc_eq7,
	ksc_eq7_desc,
	ksc_eq8,
	ksc_eq8_desc,
	ksc_eq9,
	ksc_eq9_desc,
	ksc_eq10,
	ksc_eq10_desc,
	ksc_eq11,
	ksc_eq11_desc,
	ksc_eq12,
	ksc_eq12_desc
} sc_key_index_t;

#define SC_NO_FILE 	0
#define SC_BI_FILE 	1
#define SC_CU_FILE 	2
#define SC_US_FILE 	3

#define USE_BUILTIN_SC  1
#define USE_CUSTOM_SC   2
#define USE_USER_SC     4
#define USE_ANY_SC      7

#define THIS_CPU_TYPE  		-1 //for cpu type
#define UNSPECD_CPU_TYPE 	0
#define BUILTIN_SHORTCUTS  	"_builtin_" //instead of file names

#define SC_NOT_USED_NUM "-1"
#define SC_NOT_USED_STR "#"

#define SC_EQ1 0
#define SC_EQ2 1
#define SC_EQ3 2
#define SC_EQ4 3
#define SC_EQ5 4
#define SC_EQ6 5
#define SC_EQ7 6
#define SC_EQ8 7
#define SC_EQ9 8
#define SC_EQA 9
#define SC_EQB 10
#define SC_EQC 11
#define SC_MAX_EQ_COUNT 12
#define NO_SHORTCUT_SELECTED 0

#define  SC_MAX_ENTRIES 256

#define  SC_NOTUSED    -1
#define  SC_CPUTYPE     0
#define  SC_NMBR        1
#define  SC_DESC        2
#define  SC_ABR         3
#define  SC_PMC1        4
#define  SC_PMC2        5
#define  SC_PMC3        6
#define  SC_PMC4        7
#define  SC_PMC5        8
#define  SC_PMC6        9
#define  SC_MCTYP       10
#define  SC_MCPC1       11
#define  SC_MCPC2       12
#define  SC_MCPC3       13
#define  SC_MCPC4       14
#define  SC_BFS         15 //boolean
#define  SC_CMODE       16 
#define  SC_RES1        17
#define  SC_RES1DESC    18
#define  SC_RES2        19
#define  SC_RES2DESC    20
#define  SC_RES3        21
#define  SC_RES3DESC    22
#define  SC_RES4        23
#define  SC_RES4DESC    24
#define  SC_RES5        25
#define  SC_RES5DESC    26
#define  SC_RES6        27
#define  SC_RES6DESC    28
#define  SC_THRESH      29
#define  SC_THMULT      30
#define  SC_P1PMC1       4
#define  SC_P1PMC2       5
#define  SC_P1PMC3       6
#define  SC_P1PMC4       7
#define  SC_P1PMC5       8
#define  SC_P1PMC6       9
#define  SC_P2PMC1      31
#define  SC_P2PMC2      32
#define  SC_P2PMC3      33
#define  SC_P2PMC4      34
#define  SC_P2PMC5      35
#define  SC_P2PMC6      36
#define  SC_MC1PC1      11
#define  SC_MC1PC2      12
#define  SC_MC1PC3      13
#define  SC_MC1PC4      14
#define  SC_MC2PC1      37
#define  SC_MC2PC2      38
#define  SC_MC2PC3      39
#define  SC_MC2PC4      40
#define  SC_RES7        41
#define  SC_RES7DESC    42
#define  SC_RES8        43
#define  SC_RES8DESC    44
#define  SC_RES9        45
#define  SC_RES9DESC    46
#define  SC_RESA        47
#define  SC_RESADESC    48
#define  SC_RESB        49
#define  SC_RESBDESC    50
#define  SC_RESC        51
#define  SC_RESCDESC    52
#define  SC_MC1CMODE    53
#define  SC_MC2CMODE    54
#define  SC_OSPC1	55
#define  SC_OSPC2	56
#define  SC_OSCMODE	57
#define  SC_OSPC3	58
#define  SC_OSPC4	59

#define  SC_MIN_INFO_ITEMS  55 //always = last item +1
#define  SC_MAX_INFO_ITEMS  60 //always = last item +1

#ifdef __cplusplus
}
#endif

#endif /* CHUD_SHORTCUTS_H */


