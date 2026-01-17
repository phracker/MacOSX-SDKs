/*
 * Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
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

#ifndef CHUD_PMCS_H
#define CHUD_PMCS_H

/*!
  @header CHUD PMC Macros and constants
  Use the CHUD PMC Macros and constants to simplify and clarify code that makes use of
  CHUD PMC calls. The CHUD PMC functions provide a mechanism to retrieve information from
  the processor and memory controller performance counters. Information is available for
  every device that has performance monitoring capabilities.
*/

#include <stdint.h>
#include <CHUD/chudCtrl.h>

#ifdef __cplusplus
extern "C" {
#endif


#define MAX_PMC_COUNT		8	/* maximum number of counters for all devices */
#define MAX_CPUPMC_COUNT 	8	/* maximum number of available hardware performance counters */
#define MAX_OSPMC_COUNT	 	4	/* maximum number of available OS performance counters */
#define MAX_MCPMC_COUNT	 	6	/* maximum number of available memory controller performance counters */
#define MAX_APIPMC_COUNT	6	/* maximum number of available API performance counters */

#define PPC750_PMC_CT		4
#define PPC7400_PMC_CT		4
#define PPC7450_PMC_CT		6
#define PPC970_PMC_CT		8

#define PPC970_BYTELANE_CT	4

/*indices into arrays PMC results*/
#if _use_defined_pmc_index 
#define PMC_1 		0
#define PMC_2 		1
#define PMC_3		2
#define PMC_4 		3
#define PMC_5 		4
#define PMC_6 		5
#define PMC_7		6
#define PMC_8		7
#define PMC_N		0x7FFFFFFF
#endif

#define CHUD_PMCS_PAUSED	2
#define CHUD_PMCS_RUNNING	1
#define CHUD_PMCS_STOPPED	0

/*!
    @typedef chud_pmc_t
    @abstract   The CHUD API provides these enumerations to allow programs to distinguish between the many PMC registers present in
    the devices.
    @discussion Each device with performance counting capabilities has multiple registers in which the information is collected.  These constants aid in selecting the correct PMC.
    @constant PMC_1 PMC #1
    @constant PMC_2 PMC #2
    @constant PMC_3 PMC #3
    @constant PMC_4 PMC #4
    @constant PMC_5 PMC #5
    @constant PMC_6 PMC #6
    @constant PMC_7 PMC #7
    @constant PMC_8 PMC #8
    @constant PMC_N (ask Eric)
 */
typedef enum {
    PMC_1 =		0,
    PMC_2 =		1,
    PMC_3 =		2,
    PMC_4 =		3,
    PMC_5 =		4,
    PMC_6 =		5,
    PMC_7 =		6,
    PMC_8 =		7,
    PMC_N =		0x7FFFFFFF
} chud_pmc_t;

/*!
    @typedef chud_pmc_mux_t
    @abstract   The CHUD API provides these enumerations to allow programs to select the PMC MUXs.
    @discussion To configure the full set of events available via the PMCs, the PMC MUXs need to be adjusted.  These contants allow the MUXs to easily be referenced.  A complete description of the usage of the PMC MUXs is available from IBM.
    @constant PMC_MUX_TTM0SEL TTM0
    @constant PMC_MUX_TTM1SEL TTM1
    @constant PMC_MUX_TTM3SEL TTM3
    @constant PMC_MUX_SPECSEL SPEC
    @constant PMC_MUX_BYTELANE0SEL Byte lane 0
    @constant PMC_MUX_BYTELANE1SEL Byte lane 1
    @constant PMC_MUX_BYTELANE2SEL Byte lane 2
    @constant PMC_MUX_BYTELANE3SEL Byte lane 3
 */
typedef enum {
    PMC_MUX_TTM0SEL =		0,	// positions: see chud_ttm0_func_t
    PMC_MUX_TTM1SEL =		1,	// chud_ttm1_func_t
    PMC_MUX_TTM3SEL =		3,	// chud_ttm3_func_t
    PMC_MUX_SPECSEL =		8,	// chud_spec_func_t
    PMC_MUX_BYTELANE0SEL =	16,	// chud_bytelane_func_t
    PMC_MUX_BYTELANE1SEL =	17,	// chud_bytelane_func_t
    PMC_MUX_BYTELANE2SEL =	18,	// chud_bytelane_func_t
    PMC_MUX_BYTELANE3SEL =	19	// chud_bytelane_func_t
} chud_pmc_mux_t;

/*!
    @typedef chud_ttm0_func_t
    @abstract  The TTM0 MUX has multiple inputs.  These enumerations allow programs to select the proper input.
    @discussion  The individual PMC MUXs must be configured to access the full set of available PMC events.  These enumerations allow the TTM0 MUX inputs to be selected.  A complete description of the usage of the PMC MUXs is available from IBM.
    @constant PMC_TTM0_FUNC_FPU FPU unit
    @constant PMC_TTM0_FUNC_ISU ISU unit
    @constant PMC_TTM0_FUNC_IFU IFU unit
    @constant PMC_TTM0_FUNC_VMX VMX unit
    @constant PMC_TTM0_POSITION_COUNT number of positions for the TTM0 MUX
 */
typedef enum {
    PMC_TTM0_FUNC_FPU =		0,
    PMC_TTM0_FUNC_ISU =		1,
    PMC_TTM0_FUNC_IFU =		2,
    PMC_TTM0_FUNC_VMX =		3,
    PMC_TTM0_POSITION_COUNT =	4
} chud_ttm0_func_t;

/*!
    @typedef chud_ttm1_func_t
    @abstract  The TTM1 MUX has multiple inputs.  These enumerations allow programs to select the proper input.
    @discussion  The individual PMC MUXs must be configured to access the full set of available PMC events.  These enumerations allow the TTM1 MUX inputs to be selected.  A complete description of the usage of the PMC MUXs is available from IBM.
    @constant PMC_TTM1_FUNC_IDU IDU unit
    @constant PMC_TTM1_FUNC_ISU ISU unit
    @constant PMC_TTM1_FUNC_GPS GPS unit
    @constant PMC_TTM1_POSITION_COUNT number of positions for the TTM1 MUX
 */
typedef enum {
    PMC_TTM1_FUNC_IDU =		0,
    PMC_TTM1_FUNC_RESERVED = 	1,
    PMC_TTM1_FUNC_ISU =		2,
    PMC_TTM1_FUNC_GPS =		3,
    PMC_TTM1_POSITION_COUNT =	4
} chud_ttm1_func_t;

/*!
    @typedef chud_ttm3_func_t
    @abstract  The TTM3 MUX has multiple inputs.  These enumerations allow programs to select the proper input.
    @discussion  The individual PMC MUXs must be configured to access the full set of available PMC events.  These enumerations allow the TTM3 MUX inputs to be selected.  A complete description of the usage of the PMC MUXs is available from IBM.
    @constant PMC_TTM3_FUNC_LSU1_HI_HI Selects the high (left most) bits from both halves of LSU1
    @constant PMC_TTM3_FUNC_LSU1_HI_LO Selects the high (left most) bits from the lower half of LSU1 and the low (right most) bits from the other half.
    @constant PMC_TTM3_FUNC_LSU1_LO_HI Selects the low (right most) bits from the lower half of LSU1 and the high (left most) bits from the other half.
    @constant PMC_TTM3_FUNC_LSU1_LO_LO Selects the low (right most) bits from both halves of LSU1
    @constant PMC_TTM3_POSITION_COUNT number of positions for the TTM3 MUX
 */
typedef enum {
    PMC_TTM3_LSU1_HI_HI =	0,
    PMC_TTM3_LSU1_HI_LO =	1,
    PMC_TTM3_LSU1_LO_HI =	2,
    PMC_TTM3_LSU1_LO_LO = 	3,
    PMC_TTM3_POSITION_COUNT =	4
} chud_ttm3_func_t;

/*!
    @typedef chud_spec_func_t
    @abstract  The SPEC MUX has multiple inputs.  These enumerations allow programs to select the proper input.
    @discussion  The individual PMC MUXs must be configured to access the full set of available PMC events.  These enumerations allow the SPEC MUX inputs to be selected.  A complete description of the usage of the PMC MUXs is available from IBM.
    @constant PMC_SPEC_FUNC_0 Unit 0
    @constant PMC_SPEC_FUNC_1 Unit 1
    @constant PMC_SPEC_FUNC_2 Unit 2
    @constant PMC_SPEC_FUNC_3 Unit 3
    @constant PMC_SPEC_POSITION_COUNT number of positions for the SPEC MUX
 */
typedef enum {
    PMC_SPEC_FUNC_0 =		0,
    PMC_SPEC_FUNC_1 =		1,
    PMC_SPEC_FUNC_2 =		2,
    PMC_SPEC_FUNC_3 =		3,
    PMC_SPEC_POSITION_COUNT =	4
} chud_spec_func_t;

/*!
    @typedef chud_bytelane_func_t
    @abstract  The bytelane MUX has multiple inputs.  These enumerations allow programs to select the proper input.
    @discussion  The individual PMC MUXs must be configured to access the full set of available PMC events.  These enumerations allow the bytelane MUX inputs to be selected.  A complete description of the usage of the PMC MUXs is available from IBM.
    @constant PMC_BYTELANE_TTM0 Selects TTM0 as the input for the bytelane
    @constant PMC_BYTELANE_TTM0 Selects TTM1 as the input for the bytelane
    @constant PMC_BYTELANE_TTM0 Selects LSU0 as the input for the bytelane
    @constant PMC_BYTELANE_TTM0 Selects LSU1 as the input for the bytelane
    @constant PMC_BYTELANE_POSITION_COUNT number of positions for each bytelane MUX
 */
typedef enum {
    PMC_BYTELANE_TTM0 =			0,
    PMC_BYTELANE_TTM1 =			1,
    PMC_BYTELANE_LSU0 =			2,
    PMC_BYTELANE_LSU1 =			3,
    PMC_BYTELANE_POSITION_COUNT =	4
} chud_bytelane_func_t;

#define 	MAX_IMC_PARTIAL_ROW_COUNT	6
#define 	MAX_IMC_COMPLETE_ROW_COUNT	2

/*!
    @typedef chud_inst_math_mode_t
    @abstract  Instruction matching facilities are provided by the PMC system and can be enabled using this enumeration.
    @discussion  The PMCs provide an instruction matching facility.  This enumeration allows selection of the matching system to be used.  A complete description of the usage of the instruction matching facility is available from IBM.
    @constant chudInstMatchNone No instruction matching
    @constant chudInstMatchIFU  IFU instruction matching
    @constant chudInstMatchIDU  IDU instruction matching
 */
typedef enum {
    chudInstMatchNone			= 0,
    chudInstMatchIFU			= 1,
    chudInstMatchIDU			= 2
} chud_inst_match_mode_t;

/*!
    @typedef chud_iop_mark_mode_t
    @abstract Instruction matching facilities are provided by the PMC system and can be enabled using this enumeration.
    @discussion The PMCs provide an instruction matching facility.  This enumeration allows the program to mark each internal operation, microcoded operations, the first internal operation per PPC instruction or the first load/store operation per PPC instruction.  A complete description of the usage of the instruction matching facility is available from IBM.
    @constant chudInstIOPMarkAll Mark all internal operations
    @constant chudInstIOPMarkMicrocode Mark all microcoded operations
    @constant chudInstIOPMarkOneIOPperInst Mark one internal operation per PPC instruction
    @constant chudInstIOPMarkFirstIOPldst Mark one internal operation per load/store instruction
 */
typedef enum {
    chudInstIOPMarkAll			= 0,
    chudInstIOPMarkMicrocode		= 1,
    chudInstIOPMarkOneIOPperInst	= 2,
    chudInstIOPMarkFirstIOPldst		= 3
} chud_iop_mark_mode_t;

/*!
    @typedef chud_ifu_predecode_t
    @abstract Each instruction is decoded by the instruction matching facility before execution.  This is called "predecoding." The predecoding yields four bits that describe the type of instruction. Each of the enumerations represent a four-bit mask used for matching against these predecode bits.
    @discussion The instruction matching facility is capable of marking instructions based on the predecode bits as defined in Book IV.  This enumeration lists all possible combinations of these predecode bits.
    @constant chudIFUPredecodeSimple
    @constant chudIFUPredecodeSimpleLast
    @constant chudIFUPredecodeSimpleFirst
    @constant chudIFUPredecodeSimpleOnly
    @constant chudIFUPredecodeSplit
    @constant chudIFUPredecodeSplitLast
    @constant chudIFUPredecodeSplitFirst
    @constant chudIFUPredecodeSplitOnly
    @constant chudIFUPredecodeBranchConditional
    @constant chudIFUPredecodeBranchUnconditional
    @constant chudIFUPredecodeIllegalOpcode
    @constant chudIFUPredecodeMicrocodeHard
    @constant chudIFUPredecodeMicrocodeSoft
    @constant chudIFUPredecodeMicrocodeCondA
    @constant chudIFUPredecodeMicrocodeCondB
 */
typedef enum {
    chudIFUPredecodeSimple		= 0,
    chudIFUPredecodeSimpleLast		= 1,
    chudIFUPredecodeSimpleFirst		= 2,
    chudIFUPredecodeSimpleOnly		= 3,
    chudIFUPredecodeSplit		= 4,
    chudIFUPredecodeSplitLast		= 5,
    chudIFUPredecodeSplitFirst		= 6,
    chudIFUPredecodeSplitOnly		= 7,
    chudIFUPredecodeBranchConditional	= 8,
    chudIFUPredecodeBranchUncoditional	= 9,
    chudIFUPredecodeIllegalOpcode	= 10,
    chudIFUPredecodeMicrocodeHard	= 12,
    chudIFUPredecodeMicrocodeSoft	= 13,
    chudIFUPredecodeMicrocodeCondA	= 14,
    chudIFUPredecodeMicrocodeCondB	= 15
} chud_ifu_predecode_t;

/*!
    @typedef chud_priv_filter_t
    @abstract PowerPC processors performance monitor facility supports monitoring in three priviledge modes: supervisor , user and both.
    @discussion Use these enumerations with the chudSetPriviledgeMode function.
    @constant chudFmodeIgnorePriv
    @constant chudFmodeOnlySupervisor
    @constant chudFmodeOnlyUser
 */
typedef enum {
    chudFmodeIgnorePriv			= 9,
    chudFmodeOnlySupervisor		= 10,
    chudFmodeOnlyUser			= 11,
} chud_priv_filter_t;
    
/*!
    @typedef chud_mark_filter_t
    @abstract PowerPC processors performance monitor facility supports a performance monitor "mark bit". If the mark bit is set, then only processes that are marked will be profiled.  If the mark bit is not set, then any process will be profiled.
    @discussion Use these enumerations with the chudSetMarkMode function.  In order for the mark mode to take effect, each process must be "marked" using one of the CHUD utility functions: chudMarkPID and chudMarkCurrentThread.
    @constant chudFmodeIgnoreMarkBit
    @constant chudFmodeOnlyMarked
    @constant chudFmodeOnlyUnmarked
 */
typedef enum {
    chudFmodeIgnoreMarkBit		= 12,
    chudFmodeOnlyMarked			= 13,
    chudFmodeOnlyUnmarked		= 14
} chud_mark_filter_t;

/*!
    @typedef chud_mc_source_t
    @abstract The memory controller performance counters can monitor many different aspects of the north bridge chipset. The source constants can be OR'ed together to specify (or ignore) performance events from the many sources.
    @discussion Use these enumerations with the chudSetMCSourceFilter function.
    @constant chudMCsourceNone
    @constant chudMCsourceCPU1
    @constant chudMCsourceCPU2
    @constant chudMCsourceCPU3
    @constant chudMCsourceCPU4
    @constant chudMCsourcePCI
    @constant chudMCsourceHT
    @constant chudMCsouceAGP
    @constant chudMCsourceFwireAndEnet
    @constant chudMCsourceAll
 */
typedef enum { //be able to OR these together
    chudMCsourceNone 		= 0x0,
    chudMCsourceCPU1 		= 0x1,
    chudMCsourceCPU2		= 0x2,
    chudMCsourceCPU3		= 0x4,
    chudMCsourceCPU4		= 0x8,
    chudMCsourcePCI		= 0x10,
    chudMCsourceHT		= 0x20,
    chudMCsourceAGP		= 0x100,
    chudMCsourceFwireAndEnet	= 0x200,
    chudMCsourceAll  		= 0x7FFFFFFF
} chud_mc_source_t;
#define MC_SOURCE_FILTER_CT	12
#define MC_SOURCE_MASK		0x000007FF

/*!
    @typedef chud_mc_access_t
    @abstract The memory controller performance counters can monitor many different aspects of the north bridge chipset. The access constants can be OR'ed together to specify (or ignore) performance events based on the access modes.
    @discussion Use these enumerations with the chudSetMCAccessFilter function.
    @constant chudMCaccessNone
    @constant chudMCaccessRead
    @constant chudMCaccessWrite
    @constant chudMCaccessAll
 */
typedef enum { //be able to OR these together
    chudMCaccessNone 		= 0x0,
    chudMCaccessRead 		= 0x1,
    chudMCaccessWrite		= 0x2,
    chudMCaccessAll  		= 0x7FFFFFFF
} chud_mc_access_t;
#define MC_ACCESS_FILTER_CT	4
#define MC_ACCESS_MASK		0x00000003

/*!
    @typedef chud_mc_page_t
    @abstract The memory controller performance counters can monitor many different aspects of the north bridge chipset. The page state constants can be OR'ed together to specify (or ignore) performance events based on the page state when a 4K page of memory is accessed by a program.
    @discussion Use these enumerations with the chudSetMCPageFilter function.
    @constant chudMCpageNone
    @constant chudMCpageOpenHit
    @constant chudMCpageOpenMiss
    @constant chudMCpageClosed
    @constant chudMCpageAll
 */
typedef enum { //be able to OR these together
    chudMCpageNone 		= 0x0,
    chudMCpageOpenHit 		= 0x1,
    chudMCpageOpenMiss		= 0x2,
    chudMCpageClosed		= 0x4,
    chudMCpageAll  		= 0x7FFFFFFF
} chud_mc_page_t;
#define MC_PAGE_FILTER_CT	5
#define MC_PAGE_MASK		0x00000007

/*!
    @typedef chud_mc_divider_t
    @abstract To prevent the memory controller PMCs from overflowing, the number of events counted can be reduced by a factor as selected.
    @discussion Use these enumerations with the chudSetMCDivider function.
    @constant chudMCdivideBy1
    @constant chudMCdivideBy2
    @constant chudMCdivideBy4
    @constant chudMCdivideBy8
    @constant chudMCdivideBy16
    @constant chudMCdivideBy32
    @constant chudMCdivideBy64
    @constant chudMCdivideBy128
 */
typedef enum {		 
    chudMCdivideBy1 		=   0x1,
    chudMCdivideBy2 		=   0x2,
    chudMCdivideBy4		=   0x4,
    chudMCdivideBy8		=   0x8,
    chudMCdivideBy16		=  0x10,
    chudMCdivideBy32		=  0x20,
    chudMCdivideBy64		=  0x40,
    chudMCdivideBy128		=  0x80
} chud_mc_divider_t;
#define MC_DIVIDER_MASK		0x000000FF
#define MC_DIVIDER_TOO_BIG	0xFFFFFF00

/*!
    @typedef chud_api_source_t
    @abstract The memory controller performance counters can monitor many different aspects of the north bridge chipset. One part of the chipset is Apple Processor Interface (ApplePI). The API source constants can be selected to specify (or ignore) performance events that are generated by the selected sources.
    @discussion Use these enumerations with the chudSetAPISourceFilter function.
    @constant chudAPIsourceSynchronizationQ
    @constant chudAPIsourceCommandSlotQ
    @constant chudAPIsourceSnoopSlotsQ
    @constant chudAPIsourceInterventionQ
    @constant chudAPIsourceMemWtTargetRqQ
    @constant chudAPIsourceMemRdTargetRqQ
    @constant chudAPIsourcePciWtTargetRqQ
    @constant chudAPIsourcePciRdTargetRqQ
    @constant chudAPIsourceHtWtTargetRqQ
    @constant chudAPIsourceHtRdTargetRqQ
    @constant chudAPIsourceRegTargetRqQ
    @constant chudAPIsourceMemReponseQ
    @constant chudAPIsourcePciResponeQ
    @constant chudAPIsourceHtResponseQ
    @constant chudAPIsourceRegResponseQ
    @constant chudAPIsourcePciCohRdRqQ
    @constant chudAPIsourcePciCohWrRqQ
    @constant chudAPIsourceHtCohRdRqQ
    @constant chudAPIsourceHtCohWrRqQ
    @constant chudAPIsourceAPI0MemRdTargetRqQ
    @constant chudAPIsourceAPI1MemRdTargetRqQ
    @constant chudAPIsourceAPI0MemWtTargetRqQ
    @constant chudAPIsourceAPI1MemWtTargetRqQ
    @constant chudAPIsourceAPI0MITargetRqQ
    @constant chudAPIsourceAPI1MITargetRqQ
    @constant chudAPIsourceMemWtDataQ
    @constant chudAPIsourcePciWtDataQ
    @constant chudAPIsourceHtWtDataQ
    @constant chudAPIsourceRegWtDataQ
    @constant chudAPIsourceWriteDataBuffer
    @constant chudAPIsourceWriteDataBufferAPI0Wr
    @constant chudAPIsourceWriteDataBufferAPI1Wr
    @constant chudAPIsourceWriteDataBufferAPI0MI
    @constant chudAPIsourceWriteDataBufferAPI1MI
    @constant chudAPIsourceMasterTagAPI0
    @constant chudAPIsourceMasterTagAPI1
    @constant chudAPIsourceMasterTagAPIx
    @constant chudAPIsourceMasterTagPCI
    @constant chudAPIsourceMasterTagHT
    @constant chudAPIsourceMasterTagAll
 */
typedef enum {
    chudAPIsourceSynchronizationQ = 0,
    chudAPIsourceCommandSlotQ,
    chudAPIsourceSnoopSlotsQ,
    chudAPIsourceInterventionQ,
    chudAPIsourceMemWtTargetRqQ,
    chudAPIsourceMemRdTargetRqQ,
    chudAPIsourcePciWtTargetRqQ,
    chudAPIsourcePciRdTargetRqQ,
    chudAPIsourceHtWtTargetRqQ,
    chudAPIsourceHtRdTargetRqQ,
    chudAPIreserved0 = 10,
    chudAPIsourceRegTargetRqQ,
    chudAPIsourceMemResponseQ,
    chudAPIsourcePciResponseQ,
    chudAPIsourceHtResponseQ,
    chudAPIreserved1 = 15, 
    chudAPIsourceRegResponseQ,
    chudAPIsourcePciCohRdRqQ,
    chudAPIsourcePciCohWtRqQ,
    chudAPIsourceHtCohRdRqQ,
    chudAPIsourceHtCohWtRqQ,
    chudAPIreserved2 = 21,
    chudAPIsourceAPI0MemRdTargetRqQ,
    chudAPIsourceAPI1MemRdTargetRqQ,
    chudAPIsourceAPI0MemWtTargetRqQ,
    chudAPIsourceAPI1MemWtTargetRqQ,
    chudAPIsourceAPI0MITargetRqQ,
    chudAPIsourceAPI1MITargetRqQ,
    chudAPIsourceMemWtDataQ,
    chudAPIsourcePciWtDataQ,
    chudAPIsourceHtWtDataQ,
    chudAPIreserved3 = 31,    
    chudAPIsourceRegWtDataQ,
    chudAPIsourceMemRdDataQ,
    chudAPIsourcePciRdDataQ,
    chudAPIsourceHtRdDataQ,
    chudAPIreserved4 = 36,
    chudAPIsourceRegRdDataQ,
    chudAPIsourceWriteDataBuffer,
    chudAPIsourceWriteDataBufferAPI0Wr,
    chudAPIsourceWriteDataBufferAPI1Wr,
    chudAPIsourceWriteDataBufferAPI0MI,
    chudAPIsourceWriteDataBufferAPI1MI,
    chudAPIsourceMasterTagAPI0,
    chudAPIsourceMasterTagAPI1,
    chudAPIsourceMasterTagAPIx,
    chudAPIreserved5 = 46, 
    chudAPIsourceMasterTagPCI,
    chudAPIsourceMasterTagHT,
    chudAPIreserved6 = 49,
    chudAPIsourceMasterTagAll,
} chud_api_source_t;

/*!
    @typedef chud_api_divider_t
    @abstract To prevent the ApplePI PMCs from overflowing, the number of events counted can be reduced by a factor as selected.
    @discussion Use these enumerations with the chudSetAPIDivider function.
    @constant chudAPIdivideBy1
    @constant chudAPIdivideBy2
    @constant chudAPIdivideBy4
    @constant chudAPIdivideBy8
    @constant chudAPIdivideBy16
    @constant chudAPIdivideBy32
    @constant chudAPIdivideBy64
    @constant chudAPIdivideBy128
 */
typedef enum {		 
    chudAPIdivideBy1 		=   0x1,
    chudAPIdivideBy2 		=   0x2,
    chudAPIdivideBy4		=   0x4,
    chudAPIdivideBy8		=   0x8,
    chudAPIdivideBy16		=  0x10,
    chudAPIdivideBy32		=  0x20,
    chudAPIdivideBy64		=  0x40,
    chudAPIdivideBy128		=  0x80
} chud_api_divider_t;
#define API_DIVIDER_MASK	0x000000FF
#define API_DIVIDER_TOO_BIG	0xFFFFFF00

/*!
    @typedef chud_pmc_mode_t
    @abstract In general, there are three modes for PMCs: unused, counter, and trigger.
    @discussion If a counter's mode is unused, the counter will record no performance information even if the counter has been setup.  If it is marked as chudCounter, it will collect counts as long as the control register has an event for it to count.  If it is marked as chudTrigger, it's overflow state will be used as a trigger for performance monitor interrupt (PMI) based counting.
    @constant chudUnused
    @constant chudCounter
    @constant chudTrigger
 */
typedef enum {
    chudUnused = 0x0,
    chudCounter = 0x1,
    chudTrigger = 0x2
} chud_pmc_mode_t;


#ifndef CHUD_KEXT
int 	chudSetPMCEvent( chud_device_t dev, int pmc, int evtnum ); 
int	chudGetPMCEvent( chud_device_t dev, int pmc ); 
int	chudGetPMCEventCount( chud_device_t dev, int pmc ); 
char *	chudGetCurrentEventName( chud_device_t dev, int pmc ); 
char *	chudGetEventName( chud_device_t dev, int pmc, int evt );
int	chudIsEventValid( chud_device_t dev, int pmc, int evt );

int	chudSetPMCMuxPosition(chud_device_t dev, chud_pmc_mux_t mux, int position);
int	chudGetPMCMuxPosition(chud_device_t dev, chud_pmc_mux_t mux);
int	chudSetInstructionMatchMode( chud_device_t dev, chud_inst_match_mode_t mmode );
int	chudSetIOPMarkMode( chud_device_t dev, chud_iop_mark_mode_t mmode );
int	chudSetIDUMatching( chud_device_t dev, int mask, int match );
int	chudSetPartialIMCRow( chud_device_t dev, int rowIndex, uint64_t value );
int	chudSetCompleteIMCRow( chud_device_t dev, int rowIndex, uint64_t value );
int	chudGetInstructionMatchMode( chud_device_t dev );
int	chudGetIOPMarkMode( chud_device_t dev );
int	chudGetIDUMatching( chud_device_t dev, int *mask, int *match );
int	chudGetPartialIMCRow( chud_device_t dev, int rowIndex, uint64_t *value );
int	chudGetCompleteIMCRow( chud_device_t dev, int rowIndex, uint64_t *value );

int	chudSetPrivilegeFilter( chud_device_t cpudev, chud_priv_filter_t fmode );
int 	chudGetPrivilegeFilter( chud_device_t cpudev );
int	chudSetMarkFilter( chud_device_t dev, chud_mark_filter_t fmode );
int	chudGetMarkFilter( chud_device_t dev );

//changing MC filtering to accomodate U3
int 	chudSetMCSourceFilter( chud_device_t dev, int mc_pmc, chud_mc_source_t fmode );
int 	chudGetMCSourceFilter( chud_device_t dev, int mc_pmc );
int	chudSetMCAccessFilter( chud_device_t dev, int mc_pmc, chud_mc_access_t fmode );
int 	chudGetMCAccessFilter( chud_device_t dev, int mc_pmc );
int	chudSetMCPageFilter( chud_device_t dev, int mc_pmc, chud_mc_page_t fmode );
int 	chudGetMCPageFilter( chud_device_t dev, int mc_pmc );
//'round' to nearest legit divide value
unsigned int chudSetMCcountDivider( chud_device_t dev, int mc_pmc, unsigned int divider );
unsigned int chudGetMCcountDivider( chud_device_t dev, int mc_pmc );

int	chudGetAPISourceCount( chud_device_t dev );
char *	chudGetAPISourceName( chud_device_t dev, int src_idx );
int 	chudSetAPISourceFilter( chud_device_t dev, int api_pmc, chud_mc_source_t fmode );
int 	chudGetAPISourceFilter( chud_device_t dev, int api_pmc );
unsigned int chudSetAPIcountDivider( chud_device_t dev, int api_pmc, unsigned int divider );
unsigned int chudGetAPIcountDivider( chud_device_t dev, int api_pmc );

int 	chudClearPMCs( void );
int 	chudStopPMCs( void );
int 	chudStartPMCs( void );
int 	chudPausePMCs( void );
int 	chudResumePMCs( void );

unsigned int chudSetThresholdValue( chud_device_t dev, unsigned int thresh );
unsigned int chudGetThresholdValue( chud_device_t dev );

int	chudGetBranchFoldingState( int cpunum );
int	chudSetBranchFoldingState( int cpunum, int state );

int	chudSetPMCMode( chud_device_t dev, int pmc, chud_pmc_mode_t mode );
int	chudGetPMCMode( chud_device_t dev, int pmc );
int	chudSetPMCModes( chud_device_t dev, chud_pmc_mode_t *counter_modes );
chud_pmc_mode_t *chudGetPMCModes( chud_device_t dev, int *mode_ct );
#endif /* !CHUD_KEXT */

#ifdef __cplusplus
}
#endif

#endif /* CHUD_PMCS_H */
