/*	CFBitVector.h
	Copyright (c) 1998-2011, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFBITVECTOR__)
#define __COREFOUNDATION_CFBITVECTOR__ 1

#include <CoreFoundation/CFBase.h>

CF_EXTERN_C_BEGIN

typedef UInt32 CFBit;

typedef const struct __CFBitVector * CFBitVectorRef;
typedef struct __CFBitVector * CFMutableBitVectorRef;

CF_EXPORT CFTypeID	CFBitVectorGetTypeID(void);

CF_EXPORT CFBitVectorRef	CFBitVectorCreate(CFAllocatorRef allocator, const UInt8 *bytes, CFIndex numBits);
CF_EXPORT CFBitVectorRef	CFBitVectorCreateCopy(CFAllocatorRef allocator, CFBitVectorRef bv);
CF_EXPORT CFMutableBitVectorRef	CFBitVectorCreateMutable(CFAllocatorRef allocator, CFIndex capacity);
CF_EXPORT CFMutableBitVectorRef	CFBitVectorCreateMutableCopy(CFAllocatorRef allocator, CFIndex capacity, CFBitVectorRef bv);

CF_EXPORT CFIndex	CFBitVectorGetCount(CFBitVectorRef bv);
CF_EXPORT CFIndex	CFBitVectorGetCountOfBit(CFBitVectorRef bv, CFRange range, CFBit value);
CF_EXPORT Boolean	CFBitVectorContainsBit(CFBitVectorRef bv, CFRange range, CFBit value);
CF_EXPORT CFBit		CFBitVectorGetBitAtIndex(CFBitVectorRef bv, CFIndex idx);
CF_EXPORT void		CFBitVectorGetBits(CFBitVectorRef bv, CFRange range, UInt8 *bytes);
CF_EXPORT CFIndex	CFBitVectorGetFirstIndexOfBit(CFBitVectorRef bv, CFRange range, CFBit value);
CF_EXPORT CFIndex	CFBitVectorGetLastIndexOfBit(CFBitVectorRef bv, CFRange range, CFBit value);

CF_EXPORT void		CFBitVectorSetCount(CFMutableBitVectorRef bv, CFIndex count);
CF_EXPORT void		CFBitVectorFlipBitAtIndex(CFMutableBitVectorRef bv, CFIndex idx);
CF_EXPORT void		CFBitVectorFlipBits(CFMutableBitVectorRef bv, CFRange range);
CF_EXPORT void		CFBitVectorSetBitAtIndex(CFMutableBitVectorRef bv, CFIndex idx, CFBit value);
CF_EXPORT void		CFBitVectorSetBits(CFMutableBitVectorRef bv, CFRange range, CFBit value);
CF_EXPORT void		CFBitVectorSetAllBits(CFMutableBitVectorRef bv, CFBit value);

CF_EXTERN_C_END

#endif /* ! __COREFOUNDATION_CFBITVECTOR__ */

