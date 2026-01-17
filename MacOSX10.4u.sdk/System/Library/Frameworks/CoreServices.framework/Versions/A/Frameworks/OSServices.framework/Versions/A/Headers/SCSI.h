/*
     File:       OSServices/SCSI.h
 
     Contains:   SCSI Family Interfaces.
 
     Version:    OSServices-101.1~790
 
     Copyright:  © 1986-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __SCSI__
#define __SCSI__

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

#pragma options align=mac68k

/* TIB opcodes */
enum {
  scInc                         = 1,
  scNoInc                       = 2,
  scAdd                         = 3,
  scMove                        = 4,
  scLoop                        = 5,
  scNop                         = 6,
  scStop                        = 7,
  scComp                        = 8
};

/* TIB instruction */
struct SCSIInstr {
  unsigned short      scOpcode;
  long                scParam1;
  long                scParam2;
};
typedef struct SCSIInstr                SCSIInstr;
/*
 *  SCSIReset()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SCSIGet()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SCSISelect()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SCSICmd()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SCSIRead()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SCSIRBlind()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SCSIWrite()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SCSIWBlind()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SCSIComplete()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SCSIStat()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SCSISelAtn()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SCSIMsgIn()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SCSIMsgOut()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */



enum {
  scsiVERSION                   = 43
};


/*
 * SCSI Completion routine callback for SCSIAction.
 */
typedef CALLBACK_API( void , SCSICallbackProcPtr )(void * scsiPB);
typedef STACK_UPP_TYPE(SCSICallbackProcPtr)                     SCSICallbackUPP;
/*
 *  NewSCSICallbackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern SCSICallbackUPP
NewSCSICallbackUPP(SCSICallbackProcPtr userRoutine)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_2;

/*
 *  DisposeSCSICallbackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeSCSICallbackUPP(SCSICallbackUPP userUPP)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_2;

/*
 *  InvokeSCSICallbackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeSCSICallbackUPP(
  void *           scsiPB,
  SCSICallbackUPP  userUPP)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_2;



/* 
   SCSI Manager 4.3 function codes 
 */
enum {
  SCSINop                       = 0x00, /* Execute nothing                          */
  SCSIExecIO                    = 0x01, /* Execute the specified IO                  */
  SCSIBusInquiry                = 0x03, /* Get parameters for entire path of HBAs           */
  SCSIReleaseQ                  = 0x04, /* Release the frozen SIM queue for particular LUN      */
  SCSIAbortCommand              = 0x10, /* Abort the selected Control Block             */
  SCSIResetBus                  = 0x11, /* Reset the SCSI bus                         */
  SCSIResetDevice               = 0x12, /* Reset the SCSI device                      */
  SCSITerminateIO               = 0x13  /* Terminate any pending IO                    */
};

enum {
  vendorUnique                  = 0xC0  /* 0xC0 thru 0xFF */
};


/* Allocation length defines for some of the fields */
enum {
  handshakeDataLength           = 8,    /* Handshake data length */
  maxCDBLength                  = 16,   /* Space for the CDB bytes/pointer */
  vendorIDLength                = 16    /* ASCII string len for Vendor ID  */
};

/* Define DeviceIdent structure */
struct DeviceIdent {
  UInt8               diReserved;             /* reserved           */
  UInt8               bus;                    /* SCSI - Bus Number   */
  UInt8               targetID;               /* SCSI - Target SCSI ID  */
  UInt8               LUN;                    /* SCSI - LUN            */
};
typedef struct DeviceIdent              DeviceIdent;
/* Constants for the diReserved field of DeviceIdent */
/* used to distinguish whether the DeviceIdent holds */
/* information about a SCSI device (kBusTypeSCSI)    */
/* or an ATA device (kBusTypeATA).  The other        */
/* constants are pretty much deprecated.  Let me     */
/* know if you see any.                              */
enum {
  kBusTypeSCSI                  = 0,
  kBusTypeATA                   = 1,
  kBusTypePCMCIA                = 2,
  kBusTypeMediaBay              = 3
};

/* If diReserved indicates that a DeviceIdent is     */
/* really for ATA, you can cast it to DeviceIdentATA */
/* to get at the important fields.                   */
struct DeviceIdentATA {
  UInt8               diReserved;
  UInt8               busNum;
  UInt8               devNum;
  UInt8               diReserved2;
};
typedef struct DeviceIdentATA           DeviceIdentATA;


/* Command Descriptor Block structure */
union CDB {
  BytePtr             cdbPtr;                 /* pointer to the CDB, or */
  UInt8               cdbBytes[16];           /* the actual CDB to send */
};
typedef union CDB                       CDB;
typedef CDB *                           CDBPtr;
/* Scatter/gather list element (Deprecated for MacOS8) */
struct SGRecord {
  Ptr                 SGAddr;
  UInt32              SGCount;
};
typedef struct SGRecord                 SGRecord;

#define SCSIPBHdr                      \
  struct SCSIHdr* qLink;              \
  short           scsiReserved1;      \
  UInt16          scsiPBLength;       \
  UInt8           scsiFunctionCode;   \
  UInt8           scsiReserved2;      \
  volatile OSErr  scsiResult;         \
  DeviceIdent     scsiDevice;         \
  SCSICallbackUPP scsiCompletion;     \
  UInt32          scsiFlags;          \
  UInt8 *         scsiDriverStorage;  \
  Ptr             scsiXPTprivate;     \
  long            scsiReserved3;

