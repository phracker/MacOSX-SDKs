/*
     File:       CarbonCore/Endian.h
 
     Contains:   Endian swapping utilties
                 The contents of this header file are deprecated.
                 Use CFByteOrder API instead.
 
     Copyright:  � 1997-2011 by Apple Inc. All rights reserved.
*/
#ifndef __ENDIAN__
#define __ENDIAN__

#ifndef __CONDITIONALMACROS__
#include <ConditionalMacros.h>
#endif

#ifndef __MACTYPES__
#include <MacTypes.h>
#endif



#include <Availability.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __GNUC__
#include <libkern/OSByteOrder.h>
#endif
	
#pragma pack(push, 2)

/*
    This file provides Endian Flipping routines for dealing with converting data
    between Big-Endian and Little-Endian machines.  These routines are useful
    when writing code to compile for both Big and Little Endian machines and  
    which must handle other endian number formats, such as reading or writing 
    to a file or network packet.
    
    These routines are named as follows:
    
        Endian<U><W>_<S>to<D>

    where
        <U> is whether the integer is signed ('S') or unsigned ('U')
        <W> is integer bit width: 16, 32, or 64 
        <S> is the source endian format: 'B' for big, 'L' for little, or 'N' for native
        <D> is the destination endian format: 'B' for big, 'L' for little, or 'N' for native
    
    For example, to convert a Big Endian 32-bit unsigned integer to the current native format use:
        
        long i = EndianU32_BtoN(data);
        
    This file is set up so that the function macro to nothing when the target runtime already
    is the desired format (e.g. on Big Endian machines, EndianU32_BtoN() macros away).
            
    If long long's are not supported, you cannot get 64-bit quantities as a single value.
    The macros are not defined in that case.

    For gcc, the macros build on top of the inline byte swapping
    routines from <libkern/OSByteOrder.h>, which may have better performance.
    
    
                                <<< W A R N I N G >>>
    
    It is very important not to put any autoincrements inside the macros.  This 
    will produce erroneous results because each time the address is accessed in the macro, 
    the increment occurs.
    
 */
/*
 If building for Mac OS X with GCC, use the inline versions.
 Otherwise, use the macros.
*/
#ifdef __GNUC__

/*
  Implement low level �_Swap functions.
  
   These *always* swap the data, without regard of its underlying
 endian'ness.  If a constant, these will use the constant swapper
   macro.  
*/

#define Endian16_Swap(value)       (UInt16) (__builtin_constant_p(value) ? OSSwapConstInt16(value) : OSSwapInt16(value))
#define Endian32_Swap(value)      (UInt32) (__builtin_constant_p(value) ? OSSwapConstInt32(value) : OSSwapInt32(value))
#define Endian64_Swap(value)      (UInt64) (__builtin_constant_p(value) ? OSSwapConstInt64(value) : OSSwapInt64(value))

#else

/*
    Macro versions for non-gcc compilers
*/
#define Endian16_Swap(value) \
      ((((UInt16)((value) & 0x00FF)) << 8) | \
         (((UInt16)((value) & 0xFF00)) >> 8))

#define Endian32_Swap(value) \
         ((((UInt32)((value) & 0x000000FF)) << 24) | \
         (((UInt32)((value) & 0x0000FF00)) << 8) | \
         (((UInt32)((value) & 0x00FF0000)) >> 8) | \
         (((UInt32)((value) & 0xFF000000)) >> 24))

#if TYPE_LONGLONG
        #define Endian64_Swap(value)                                \
                (((((UInt64)value)<<56) & 0xFF00000000000000ULL)  | \
                 ((((UInt64)value)<<40) & 0x00FF000000000000ULL)  | \
                 ((((UInt64)value)<<24) & 0x0000FF0000000000ULL)  | \
                 ((((UInt64)value)<< 8) & 0x000000FF00000000ULL)  | \
                 ((((UInt64)value)>> 8) & 0x00000000FF000000ULL)  | \
                 ((((UInt64)value)>>24) & 0x0000000000FF0000ULL)  | \
                 ((((UInt64)value)>>40) & 0x000000000000FF00ULL)  | \
                 ((((UInt64)value)>>56) & 0x00000000000000FFULL))
