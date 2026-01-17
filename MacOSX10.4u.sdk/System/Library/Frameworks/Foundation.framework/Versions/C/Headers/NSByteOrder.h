/*	NSByteOrder.h
	Copyright (c) 1995-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObjCRuntime.h>
#import <CoreFoundation/CFByteOrder.h>

enum _NSByteOrder {
    NS_UnknownByteOrder = CFByteOrderUnknown,
    NS_LittleEndian = CFByteOrderLittleEndian,
    NS_BigEndian = CFByteOrderBigEndian
};

FOUNDATION_STATIC_INLINE unsigned NSHostByteOrder(void) {
    return CFByteOrderGetCurrent();
}

FOUNDATION_STATIC_INLINE unsigned short NSSwapShort(unsigned short inv) {
    return CFSwapInt16(inv);
}

FOUNDATION_STATIC_INLINE unsigned int NSSwapInt(unsigned int inv) {
    return CFSwapInt32(inv);
}

FOUNDATION_STATIC_INLINE unsigned long NSSwapLong(unsigned long inv) {
    return CFSwapInt32(inv);
}

FOUNDATION_STATIC_INLINE unsigned long long NSSwapLongLong(unsigned long long inv) {
    return CFSwapInt64(inv);
}

FOUNDATION_STATIC_INLINE unsigned short NSSwapBigShortToHost(unsigned short x) {
    return CFSwapInt16BigToHost(x);
}

FOUNDATION_STATIC_INLINE unsigned int NSSwapBigIntToHost(unsigned int x) {
    return CFSwapInt32BigToHost(x);
}

FOUNDATION_STATIC_INLINE unsigned long NSSwapBigLongToHost(unsigned long x) {
    return CFSwapInt32BigToHost(x);
}

FOUNDATION_STATIC_INLINE unsigned long long NSSwapBigLongLongToHost(unsigned long long x) {
    return CFSwapInt64BigToHost(x);
}

FOUNDATION_STATIC_INLINE unsigned short NSSwapHostShortToBig(unsigned short x) {
    return CFSwapInt16HostToBig(x);
}

FOUNDATION_STATIC_INLINE unsigned int NSSwapHostIntToBig(unsigned int x) {
    return CFSwapInt32HostToBig(x);
}

FOUNDATION_STATIC_INLINE unsigned long NSSwapHostLongToBig(unsigned long x) {
    return CFSwapInt32HostToBig(x);
}

FOUNDATION_STATIC_INLINE unsigned long long NSSwapHostLongLongToBig(unsigned long long x) {
    return CFSwapInt64HostToBig(x);
}

FOUNDATION_STATIC_INLINE unsigned short NSSwapLittleShortToHost(unsigned short x) {
    return CFSwapInt16LittleToHost(x);
}

FOUNDATION_STATIC_INLINE unsigned int NSSwapLittleIntToHost(unsigned int x) {
    return CFSwapInt32LittleToHost(x);
}

FOUNDATION_STATIC_INLINE unsigned long NSSwapLittleLongToHost(unsigned long x) {
    return CFSwapInt32LittleToHost(x);
}

FOUNDATION_STATIC_INLINE unsigned long long NSSwapLittleLongLongToHost(unsigned long long x) {
    return CFSwapInt64LittleToHost(x);
}

FOUNDATION_STATIC_INLINE unsigned short NSSwapHostShortToLittle(unsigned short x) {
    return CFSwapInt16HostToLittle(x);
}

FOUNDATION_STATIC_INLINE unsigned int NSSwapHostIntToLittle(unsigned int x) {
    return CFSwapInt32HostToLittle(x);
}

FOUNDATION_STATIC_INLINE unsigned long NSSwapHostLongToLittle(unsigned long x) {
    return CFSwapInt32HostToLittle(x);
}

FOUNDATION_STATIC_INLINE unsigned long long NSSwapHostLongLongToLittle(unsigned long long x) {
    return CFSwapInt64HostToLittle(x);
}


typedef struct {unsigned long v;} NSSwappedFloat;
typedef struct {unsigned long long v;} NSSwappedDouble;

FOUNDATION_STATIC_INLINE NSSwappedFloat NSConvertHostFloatToSwapped(float x) {
    union fconv {
	float number;
	NSSwappedFloat sf;
    };
    return ((union fconv *)&x)->sf;
}

FOUNDATION_STATIC_INLINE float NSConvertSwappedFloatToHost(NSSwappedFloat x) {
    union fconv {
	float number;
	NSSwappedFloat sf;
    };
    return ((union fconv *)&x)->number;
}

FOUNDATION_STATIC_INLINE NSSwappedDouble NSConvertHostDoubleToSwapped(double x) {
    union dconv {
	double number;
	NSSwappedDouble sd;
    };
    return ((union dconv *)&x)->sd;
}

FOUNDATION_STATIC_INLINE double NSConvertSwappedDoubleToHost(NSSwappedDouble x) {
    union dconv {
	double number;
	NSSwappedDouble sd;
    };
    return ((union dconv *)&x)->number;
}

FOUNDATION_STATIC_INLINE NSSwappedFloat NSSwapFloat(NSSwappedFloat x) {
    x.v = NSSwapLong(x.v);
    return x;
}

FOUNDATION_STATIC_INLINE NSSwappedDouble NSSwapDouble(NSSwappedDouble x) {
    x.v = NSSwapLongLong(x.v);
    return x;
}

#if defined(__BIG_ENDIAN__)

FOUNDATION_STATIC_INLINE double NSSwapBigDoubleToHost(NSSwappedDouble x) {
    return NSConvertSwappedDoubleToHost(x);
}

FOUNDATION_STATIC_INLINE float NSSwapBigFloatToHost(NSSwappedFloat x) {
    return NSConvertSwappedFloatToHost(x);
}

FOUNDATION_STATIC_INLINE NSSwappedDouble NSSwapHostDoubleToBig(double x) {
    return NSConvertHostDoubleToSwapped(x);
}

FOUNDATION_STATIC_INLINE NSSwappedFloat NSSwapHostFloatToBig(float x) {
    return NSConvertHostFloatToSwapped(x);
}

FOUNDATION_STATIC_INLINE double NSSwapLittleDoubleToHost(NSSwappedDouble x) {
    return NSConvertSwappedDoubleToHost(NSSwapDouble(x));
}

FOUNDATION_STATIC_INLINE float NSSwapLittleFloatToHost(NSSwappedFloat x) {
    return NSConvertSwappedFloatToHost(NSSwapFloat(x));
}

FOUNDATION_STATIC_INLINE NSSwappedDouble NSSwapHostDoubleToLittle(double x) {
    return NSSwapDouble(NSConvertHostDoubleToSwapped(x));
}

FOUNDATION_STATIC_INLINE NSSwappedFloat NSSwapHostFloatToLittle(float x) {
    return NSSwapFloat(NSConvertHostFloatToSwapped(x));
}

#elif defined(__LITTLE_ENDIAN__)

FOUNDATION_STATIC_INLINE double NSSwapBigDoubleToHost(NSSwappedDouble x) {
    return NSConvertSwappedDoubleToHost(NSSwapDouble(x));
}

FOUNDATION_STATIC_INLINE float NSSwapBigFloatToHost(NSSwappedFloat x) {
    return NSConvertSwappedFloatToHost(NSSwapFloat(x));
}

FOUNDATION_STATIC_INLINE NSSwappedDouble NSSwapHostDoubleToBig(double x) {
    return NSSwapDouble(NSConvertHostDoubleToSwapped(x));
}

FOUNDATION_STATIC_INLINE NSSwappedFloat NSSwapHostFloatToBig(float x) {
    return NSSwapFloat(NSConvertHostFloatToSwapped(x));
}

FOUNDATION_STATIC_INLINE double NSSwapLittleDoubleToHost(NSSwappedDouble x) {
    return NSConvertSwappedDoubleToHost(x);
}

FOUNDATION_STATIC_INLINE float NSSwapLittleFloatToHost(NSSwappedFloat x) {
    return NSConvertSwappedFloatToHost(x);
}

FOUNDATION_STATIC_INLINE NSSwappedDouble NSSwapHostDoubleToLittle(double x) {
    return NSConvertHostDoubleToSwapped(x);
}

FOUNDATION_STATIC_INLINE NSSwappedFloat NSSwapHostFloatToLittle(float x) {
    return NSConvertHostFloatToSwapped(x);
}

#else
#error Do not know the endianess of this architecture
#endif