struct SCSIHdr {
  struct SCSIHdr *    qLink;                  /* (internal use, must be nil on entry)   */
  short               scsiReserved1;          /* ->     reserved for input          */
  UInt16              scsiPBLength;           /* -> Length of the entire PB        */
  UInt8               scsiFunctionCode;       /* -> function selector           */
  UInt8               scsiReserved2;          /* <-     reserved for output          */
  volatile OSErr      scsiResult;             /* <- Returned result               */
  DeviceIdent         scsiDevice;             /* -> Device Identifier (bus+target+lun)*/
  SCSICallbackUPP     scsiCompletion;         /* -> Callback on completion function     */
  UInt32              scsiFlags;              /* -> assorted flags            */
  BytePtr             scsiDriverStorage;      /* <> Ptr for driver private use   */
  Ptr                 scsiXPTprivate;         /* private field for use in XPT      */
  long                scsiReserved3;          /* reserved                    */
};
typedef struct SCSIHdr                  SCSIHdr;
struct SCSI_PB {
  SCSIHdr *           qLink;                  /* (internal use, must be nil on entry)   */
  short               scsiReserved1;          /* ->     reserved for input          */
  UInt16              scsiPBLength;           /* -> Length of the entire PB        */
  UInt8               scsiFunctionCode;       /* -> function selector           */
  UInt8               scsiReserved2;          /* <-     reserved for output          */
  volatile OSErr      scsiResult;             /* <- Returned result               */
  DeviceIdent         scsiDevice;             /* -> Device Identifier (bus+target+lun)*/
  SCSICallbackUPP     scsiCompletion;         /* -> Callback on completion function     */
  UInt32              scsiFlags;              /* -> assorted flags            */
  BytePtr             scsiDriverStorage;      /* <> Ptr for driver private use   */
  Ptr                 scsiXPTprivate;         /* private field for use in XPT      */
  long                scsiReserved3;          /* reserved                    */
};
typedef struct SCSI_PB                  SCSI_PB;
struct SCSI_IO {
  SCSIHdr *           qLink;                  /* (internal use, must be nil on entry)   */
  short               scsiReserved1;          /* ->     reserved for input          */
  UInt16              scsiPBLength;           /* -> Length of the entire PB        */
  UInt8               scsiFunctionCode;       /* -> function selector           */
  UInt8               scsiReserved2;          /* <-     reserved for output          */
  volatile OSErr      scsiResult;             /* <- Returned result               */
  DeviceIdent         scsiDevice;             /* -> Device Identifier (bus+target+lun)*/
  SCSICallbackUPP     scsiCompletion;         /* -> Callback on completion function     */
  UInt32              scsiFlags;              /* -> assorted flags            */
  BytePtr             scsiDriverStorage;      /* <> Ptr for driver private use   */
  Ptr                 scsiXPTprivate;         /* private field for use in XPT      */
  long                scsiReserved3;          /* reserved                    */

  UInt16              scsiResultFlags;        /* <- Flags which modify the scsiResult field     */
  UInt16              scsiReserved3pt5;       /* -> Reserved                           */
  BytePtr             scsiDataPtr;            /* -> Pointer to the data buffer or the S/G list      */
  UInt32              scsiDataLength;         /* -> Data transfer length                   */
  BytePtr             scsiSensePtr;           /* -> Ptr to autosense data buffer            */
  UInt8               scsiSenseLength;        /* -> size of the autosense buffer              */
  UInt8               scsiCDBLength;          /* -> Number of bytes for the CDB               */
  UInt16              scsiSGListCount;        /* -> num of scatter gather list entries           */
  UInt32              scsiReserved4;          /* <-     reserved for output                   */
  UInt8               scsiSCSIstatus;         /* <- Returned scsi device status               */
  SInt8               scsiSenseResidual;      /* <- Autosense residual length             */
  UInt16              scsiReserved5;          /* <-     reserved for output                 */
  long                scsiDataResidual;       /* <- Returned Transfer residual length          */
  CDB                 scsiCDB;                /* -> Actual CDB or pointer to CDB            */
  long                scsiTimeout;            /* -> Timeout value (Time Mgr format) (CAM timeout) */
  BytePtr             scsiReserved5pt5;       /* -> Reserved                           */
  UInt16              scsiReserved5pt6;       /* -> Reserved                           */
  UInt16              scsiIOFlags;            /* -> additional I/O flags                      */
  UInt8               scsiTagAction;          /* -> What to do for tag queuing                */
  UInt8               scsiReserved6;          /* ->     reserved for input                   */
  UInt16              scsiReserved7;          /* ->     reserved for input                   */
  UInt16              scsiSelectTimeout;      /* -> Select timeout value                 */
  UInt8               scsiDataType;           /* -> Data description type (i.e. buffer, TIB, S/G)   */
  UInt8               scsiTransferType;       /* -> Transfer type (i.e. Blind vs Polled)       */
  UInt32              scsiReserved8;          /* ->     reserved for input                  */
  UInt32              scsiReserved9;          /* ->     reserved for input                  */
  UInt16              scsiHandshake[8];       /* -> handshaking points (null term'd)    */
  UInt32              scsiReserved10;         /* ->     reserved for input                  */
  UInt32              scsiReserved11;         /* ->   reserved for input                   */
  struct SCSI_IO *    scsiCommandLink;        /* -> Ptr to the next PB in linked cmd chain      */

  UInt8               scsiSIMpublics[8];      /* ->     reserved for input to 3rd-party SIMs     */
  UInt8               scsiAppleReserved6[8];  /* -> reserved for input                     */

                                              /* XPT layer privates (for old-API emulation) */

  UInt16              scsiCurrentPhase;       /* <- phase upon completing old call            */
  short               scsiSelector;           /* -> selector specified in old calls            */
  OSErr               scsiOldCallResult;      /* <- result of old call                     */
  UInt8               scsiSCSImessage;        /* <- Returned scsi device message (for SCSIComplete)*/
  UInt8               XPTprivateFlags;        /* <> various flags                       */
  UInt8               XPTextras[12];          /*                              */
};
typedef struct SCSI_IO                  SCSI_IO;
typedef SCSI_IO                         SCSIExecIOPB;
/* Bus inquiry PB */
struct SCSIBusInquiryPB {
  SCSIHdr *           qLink;                  /* (internal use, must be nil on entry)   */
  short               scsiReserved1;          /* ->     reserved for input          */
  UInt16              scsiPBLength;           /* -> Length of the entire PB        */
  UInt8               scsiFunctionCode;       /* -> function selector           */
  UInt8               scsiReserved2;          /* <-     reserved for output          */
  volatile OSErr      scsiResult;             /* <- Returned result               */
  DeviceIdent         scsiDevice;             /* -> Device Identifier (bus+target+lun)*/
  SCSICallbackUPP     scsiCompletion;         /* -> Callback on completion function     */
  UInt32              scsiFlags;              /* -> assorted flags            */
  BytePtr             scsiDriverStorage;      /* <> Ptr for driver private use   */
  Ptr                 scsiXPTprivate;         /* private field for use in XPT      */
  long                scsiReserved3;          /* reserved                    */