#else
/* 
    Note: When using compilers that don't support "long long",
          Endian64_Swap must be implemented as glue. 
*/
#ifdef __cplusplus
    inline static UInt64 Endian64_Swap(UInt64 value)
    {
        UInt64 temp;
        ((UnsignedWide*)&temp)->lo = Endian32_Swap(((UnsignedWide*)&value)->hi);
        ((UnsignedWide*)&temp)->hi = Endian32_Swap(((UnsignedWide*)&value)->lo);
        return temp;
    }
#else
/*
 *  Endian64_Swap()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern UInt64 
Endian64_Swap(UInt64 value)                                   __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_3, __MAC_10_8, __IPHONE_NA, __IPHONE_NA);


#endif
#endif  /* TYPE_LONGLONG */

#endif  /* defined(__GNUC__) */


/*
    Macro away no-op functions
*/
#if TARGET_RT_BIG_ENDIAN
 #define EndianS16_BtoN(value)               (value)
    #define EndianS16_NtoB(value)               (value)
    #define EndianU16_BtoN(value)               (value)
    #define EndianU16_NtoB(value)               (value)
    #define EndianS32_BtoN(value)               (value)
    #define EndianS32_NtoB(value)               (value)
    #define EndianU32_BtoN(value)               (value)
    #define EndianU32_NtoB(value)               (value)
    #define EndianS64_BtoN(value)               (value)
    #define EndianS64_NtoB(value)               (value)
    #define EndianU64_BtoN(value)               (value)
    #define EndianU64_NtoB(value)               (value)
#else
  #define EndianS16_LtoN(value)               (value)
    #define EndianS16_NtoL(value)               (value)
    #define EndianU16_LtoN(value)               (value)
    #define EndianU16_NtoL(value)               (value)
    #define EndianS32_LtoN(value)               (value)
    #define EndianS32_NtoL(value)               (value)
    #define EndianU32_LtoN(value)               (value)
    #define EndianU32_NtoL(value)               (value)
    #define EndianS64_LtoN(value)               (value)
    #define EndianS64_NtoL(value)               (value)
    #define EndianU64_LtoN(value)               (value)
    #define EndianU64_NtoL(value)               (value)
#endif



/*
    Map native to actual
*/
#if TARGET_RT_BIG_ENDIAN
   #define EndianS16_LtoN(value)               EndianS16_LtoB(value)
  #define EndianS16_NtoL(value)               EndianS16_BtoL(value)
  #define EndianU16_LtoN(value)               EndianU16_LtoB(value)
  #define EndianU16_NtoL(value)               EndianU16_BtoL(value)
  #define EndianS32_LtoN(value)               EndianS32_LtoB(value)
  #define EndianS32_NtoL(value)               EndianS32_BtoL(value)
  #define EndianU32_LtoN(value)               EndianU32_LtoB(value)
  #define EndianU32_NtoL(value)               EndianU32_BtoL(value)
  #define EndianS64_LtoN(value)               EndianS64_LtoB(value)
  #define EndianS64_NtoL(value)               EndianS64_BtoL(value)
  #define EndianU64_LtoN(value)               EndianU64_LtoB(value)
  #define EndianU64_NtoL(value)               EndianU64_BtoL(value)
#else
    #define EndianS16_BtoN(value)               EndianS16_BtoL(value)
  #define EndianS16_NtoB(value)               EndianS16_LtoB(value)
  #define EndianU16_BtoN(value)               EndianU16_BtoL(value)
  #define EndianU16_NtoB(value)               EndianU16_LtoB(value)
  #define EndianS32_BtoN(value)               EndianS32_BtoL(value)
  #define EndianS32_NtoB(value)               EndianS32_LtoB(value)
  #define EndianU32_BtoN(value)               EndianU32_BtoL(value)
  #define EndianU32_NtoB(value)               EndianU32_LtoB(value)
  #define EndianS64_BtoN(value)               EndianS64_BtoL(value)
  #define EndianS64_NtoB(value)               EndianS64_LtoB(value)
  #define EndianU64_BtoN(value)               EndianU64_BtoL(value)
  #define EndianU64_NtoB(value)               EndianU64_LtoB(value)
