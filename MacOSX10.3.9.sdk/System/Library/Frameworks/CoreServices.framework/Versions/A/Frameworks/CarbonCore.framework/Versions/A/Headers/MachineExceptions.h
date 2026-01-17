/*
     File:       CarbonCore/MachineExceptions.h
 
     Contains:   Processor Exception Handling Interfaces.
 
     Version:    CarbonCore-557~1
 
     Copyright:  � 1993-2003 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __MACHINEEXCEPTIONS__
#define __MACHINEEXCEPTIONS__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __MIXEDMODE__
#include <CarbonCore/MixedMode.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=power

/* Some basic declarations used throughout the kernel */
typedef struct OpaqueAreaID*            AreaID;
/* Machine Dependent types for PowerPC: */
struct MachineInformationPowerPC {
  UnsignedWide        CTR;
  UnsignedWide        LR;
  UnsignedWide        PC;
  unsigned long       CR;
  unsigned long       XER;
  unsigned long       MSR;
  unsigned long       MQ;
  unsigned long       ExceptKind;
  unsigned long       DSISR;
  UnsignedWide        DAR;
  UnsignedWide        Reserved;
};
typedef struct MachineInformationPowerPC MachineInformationPowerPC;
struct RegisterInformationPowerPC {
  UnsignedWide        R0;
  UnsignedWide        R1;
  UnsignedWide        R2;
  UnsignedWide        R3;
  UnsignedWide        R4;
  UnsignedWide        R5;
  UnsignedWide        R6;
  UnsignedWide        R7;
  UnsignedWide        R8;
  UnsignedWide        R9;
  UnsignedWide        R10;
  UnsignedWide        R11;
  UnsignedWide        R12;
  UnsignedWide        R13;
  UnsignedWide        R14;
  UnsignedWide        R15;
  UnsignedWide        R16;
  UnsignedWide        R17;
  UnsignedWide        R18;
  UnsignedWide        R19;
  UnsignedWide        R20;
  UnsignedWide        R21;
  UnsignedWide        R22;
  UnsignedWide        R23;
  UnsignedWide        R24;
  UnsignedWide        R25;
  UnsignedWide        R26;
  UnsignedWide        R27;
  UnsignedWide        R28;
  UnsignedWide        R29;
  UnsignedWide        R30;
  UnsignedWide        R31;
};
typedef struct RegisterInformationPowerPC RegisterInformationPowerPC;
struct FPUInformationPowerPC {
  UnsignedWide        Registers[32];
  unsigned long       FPSCR;
  unsigned long       Reserved;
};
typedef struct FPUInformationPowerPC    FPUInformationPowerPC;
union Vector128 {
#ifdef __APPLE_ALTIVEC__
 vector unsigned int         v;
#endif
  unsigned long       l[4];
  unsigned short      s[8];
  unsigned char       c[16];
};
typedef union Vector128                 Vector128;
struct VectorInformationPowerPC {
  Vector128           Registers[32];
  Vector128           VSCR;
  UInt32              VRsave;
};
typedef struct VectorInformationPowerPC VectorInformationPowerPC;
/* Exception related declarations */
enum {
  kWriteReference               = 0,
  kReadReference                = 1,
  kFetchReference               = 2,
  writeReference                = kWriteReference, /* Obsolete name*/
  readReference                 = kReadReference, /* Obsolete name*/
  fetchReference                = kFetchReference /* Obsolete name*/
};


typedef unsigned long                   MemoryReferenceKind;
struct MemoryExceptionInformation {
  AreaID              theArea;                /* The area related to the execption, same as MPAreaID.*/
  LogicalAddress      theAddress;             /* The 32-bit address of the exception.*/
  OSStatus            theError;               /* See enum below.*/
  MemoryReferenceKind  theReference;          /* read, write, instruction fetch.*/
};
typedef struct MemoryExceptionInformation MemoryExceptionInformation;
enum {
  kUnknownException             = 0,
  kIllegalInstructionException  = 1,
  kTrapException                = 2,
  kAccessException              = 3,
  kUnmappedMemoryException      = 4,
  kExcludedMemoryException      = 5,
  kReadOnlyMemoryException      = 6,
  kUnresolvablePageFaultException = 7,
  kPrivilegeViolationException  = 8,
  kTraceException               = 9,
  kInstructionBreakpointException = 10, /* Optional*/
  kDataBreakpointException      = 11,   /* Optional*/
  kIntegerException             = 12,
  kFloatingPointException       = 13,
  kStackOverflowException       = 14,   /* Optional, may be implemented as kAccessException on some systems.*/
  kTaskTerminationException     = 15,   /* Obsolete*/
  kTaskCreationException        = 16,   /* Obsolete*/
  kDataAlignmentException       = 17    /* May occur when a task is in little endian mode or created with kMPTaskTakesAllExceptions.*/
};