  UInt16              scsiEngineCount;        /* <- Number of engines on HBA                */
  UInt16              scsiMaxTransferType;    /* <- Number of transfer types for this HBA      */

  UInt32              scsiDataTypes;          /* <- which data types are supported by this SIM  */

  UInt16              scsiIOpbSize;           /* <- Size of SCSI_IO PB for this SIM/HBA          */
  UInt16              scsiMaxIOpbSize;        /* <- Size of max SCSI_IO PB for all SIM/HBAs        */

  UInt32              scsiFeatureFlags;       /* <- Supported features flags field           */

  UInt8               scsiVersionNumber;      /* <- Version number for the SIM/HBA           */
  UInt8               scsiHBAInquiry;         /* <- Mimic of INQ byte 7 for the HBA           */
  UInt8               scsiTargetModeFlags;    /* <- Flags for target mode support           */
  UInt8               scsiScanFlags;          /* <- Scan related feature flags            */

  UInt32              scsiSIMPrivatesPtr;     /* <- Ptr to SIM private data area              */
  UInt32              scsiSIMPrivatesSize;    /* <- Size of SIM private data area           */
  UInt32              scsiAsyncFlags;         /* <- Event cap. for Async Callback           */

  UInt8               scsiHiBusID;            /* <- Highest path ID in the subsystem         */
  UInt8               scsiInitiatorID;        /* <- ID of the HBA on the SCSI bus           */
  UInt16              scsiBIReserved0;        /*                                  */

  UInt32              scsiBIReserved1;        /* <-                                */
  UInt32              scsiFlagsSupported;     /* <- which scsiFlags are supported           */

  UInt16              scsiIOFlagsSupported;   /* <- which scsiIOFlags are supported           */
  UInt16              scsiWeirdStuff;         /* <-                               */
  UInt16              scsiMaxTarget;          /* <- maximum Target number supported           */
  UInt16              scsiMaxLUN;             /* <- maximum Logical Unit number supported    */

  char                scsiSIMVendor[16];      /* <- Vendor ID of SIM (or XPT if bus<FF)        */
  char                scsiHBAVendor[16];      /* <- Vendor ID of the HBA                */
  char                scsiControllerFamily[16]; /* <- Family of SCSI Controller           */
  char                scsiControllerType[16]; /* <- Specific Model of SCSI Controller used  */

  char                scsiXPTversion[4];      /* <- version number of XPT              */
  char                scsiSIMversion[4];      /* <- version number of SIM              */
  char                scsiHBAversion[4];      /* <- version number of HBA              */

  UInt8               scsiHBAslotType;        /* <- type of "slot" that this HBA is in       */
  UInt8               scsiHBAslotNumber;      /* <- slot number of this HBA                  */
  UInt16              scsiSIMsRsrcID;         /* <- resource ID of this SIM                  */