#endif



/*
    Implement �LtoB and �BtoL
*/
#define EndianS16_LtoB(value)              ((SInt16)Endian16_Swap(value))
#define EndianS16_BtoL(value)                ((SInt16)Endian16_Swap(value))
#define EndianU16_LtoB(value)                ((UInt16)Endian16_Swap(value))
#define EndianU16_BtoL(value)                ((UInt16)Endian16_Swap(value))
#define EndianS32_LtoB(value)                ((SInt32)Endian32_Swap(value))
#define EndianS32_BtoL(value)                ((SInt32)Endian32_Swap(value))
#define EndianU32_LtoB(value)                ((UInt32)Endian32_Swap(value))
#define EndianU32_BtoL(value)                ((UInt32)Endian32_Swap(value))
#define EndianS64_LtoB(value)                ((SInt64)Endian64_Swap((UInt64)value))
#define EndianS64_BtoL(value)                ((SInt64)Endian64_Swap((UInt64)value))
#define EndianU64_LtoB(value)                ((UInt64)Endian64_Swap(value))
#define EndianU64_BtoL(value)                ((UInt64)Endian64_Swap(value))


/*
   These types are used for structures that contain data that is
   always in BigEndian format.  This extra typing prevents little
   endian code from directly changing the data, thus saving much
   time in the debugger.
*/


#if TARGET_RT_LITTLE_ENDIAN
struct BigEndianUInt32 {
  UInt32              bigEndianValue;
};
typedef struct BigEndianUInt32          BigEndianUInt32;
struct BigEndianLong {
  long                bigEndianValue;
};
typedef struct BigEndianLong            BigEndianLong;
struct BigEndianUnsignedLong {
  unsigned long       bigEndianValue;
};
typedef struct BigEndianUnsignedLong    BigEndianUnsignedLong;
struct BigEndianShort {
  short               bigEndianValue;
};
typedef struct BigEndianShort           BigEndianShort;
struct BigEndianUnsignedShort {
  unsigned short      bigEndianValue;
};
typedef struct BigEndianUnsignedShort   BigEndianUnsignedShort;
struct BigEndianFixed {
  Fixed               bigEndianValue;
};
typedef struct BigEndianFixed           BigEndianFixed;
struct BigEndianUnsignedFixed {
  UnsignedFixed       bigEndianValue;
};
typedef struct BigEndianUnsignedFixed   BigEndianUnsignedFixed;
struct BigEndianOSType {
  OSType              bigEndianValue;
};
typedef struct BigEndianOSType          BigEndianOSType;
#else

typedef UInt32                          BigEndianUInt32;
typedef long                            BigEndianLong;
typedef unsigned long                   BigEndianUnsignedLong;
typedef short                           BigEndianShort;
typedef unsigned short                  BigEndianUnsignedShort;
typedef Fixed                           BigEndianFixed;
typedef UnsignedFixed                   BigEndianUnsignedFixed;
typedef OSType                          BigEndianOSType;
#endif  /* TARGET_RT_LITTLE_ENDIAN */

#if TARGET_API_MAC_OSX
/*
        CoreEndian flipping API.

        This API is used to generically massage data buffers, in
        place, from one endian architecture to another.  In effect,
        the API supports registering a set of callbacks that can
        effect this translation.  

        The data types have specific meanings within their domain,
        although some data types can be registered with the same
        callback in several domains.  There is no wildcard domain.

        A set of pre-defined flippers are implemented by the Carbon
        frameworks for most common resource manager and AppleEvent data
        types.
  */
enum {
  kCoreEndianResourceManagerDomain = 'rsrc',
  kCoreEndianAppleEventManagerDomain = 'aevt'
};