#if OLDROUTINENAMES
enum {
  unknownException              = kUnknownException, /* Obsolete name*/
  illegalInstructionException   = kIllegalInstructionException, /* Obsolete name*/
  trapException                 = kTrapException, /* Obsolete name*/
  accessException               = kAccessException, /* Obsolete name*/
  unmappedMemoryException       = kUnmappedMemoryException, /* Obsolete name*/
  excludedMemoryException       = kExcludedMemoryException, /* Obsolete name*/
  readOnlyMemoryException       = kReadOnlyMemoryException, /* Obsolete name*/
  unresolvablePageFaultException = kUnresolvablePageFaultException, /* Obsolete name*/
  privilegeViolationException   = kPrivilegeViolationException, /* Obsolete name*/
  traceException                = kTraceException, /* Obsolete name*/
  instructionBreakpointException = kInstructionBreakpointException, /* Obsolete name*/
  dataBreakpointException       = kDataBreakpointException, /* Obsolete name*/
  integerException              = kIntegerException, /* Obsolete name*/
  floatingPointException        = kFloatingPointException, /* Obsolete name*/
  stackOverflowException        = kStackOverflowException, /* Obsolete name*/
  terminationException          = kTaskTerminationException, /* Obsolete name*/
  kTerminationException         = kTaskTerminationException /* Obsolete name*/
};

#endif  /* OLDROUTINENAMES */


typedef unsigned long                   ExceptionKind;
union ExceptionInfo {
  MemoryExceptionInformation * memoryInfo;
};
typedef union ExceptionInfo             ExceptionInfo;
struct ExceptionInformationPowerPC {
  ExceptionKind       theKind;
  MachineInformationPowerPC * machineState;
  RegisterInformationPowerPC * registerImage;
  FPUInformationPowerPC * FPUImage;
  ExceptionInfo       info;
  VectorInformationPowerPC * vectorImage;
};
typedef struct ExceptionInformationPowerPC ExceptionInformationPowerPC;
#if TARGET_CPU_PPC
typedef ExceptionInformationPowerPC     ExceptionInformation;
typedef MachineInformationPowerPC       MachineInformation;
typedef RegisterInformationPowerPC      RegisterInformation;
typedef FPUInformationPowerPC           FPUInformation;
typedef VectorInformationPowerPC        VectorInformation;
#endif  /* TARGET_CPU_PPC */

#if TARGET_CPU_X86
struct MachineInformationIntel {
  unsigned short      CS;
  unsigned short      DS;
  unsigned short      SS;
  unsigned short      ES;
  unsigned short      FS;
  unsigned short      GS;
  unsigned long       EFLAGS;
  unsigned long       EIP;
};
typedef struct MachineInformationIntel  MachineInformationIntel;
struct RegisterInformationIntel {
  unsigned long       EAX;
  unsigned long       EBX;
  unsigned long       ECX;
  unsigned long       EDX;
  unsigned long       ESI;
  unsigned long       EDI;
  unsigned long       EBP;
  unsigned long       ESP;
};
typedef struct RegisterInformationIntel RegisterInformationIntel;

typedef unsigned char                   FPRegIntel[10];
struct FPUInformationIntel {
  FPRegIntel          Registers[8];
  unsigned short      Control;
  unsigned short      Status;
  unsigned short      Tag;
  unsigned short      Opcode;
  unsigned int        EIP;
  unsigned int        DP;
  unsigned int        DS;
};
typedef struct FPUInformationIntel      FPUInformationIntel;
struct VectorInformationIntel {
  UnsignedWide        Registers[8];
};
typedef struct VectorInformationIntel   VectorInformationIntel;

typedef MachineInformationIntel         MachineInformation;
typedef RegisterInformationIntel        RegisterInformation;
typedef FPUInformationIntel             FPUInformation;
typedef VectorInformationIntel          VectorInformation;
struct ExceptionInformation {
  ExceptionKind       theKind;
  MachineInformation * machineState;
  RegisterInformation * registerImage;
  FPUInformation *    FPUImage;
  ExceptionInfo       info;
  VectorInformation * vectorImage;
};
typedef struct ExceptionInformation     ExceptionInformation;
#endif  /* TARGET_CPU_X86 */

/* 
    Note:   An ExceptionHandler is NOT a UniversalProcPtr, except in Carbon.
            It must be a PowerPC function pointer with NO routine descriptor, 
            except on Carbon, where it must be a UniversalProcPtr (TPP actually)
            to allow the interface to work from both CFM and Mach-O.
*/
typedef CALLBACK_API_C( OSStatus , ExceptionHandlerProcPtr )(ExceptionInformation * theException);
typedef STACK_UPP_TYPE(ExceptionHandlerProcPtr)                 ExceptionHandlerUPP;
/*
 *  NewExceptionHandlerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ExceptionHandlerUPP
NewExceptionHandlerUPP(ExceptionHandlerProcPtr userRoutine)   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeExceptionHandlerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeExceptionHandlerUPP(ExceptionHandlerUPP userUPP)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeExceptionHandlerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeExceptionHandlerUPP(
  ExceptionInformation *  theException,
  ExceptionHandlerUPP     userUPP)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
   ExceptionHandler function pointers (TPP):
   on classic PowerPC, use raw function pointers
   on classic PowerPC with OPAQUE_UPP_TYPES=1, use UPP's
   on Carbon, use UPP's
*/
/* use UPP's*/

typedef ExceptionHandlerUPP             ExceptionHandlerTPP;
typedef ExceptionHandlerTPP             ExceptionHandler;
/* Routine for installing per-process exception handlers */
/*
 *  InstallExceptionHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ExceptionHandlerTPP  InstallExceptionHandler(ExceptionHandlerTPP theHandler) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __MACHINEEXCEPTIONS__ */