  UInt16              scsiBIReserved3;        /* <-                               */
  UInt16              scsiAdditionalLength;   /* <- additional BusInquiry PB len              */
};
typedef struct SCSIBusInquiryPB         SCSIBusInquiryPB;
/* Abort SIM Request PB */
struct SCSIAbortCommandPB {
  SCSIHdr *           qLink;                  /* (internal use, must be nil on entry)   */
  short               scsiReserved1;          /* ->     reserved for input          */
  UInt16              scsiPBLength;           /* -> Length of the entire PB        */
  UInt8               scsiFunctionCode;       /* -> function selector           */
  UInt8               scsiReserved2;          /* <-     reserved for output          */
  volatile OSErr      scsiResult;             /* <- Returned result               */
  DeviceIdent         scsiDevice;             /* -> Device Identifier (bus+target+lun)*/
  SCSICallbackUPP     scsiCompletion;         /* -> Callback on completion function     */
  UInt32              scsiFlags;              /* -> assorted flags            */
  BytePtr             scsiDriverStorage;      /* <> Ptr for driver private use   */
  Ptr                 scsiXPTprivate;         /* private field for use in XPT      */
  long                scsiReserved3;          /* reserved                    */
  SCSI_IO *           scsiIOptr;              /* Pointer to the PB to abort        */
};
typedef struct SCSIAbortCommandPB       SCSIAbortCommandPB;
/* Terminate I/O Process Request PB */
struct SCSITerminateIOPB {
  SCSIHdr *           qLink;                  /* (internal use, must be nil on entry)   */
  short               scsiReserved1;          /* ->     reserved for input          */
  UInt16              scsiPBLength;           /* -> Length of the entire PB        */
  UInt8               scsiFunctionCode;       /* -> function selector           */
  UInt8               scsiReserved2;          /* <-     reserved for output          */
  volatile OSErr      scsiResult;             /* <- Returned result               */
  DeviceIdent         scsiDevice;             /* -> Device Identifier (bus+target+lun)*/
  SCSICallbackUPP     scsiCompletion;         /* -> Callback on completion function     */
  UInt32              scsiFlags;              /* -> assorted flags            */
  BytePtr             scsiDriverStorage;      /* <> Ptr for driver private use   */
  Ptr                 scsiXPTprivate;         /* private field for use in XPT      */
  long                scsiReserved3;          /* reserved                    */
  SCSI_IO *           scsiIOptr;              /* Pointer to the PB to terminate        */
};
typedef struct SCSITerminateIOPB        SCSITerminateIOPB;
/* Reset SCSI Bus PB */
struct SCSIResetBusPB {
  SCSIHdr *           qLink;                  /* (internal use, must be nil on entry)   */
  short               scsiReserved1;          /* ->     reserved for input          */
  UInt16              scsiPBLength;           /* -> Length of the entire PB        */
  UInt8               scsiFunctionCode;       /* -> function selector           */
  UInt8               scsiReserved2;          /* <-     reserved for output          */
  volatile OSErr      scsiResult;             /* <- Returned result               */
  DeviceIdent         scsiDevice;             /* -> Device Identifier (bus+target+lun)*/
  SCSICallbackUPP     scsiCompletion;         /* -> Callback on completion function     */
  UInt32              scsiFlags;              /* -> assorted flags            */
  BytePtr             scsiDriverStorage;      /* <> Ptr for driver private use   */
  Ptr                 scsiXPTprivate;         /* private field for use in XPT      */
  long                scsiReserved3;          /* reserved                    */
};
typedef struct SCSIResetBusPB           SCSIResetBusPB;
/* Reset SCSI Device PB */
struct SCSIResetDevicePB {
  SCSIHdr *           qLink;                  /* (internal use, must be nil on entry)   */
  short               scsiReserved1;          /* ->     reserved for input          */
  UInt16              scsiPBLength;           /* -> Length of the entire PB        */
  UInt8               scsiFunctionCode;       /* -> function selector           */
  UInt8               scsiReserved2;          /* <-     reserved for output          */
  volatile OSErr      scsiResult;             /* <- Returned result               */
  DeviceIdent         scsiDevice;             /* -> Device Identifier (bus+target+lun)*/
  SCSICallbackUPP     scsiCompletion;         /* -> Callback on completion function     */
  UInt32              scsiFlags;              /* -> assorted flags            */
  BytePtr             scsiDriverStorage;      /* <> Ptr for driver private use   */
  Ptr                 scsiXPTprivate;         /* private field for use in XPT      */
  long                scsiReserved3;          /* reserved                    */
};
typedef struct SCSIResetDevicePB        SCSIResetDevicePB;
/* Release SIM Queue PB */
struct SCSIReleaseQPB {
  SCSIHdr *           qLink;                  /* (internal use, must be nil on entry)   */
  short               scsiReserved1;          /* ->     reserved for input          */
  UInt16              scsiPBLength;           /* -> Length of the entire PB        */
  UInt8               scsiFunctionCode;       /* -> function selector           */
  UInt8               scsiReserved2;          /* <-     reserved for output          */
  volatile OSErr      scsiResult;             /* <- Returned result               */
  DeviceIdent         scsiDevice;             /* -> Device Identifier (bus+target+lun)*/
  SCSICallbackUPP     scsiCompletion;         /* -> Callback on completion function     */
  UInt32              scsiFlags;              /* -> assorted flags            */
  BytePtr             scsiDriverStorage;      /* <> Ptr for driver private use   */
  Ptr                 scsiXPTprivate;         /* private field for use in XPT      */
  long                scsiReserved3;          /* reserved                    */
};
typedef struct SCSIReleaseQPB           SCSIReleaseQPB;
/* SCSI Get Virtual ID Info PB */
struct SCSIGetVirtualIDInfoPB {
  SCSIHdr *           qLink;                  /* (internal use, must be nil on entry)   */
  short               scsiReserved1;          /* ->     reserved for input          */
  UInt16              scsiPBLength;           /* -> Length of the entire PB        */
  UInt8               scsiFunctionCode;       /* -> function selector           */
  UInt8               scsiReserved2;          /* <-     reserved for output          */
  volatile OSErr      scsiResult;             /* <- Returned result               */
  DeviceIdent         scsiDevice;             /* -> Device Identifier (bus+target+lun)*/
  SCSICallbackUPP     scsiCompletion;         /* -> Callback on completion function     */
  UInt32              scsiFlags;              /* -> assorted flags            */
  Ptr                 scsiDriverStorage;      /* <> Ptr for driver private use   */
  Ptr                 scsiXPTprivate;         /* private field for use in XPT      */
  long                scsiReserved3;          /* reserved                    */
  UInt16              scsiOldCallID;          /* -> SCSI ID of device in question   */
  Boolean             scsiExists;             /* <- true if device exists        */
  SInt8               filler;
};
typedef struct SCSIGetVirtualIDInfoPB   SCSIGetVirtualIDInfoPB;
/* Create/Lookup/Remove RefNum for Device PB */
struct SCSIDriverPB {
  SCSIHdr *           qLink;                  /* (internal use, must be nil on entry)   */
  short               scsiReserved1;          /* ->     reserved for input          */
  UInt16              scsiPBLength;           /* -> Length of the entire PB        */
  UInt8               scsiFunctionCode;       /* -> function selector           */
  UInt8               scsiReserved2;          /* <-     reserved for output          */
  volatile OSErr      scsiResult;             /* <- Returned result               */
  DeviceIdent         scsiDevice;             /* -> Device Identifier (bus+target+lun)*/
  SCSICallbackUPP     scsiCompletion;         /* -> Callback on completion function     */
  UInt32              scsiFlags;              /* -> assorted flags            */
  Ptr                 scsiDriverStorage;      /* <> Ptr for driver private use   */
  Ptr                 scsiXPTprivate;         /* private field for use in XPT      */
  long                scsiReserved3;          /* reserved                    */
  short               scsiDriver;             /* -> DriverRefNum, For SetDriver, <- For GetNextDriver */
  UInt16              scsiDriverFlags;        /* <> Details of driver/device       */
  DeviceIdent         scsiNextDevice;         /* <- DeviceIdent of the NEXT Item in the list  */
};
typedef struct SCSIDriverPB             SCSIDriverPB;
/* Load Driver PB */
struct SCSILoadDriverPB {
  SCSIHdr *           qLink;                  /* (internal use, must be nil on entry)   */
  short               scsiReserved1;          /* ->     reserved for input          */
  UInt16              scsiPBLength;           /* -> Length of the entire PB        */
  UInt8               scsiFunctionCode;       /* -> function selector           */
  UInt8               scsiReserved2;          /* <-     reserved for output          */
  volatile OSErr      scsiResult;             /* <- Returned result               */
  DeviceIdent         scsiDevice;             /* -> Device Identifier (bus+target+lun)*/
  SCSICallbackUPP     scsiCompletion;         /* -> Callback on completion function     */
  UInt32              scsiFlags;              /* -> assorted flags            */
  Ptr                 scsiDriverStorage;      /* <> Ptr for driver private use   */
  Ptr                 scsiXPTprivate;         /* private field for use in XPT      */
  long                scsiReserved3;          /* reserved                    */
  short               scsiLoadedRefNum;       /* <- SIM returns refnum of driver      */
  Boolean             scsiDiskLoadFailed;     /* -> if true, indicates call after failure to load */
  SInt8               filler;
};
typedef struct SCSILoadDriverPB         SCSILoadDriverPB;