/*
 *  CoreEndianFlipProc
 *  
 *  Discussion:
 *    Callback use to flip endian-ness of typed data
 *  
 *  Parameters:
 *    
 *    dataDomain:
 *      Domain of the data type
 *    
 *    dataType:
 *      Type of data being flipped
 *    
 *    id:
 *      resource id (if being flipped on behalf of the resource
 *      manager, otherwise will be zero)
 *    
 *    dataPtr:
 *      Pointer to the data
 *    
 *    dataSize:
 *      Length of the data
 *    
 *    currentlyNative:
 *      Boolean indicating which direction to flip: false means flip
 *      from disk big endian to native (from disk), true means flip
 *      from native to disk big endian (to disk)
 *    
 *    refcon:
 *      An optional user reference supplied when the flipper is
 *      installed
 *  
 *  Result:
 *    Error code indicating whether the data was flipped.  noErr would
 *    indicate that the data was flipped as appropriate; any other
 *    error will be propagated back to the caller.
 */
typedef CALLBACK_API( OSStatus , CoreEndianFlipProc )(OSType dataDomain, OSType dataType, SInt16 id, void *dataPtr, ByteCount dataSize, Boolean currentlyNative, void *refcon);
/*
 * Install a flipper for this application
 */
/*
 *  CoreEndianInstallFlipper()
 *  
 *  Summary:
 *    Installs a flipper proc for the given data type.  If the flipper
 *    is already registered, this flipper will take replace it.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    dataDomain:
 *      Domain of the data type
 *    
 *    dataType:
 *      Type of data for which this flipper should be installed
 *    
 *    proc:
 *      Flipper callback to be called for data of this type
 *    
 *    refcon:
 *      Optional user reference for the flipper
 *  
 *  Result:
 *    Error code indicating whether or not the flipper could be
 *    installed
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CoreEndianInstallFlipper(
  OSType               dataDomain,
  OSType               dataType,
  CoreEndianFlipProc   proc,
  void *               refcon)           /* can be NULL */    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_3, __MAC_10_8, __IPHONE_NA, __IPHONE_NA);


/*
 *  CoreEndianGetFlipper()
 *  
 *  Summary:
 *    Gets an existing data flipper proc for the given data type
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    dataDomain:
 *      Domain of the data type
 *    
 *    dataType:
 *      Type of the data for which this flipper should be installed
 *    
 *    proc:
 *      Pointer to a flipper callback
 *    
 *    refcon:
 *      Pointer to the callback refcon
 *  
 *  Result:
 *    noErr if the given flipper could be found; otherwise
 *    handlerNotFoundErr will be returned.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CoreEndianGetFlipper(
  OSType                dataDomain,
  OSType                dataType,
  CoreEndianFlipProc *  proc,
  void **               refcon)                               __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_3, __MAC_10_8, __IPHONE_NA, __IPHONE_NA);


/*
 *  CoreEndianFlipData()
 *  
 *  Summary:
 *    Calls the flipper for the given data type with the associated data
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    dataDomain:
 *      Domain of the data type
 *    
 *    dataType:
 *      type of the data
 *    
 *    id:
 *      resource id (if not a resource, pass zero)
 *    
 *    data:
 *      a pointer to the data to be flipped (in place)
 *    
 *    dataLen:
 *      length of the data to flip
 *    
 *    currentlyNative:
 *      a boolean indicating the direction to flip (whether the data is
 *      currently native endian or big-endian)
 *  
 *  Result:
 *    Error code indicating whether the data was flipped.  If
 *    handlerNotFound is returned, then no flipping took place (which
 *    is not necessarily an error condtion)
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CoreEndianFlipData(
  OSType      dataDomain,
  OSType      dataType,
  SInt16      id,
  void *      data,
  ByteCount   dataLen,
  Boolean     currentlyNative)                                __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_3, __MAC_10_8, __IPHONE_NA, __IPHONE_NA);


#endif  /* TARGET_API_MAC_OSX */


#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif /* __ENDIAN__ */