/* Defines for the scsiTransferType field */
enum {
  scsiTransferBlind             = 0,
  scsiTransferPolled            = 1
};

enum {
  scsiErrorBase                 = -7936
};

enum {
  scsiRequestInProgress         = 1,    /* 1   = PB request is in progress          */
                                        /* Execution failed  00-2F */
  scsiRequestAborted            = scsiErrorBase + 2, /* -7934 = PB request aborted by the host        */
  scsiUnableToAbort             = scsiErrorBase + 3, /* -7933 = Unable to Abort PB request          */
  scsiNonZeroStatus             = scsiErrorBase + 4, /* -7932 = PB request completed with an err   */
  scsiUnused05                  = scsiErrorBase + 5, /* -7931 =                        */
  scsiUnused06                  = scsiErrorBase + 6, /* -7930 =                        */
  scsiUnused07                  = scsiErrorBase + 7, /* -7929 =                        */
  scsiUnused08                  = scsiErrorBase + 8, /* -7928 =                        */
  scsiUnableToTerminate         = scsiErrorBase + 9, /* -7927 = Unable to Terminate I/O PB req        */
  scsiSelectTimeout             = scsiErrorBase + 10, /* -7926 = Target selection timeout        */
  scsiCommandTimeout            = scsiErrorBase + 11, /* -7925 = Command timeout              */
  scsiIdentifyMessageRejected   = scsiErrorBase + 12, /* -7924 =                        */
  scsiMessageRejectReceived     = scsiErrorBase + 13, /* -7923 = Message reject received           */
  scsiSCSIBusReset              = scsiErrorBase + 14, /* -7922 = SCSI bus reset sent/received    */
  scsiParityError               = scsiErrorBase + 15, /* -7921 = Uncorrectable parity error occured     */
  scsiAutosenseFailed           = scsiErrorBase + 16, /* -7920 = Autosense: Request sense cmd fail  */
  scsiUnused11                  = scsiErrorBase + 17, /* -7919 =                        */
  scsiDataRunError              = scsiErrorBase + 18, /* -7918 = Data overrun/underrun error     */
  scsiUnexpectedBusFree         = scsiErrorBase + 19, /* -7917 = Unexpected BUS free              */
  scsiSequenceFailed            = scsiErrorBase + 20, /* -7916 = Target bus phase sequence failure  */
  scsiWrongDirection            = scsiErrorBase + 21, /* -7915 = Data phase was in wrong direction  */
  scsiUnused16                  = scsiErrorBase + 22, /* -7914 =                        */
  scsiBDRsent                   = scsiErrorBase + 23, /* -7913 = A SCSI BDR msg was sent to target  */
  scsiTerminated                = scsiErrorBase + 24, /* -7912 = PB request terminated by the host  */
  scsiNoNexus                   = scsiErrorBase + 25, /* -7911 = Nexus is not established        */
  scsiCDBReceived               = scsiErrorBase + 26, /* -7910 = The SCSI CDB has been received        */
                                        /* Couldn't begin execution  30-3F */
  scsiTooManyBuses              = scsiErrorBase + 48, /* -7888 = Register failed because we're full */
  scsiBusy                      = scsiErrorBase + 49, /* -7887 = SCSI subsystem is busy           */
  scsiProvideFail               = scsiErrorBase + 50, /* -7886 = Unable to provide requ. capability */
  scsiDeviceNotThere            = scsiErrorBase + 51, /* -7885 = SCSI device not installed/there    */
  scsiNoHBA                     = scsiErrorBase + 52, /* -7884 = No HBA detected Error           */
  scsiDeviceConflict            = scsiErrorBase + 53, /* -7883 = sorry, max 1 refNum per DeviceIdent    */
  scsiNoSuchXref                = scsiErrorBase + 54, /* -7882 = no such RefNum xref              */
  scsiQLinkInvalid              = scsiErrorBase + 55, /* -7881 = pre-linked PBs not supported      */
                                        /*   (The QLink field was nonzero)          */
                                        /* Parameter errors  40-7F */
  scsiPBLengthError             = scsiErrorBase + 64, /* -7872 = (scsiPBLength is insuf'ct/invalid  */
  scsiFunctionNotAvailable      = scsiErrorBase + 65, /* -7871 = The requ. func is not available    */
  scsiRequestInvalid            = scsiErrorBase + 66, /* -7870 = PB request is invalid           */
  scsiBusInvalid                = scsiErrorBase + 67, /* -7869 = Bus ID supplied is invalid        */
  scsiTIDInvalid                = scsiErrorBase + 68, /* -7868 = Target ID supplied is invalid      */
  scsiLUNInvalid                = scsiErrorBase + 69, /* -7867 = LUN supplied is invalid         */
  scsiIDInvalid                 = scsiErrorBase + 70, /* -7866 = The initiator ID is invalid     */
  scsiDataTypeInvalid           = scsiErrorBase + 71, /* -7865 = scsiDataType requested not supported */
  scsiTransferTypeInvalid       = scsiErrorBase + 72, /* -7864 = scsiTransferType field is too high     */
  scsiCDBLengthInvalid          = scsiErrorBase + 73 /* -7863 = scsiCDBLength field is too big        */
};

/* New errors for SCSI Family         */
enum {
  scsiUnused74                  = scsiErrorBase + 74, /* -7862 =                          */
  scsiUnused75                  = scsiErrorBase + 75, /* -7861 =                          */
  scsiBadDataLength             = scsiErrorBase + 76, /* -7860 = a zero data length in PB        */
  scsiPartialPrepared           = scsiErrorBase + 77, /* -7859 = could not do full prepare mem for I/O*/
  scsiInvalidMsgType            = scsiErrorBase + 78, /* -7858 = Invalid message type (internal)       */
  scsiUnused79                  = scsiErrorBase + 79, /* -7857 =                              */
  scsiBadConnID                 = scsiErrorBase + 80, /* -7856 = Bad Connection ID                */
  scsiUnused81                  = scsiErrorBase + 81, /* -7855 =                          */
  scsiIOInProgress              = scsiErrorBase + 82, /* -7854 = Can't close conn, IO in prog      */
  scsiTargetReserved            = scsiErrorBase + 83, /* -7853 = Target already reserved          */
  scsiUnused84                  = scsiErrorBase + 84, /* -7852 =                          */
  scsiUnused85                  = scsiErrorBase + 85, /* -7851 =                          */
  scsiBadConnType               = scsiErrorBase + 86, /* -7850 = Bad connection type              */
  scsiCannotLoadPlugin          = scsiErrorBase + 87 /* -7849 = No matching service category      */
};

/* +++ */
/*
 * scsiFamilyInternalError and scsiPluginInternalError are intended to handle consistency check failures.
 * For example, if the family stores a record on a lookaside queue, but does not find that record
 * it can use this error to report this failure. SCSI Manager 4.3 uses dsIOCoreErr in a few places,
 * but this is probably not the best error. In general, internal errors should be reported as bugs.
 *
 * The following range of errors is provided for third-party (non-Apple) SCSI SIM and device driver vendors.
 * In general, they would be used for error conditions that are not covered by the standardized errors.
 * They should not normally be conveyed to normal applications, but might be used for communication between
 * a plug-in and a vendor-provided device driver (for example, to manage RAID hot-swapping).
 *
 * Note: I don't know how many SCSI errors are reserved in the error code architecture. Don't assume that
 * we'll actually get sixteen, but we should reserve at least one.
 */
enum {
  scsiFamilyInternalError       = scsiErrorBase + 87, /* -7849 = Internal consistency check failed  */
  scsiPluginInternalError       = scsiErrorBase + 88, /* -7848 = Internal consistency check failed  */
  scsiVendorSpecificErrorBase   = scsiErrorBase + 128, /* ??    = Start of third-party error range     */
  scsiVendorSpecificErrorCount  = 16    /* Number of third-party errors             */
};

/* --- */
enum {
  scsiExecutionErrors           = scsiErrorBase,
  scsiNotExecutedErrors         = scsiTooManyBuses,
  scsiParameterErrors           = scsiPBLengthError
};

/* Defines for the scsiResultFlags field */
enum {
  scsiSIMQFrozen                = 0x0001, /* The SIM queue is frozen w/this err        */
  scsiAutosenseValid            = 0x0002, /* Autosense data valid for target         */
  scsiBusNotFree                = 0x0004 /* At time of callback, SCSI bus is not free  */
};

/* Defines for the bit numbers of the scsiFlags field in the PB header for the SCSIExecIO function */
enum {
  kbSCSIDisableAutosense        = 29,   /* Disable auto sense feature               */
  kbSCSIFlagReservedA           = 28,   /*                             */
  kbSCSIFlagReserved0           = 27,   /*                             */
  kbSCSICDBLinked               = 26,   /* The PB contains a linked CDB             */
  kbSCSIQEnable                 = 25,   /* Target queue actions are enabled          */
  kbSCSICDBIsPointer            = 24,   /* The CDB field contains a pointer          */
  kbSCSIFlagReserved1           = 23,   /*                               */
  kbSCSIInitiateSyncData        = 22,   /* Attempt Sync data xfer and SDTR          */
  kbSCSIDisableSyncData         = 21,   /* Disable sync, go to async            */
  kbSCSISIMQHead                = 20,   /* Place PB at the head of SIM Q          */
  kbSCSISIMQFreeze              = 19,   /* Return the SIM Q to frozen state          */
  kbSCSISIMQNoFreeze            = 18,   /* Disallow SIM Q freezing                 */
  kbSCSIDoDisconnect            = 17,   /* Definitely do disconnect               */
  kbSCSIDontDisconnect          = 16,   /* Definitely don't disconnect              */
  kbSCSIDataReadyForDMA         = 15,   /* Data buffer(s) are ready for DMA          */
  kbSCSIFlagReserved3           = 14,   /*                               */
  kbSCSIDataPhysical            = 13,   /* SG/Buffer data ptrs are physical          */
  kbSCSISensePhysical           = 12,   /* Autosense buffer ptr is physical          */
  kbSCSIFlagReserved5           = 11,   /*                               */
  kbSCSIFlagReserved6           = 10,   /*                               */
  kbSCSIFlagReserved7           = 9,    /*                               */
  kbSCSIFlagReserved8           = 8,    /*                               */
  kbSCSIDataBufferValid         = 7,    /* Data buffer valid                 */
  kbSCSIStatusBufferValid       = 6,    /* Status buffer valid                 */
  kbSCSIMessageBufferValid      = 5,    /* Message buffer valid                */
  kbSCSIFlagReserved9           = 4     /*                             */
};

/* Defines for the bit masks of the scsiFlags field */
enum {
  scsiDirectionMask             = (long)0xC0000000, /* Data direction mask                 */
  scsiDirectionNone             = (long)0xC0000000, /* Data direction (11: no data)          */
  scsiDirectionReserved         = 0x00000000, /* Data direction (00: reserved)       */
  scsiDirectionOut              = (long)0x80000000, /* Data direction (10: DATA OUT)       */
  scsiDirectionIn               = 0x40000000, /* Data direction (01: DATA IN)          */
  scsiDisableAutosense          = 0x20000000, /* Disable auto sense feature          */
  scsiFlagReservedA             = 0x10000000, /*                           */
  scsiFlagReserved0             = 0x08000000, /*                           */
  scsiCDBLinked                 = 0x04000000, /* The PB contains a linked CDB          */
  scsiQEnable                   = 0x02000000, /* Target queue actions are enabled      */
  scsiCDBIsPointer              = 0x01000000, /* The CDB field contains a pointer      */
  scsiFlagReserved1             = 0x00800000, /*                           */
  scsiInitiateSyncData          = 0x00400000, /* Attempt Sync data xfer and SDTR         */
  scsiDisableSyncData           = 0x00200000, /* Disable sync, go to async          */
  scsiSIMQHead                  = 0x00100000, /* Place PB at the head of SIM Q       */
  scsiSIMQFreeze                = 0x00080000, /* Return the SIM Q to frozen state      */
  scsiSIMQNoFreeze              = 0x00040000, /* Disallow SIM Q freezing              */
  scsiDoDisconnect              = 0x00020000, /* Definitely do disconnect             */
  scsiDontDisconnect            = 0x00010000, /* Definitely don't disconnect          */
  scsiDataReadyForDMA           = 0x00008000, /* Data buffer(s) are ready for DMA      */
  scsiFlagReserved3             = 0x00004000, /*  */
  scsiDataPhysical              = 0x00002000, /* SG/Buffer data ptrs are physical      */
  scsiSensePhysical             = 0x00001000, /* Autosense buffer ptr is physical      */
  scsiFlagReserved5             = 0x00000800, /*                         */
  scsiFlagReserved6             = 0x00000400, /*                           */
  scsiFlagReserved7             = 0x00000200, /*                           */
  scsiFlagReserved8             = 0x00000100 /*                           */
};

/* bit masks for the scsiIOFlags field in SCSIExecIOPB */
enum {
  scsiNoParityCheck             = 0x0002, /* disable parity checking                 */
  scsiDisableSelectWAtn         = 0x0004, /* disable select w/Atn                    */
  scsiSavePtrOnDisconnect       = 0x0008, /* do SaveDataPointer upon Disconnect msg          */
  scsiNoBucketIn                = 0x0010, /* donÕt bit bucket in during this I/O           */
  scsiNoBucketOut               = 0x0020, /* donÕt bit bucket out during this I/O        */
  scsiDisableWide               = 0x0040, /* disable wide transfer negotiation           */
  scsiInitiateWide              = 0x0080, /* initiate wide transfer negotiation           */
  scsiRenegotiateSense          = 0x0100, /* renegotiate sync/wide before issuing autosense     */
  scsiDisableDiscipline         = 0x0200, /* disable parameter checking on SCSIExecIO calls */
  scsiIOFlagReserved0080        = 0x0080, /*                                */
  scsiIOFlagReserved8000        = 0x8000 /*                                  */
};

/* Defines for the Bus Inquiry PB fields. */
/* scsiHBAInquiry field bits */
enum {
  scsiBusMDP                    = 0x80, /* Supports Modify Data Pointer message               */
  scsiBusWide32                 = 0x40, /* Supports 32 bit wide SCSI                    */
  scsiBusWide16                 = 0x20, /* Supports 16 bit wide SCSI                    */
  scsiBusSDTR                   = 0x10, /* Supports Sync Data Transfer Req message              */
  scsiBusLinkedCDB              = 0x08, /* Supports linked CDBs                         */
  scsiBusTagQ                   = 0x02, /* Supports tag queue message                    */
  scsiBusSoftReset              = 0x01  /* Supports soft reset                           */
};

/* Defines for the scsiDataType field */
enum {
  scsiDataBuffer                = 0,    /* single contiguous buffer supplied            */
  scsiDataTIB                   = 1,    /* TIB supplied (ptr in scsiDataPtr)           */
  scsiDataSG                    = 2,    /* scatter/gather list supplied             */
  scsiDataIOTable               = 3     /*#(7/11/95) Prepared by Block Storage         */
};

/* scsiDataTypes field bits  */
/*  bits 0->15 Apple-defined, 16->30 3rd-party unique, 31 = reserved */
enum {
  scsiBusDataTIB                = (1 << scsiDataTIB), /* TIB supplied (ptr in scsiDataPtr)   */
  scsiBusDataBuffer             = (1 << scsiDataBuffer), /* single contiguous buffer supplied      */
  scsiBusDataSG                 = (1 << scsiDataSG), /* scatter/gather list supplied        */
  scsiBusDataIOTable            = (1 << scsiDataIOTable), /* (2/6/95) Prepare Memory for IO*/
  scsiBusDataReserved           = (long)0x80000000 /*                            */
};

/* scsiScanFlags field bits */
enum {
  scsiBusScansDevices           = 0x80, /* Bus scans for and maintains device list         */
  scsiBusScansOnInit            = 0x40, /* Bus scans performed at power-up/reboot        */
  scsiBusLoadsROMDrivers        = 0x20  /* may load ROM drivers to support targets       */
};

/* scsiFeatureFlags field bits */
enum {
  scsiBusLVD                    = 0x00000400, /* HBA is Low Voltage Differential Bus         */
  scsiBusUltra3SCSI             = 0x00000200, /* HBA supports Ultra3 SCSI               */
  scsiBusUltra2SCSI             = 0x00000100, /* HBA supports Ultra2 SCSI               */
  scsiBusInternalExternalMask   = 0x000000C0, /* bus internal/external mask           */
  scsiBusInternalExternalUnknown = 0x00000000, /* not known whether bus is inside or outside     */
  scsiBusInternalExternal       = 0x000000C0, /* bus goes inside and outside the box       */
  scsiBusInternal               = 0x00000080, /* bus goes inside the box                */
  scsiBusExternal               = 0x00000040, /* bus goes outside the box             */
  scsiBusCacheCoherentDMA       = 0x00000020, /* DMA is cache coherent                */
  scsiBusOldCallCapable         = 0x00000010, /* SIM is old call capable                */
  scsiBusUltraSCSI              = 0x00000008, /* HBA supports Ultra SCSI                 */
  scsiBusDifferential           = 0x00000004, /* Single Ended (0) or Differential (1)    */
  scsiBusFastSCSI               = 0x00000002, /* HBA supports fast SCSI                  */
  scsiBusDMAavailable           = 0x00000001 /* DMA is available                  */
};

/* scsiWeirdStuff field bits */
enum {
  scsiOddDisconnectUnsafeRead1  = 0x0001, /* Disconnects on odd byte boundries are unsafe with DMA and/or blind reads */
  scsiOddDisconnectUnsafeWrite1 = 0x0002, /* Disconnects on odd byte boundries are unsafe with DMA and/or blind writes */
  scsiBusErrorsUnsafe           = 0x0004, /* Non-handshaked delays or disconnects during blind transfers may cause a crash */
  scsiRequiresHandshake         = 0x0008, /* Non-handshaked delays or disconnects during blind transfers may cause data corruption */
  scsiTargetDrivenSDTRSafe      = 0x0010, /* Targets which initiate synchronous negotiations are supported */
  scsiOddCountForPhysicalUnsafe = 0x0020, /* If using physical addrs all counts must be even, and disconnects must be on even boundries */
  scsiAbortCmdFixed             = 0x0040, /* Set if abort command is fixed to properly make callbacks */
  scsiMeshACKTimingFixed        = 0x0080 /* Set if bug allowing Mesh to release ACK prematurely is fixed */
};

/* scsiHBAslotType values */
enum {
  scsiMotherboardBus            = 0x00, /* A built in Apple supplied bus            */
  scsiNuBus                     = 0x01, /* A SIM on a NuBus card                   */
  scsiPDSBus                    = 0x03, /*    "  on a PDS card                    */
  scsiPCIBus                    = 0x04, /*    "  on a PCI bus card                   */
  scsiPCMCIABus                 = 0x05, /*    "  on a PCMCIA card                  */
  scsiFireWireBridgeBus         = 0x06, /*    "  connected through a FireWire bridge   */
  scsiUSBBus                    = 0x07  /*    "  connected on a USB bus               */
};

/* Defines for the scsiDriverFlags field (in SCSIDriverPB) */
enum {
  scsiDeviceSensitive           = 0x0001, /* Only driver should access this device          */
  scsiDeviceNoOldCallAccess     = 0x0002 /* no old call access to this device            */
};

/*
 * SCSI bus status. These values are returned by the SCSI target in the status phase.
 * They are not related to Macintosh status values (except that values other than
 * scsiStatusGood will result in scsiResult set to scsiNonZeroStatus).
 */
enum {
  scsiStatGood                  = 0x00, /* Good Status*/
  scsiStatCheckCondition        = 0x02, /* Check Condition*/
  scsiStatConditionMet          = 0x04, /* Condition Met*/
  scsiStatBusy                  = 0x08, /* Busy*/
  scsiStatIntermediate          = 0x10, /* Intermediate*/
  scsiStatIntermedMet           = 0x14, /* Intermediate - Condition Met*/
  scsiStatResvConflict          = 0x18, /* Reservation conflict*/
  scsiStatTerminated            = 0x22, /* Command terminated*/
  scsiStatQFull                 = 0x28  /* Queue full*/
};

/* SCSI messages*/
enum {
  kCmdCompleteMsg               = 0,
  kExtendedMsg                  = 1,    /* 0x01*/
  kSaveDataPointerMsg           = 2,    /* 0x02*/
  kRestorePointersMsg           = 3,    /* 0x03*/
  kDisconnectMsg                = 4,    /* 0x04*/
  kInitiatorDetectedErrorMsg    = 5,    /* 0x05*/
  kAbortMsg                     = 6,    /* 0x06*/
  kMsgRejectMsg                 = 7,    /* 0x07*/
  kNoOperationMsg               = 8,    /* 0x08*/
  kMsgParityErrorMsg            = 9,    /* 0x09*/
  kLinkedCmdCompleteMsg         = 10,   /* 0x0a*/
  kLinkedCmdCompleteWithFlagMsg = 11,   /* 0x0b*/
  kBusDeviceResetMsg            = 12,   /* 0x0c*/
  kAbortTagMsg                  = 13,   /* 0x0d*/
  kClearQueueMsg                = 14,   /* 0x0e*/
  kInitiateRecoveryMsg          = 15,   /* 0x0f*/
  kReleaseRecoveryMsg           = 16,   /* 0x10*/
  kTerminateIOProcessMsg        = 17,   /* 0x11*/
  kSimpleQueueTag               = 0x20, /* 0x20*/
  kHeadOfQueueTagMsg            = 0x21, /* 0x21*/
  kOrderedQueueTagMsg           = 0x22, /* 0x22*/
  kIgnoreWideResidueMsg         = 0x23  /* 0x23*/
};


/*
 *  SCSIAction()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use the SCSITaskUserClient API instead.
 *  
 *  Discussion:
 *    This routine is deprecated. It is exported and callable, but it
 *    is no longer being maintained.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.2
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.5 and later
 */
extern OSErr 
SCSIAction(SCSI_PB * parameterBlock)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_2;


/*
 *  SCSIRegisterBus()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.5 and later
 */


/*
 *  SCSIDeregisterBus()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.5 and later
 */


/*
 *  SCSIReregisterBus()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.5 and later
 */


/*
 *  SCSIKillXPT()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.5 and later
 */





#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __SCSI__ */

